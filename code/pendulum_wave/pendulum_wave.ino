const int trigger_level = 128; // deviation from average needed for the sensor to trigger.
const float first_tempo = 61.0; // Tempo in bpm of the first pendulum
const unsigned long pulse = 40ul; // Driver pulse length in milliseconds.
const unsigned long lockout = 350ul; // Sensor lockout after triggered, in milliseconds.
const unsigned long switch_lockout = 1400ul; // Sensor lockout after triggered, in milliseconds.
const int pendulums = 8;

unsigned long now; // The millis count for the current main loop
int sensors[pendulums]; // The immediate sensor readings
int averages[pendulums]; // Sensor long-term averages
unsigned long lockouts[pendulums]; // Trackers for the lockout timings
unsigned long pulses[pendulums]; // Trackers for the pulses
float ideal_periods[pendulums]; // Swing period for each pendulum. Needed to accurately control speed.
float wheres[pendulums]; // Swing period for each pendulum. Needed to accurately control speed.
unsigned long average_periods[pendulums]; // Keep the previous swing trigger timestamps for imbalance calculations.
unsigned long expected_triggers[pendulums]; // When we expect the next positive trigger.
unsigned long previous_triggers[pendulums]; // Keep the previous swing trigger timestamps for imbalance calculations.
unsigned long previous_triggers_2[pendulums]; // Keep the previous swing trigger timestamps for imbalance calculations.
int trigger_counts[pendulums]; // Count positive triggers to implement a state machine
bool should_pulse[pendulums];
int imbalances[pendulums]; // Track imbalance in the swing length.
bool pos[pendulums]; // flag if this is a positive or negative swing direction. positive is the one taking longer.
float where; // Computes where in the cycle we are.
float modulo; // computes where in the swing we are.
int i; // Loop iterator
int j; // Loop iterator
int pendulum_to_view = -1; //Which pendulum to view
unsigned long switch_time;
int min_counts;
int display_function;
// PID loop parameters;
float loop_p;
float loop_i;
float loop_d;

void setup() {
  Serial.begin(9600);
  // initialize serial communications at 9600 bps:
  now = millis();
  switch_time = now;
  display_function = 0;
  for ( i = 0; i < pendulums; i++ ) {

    // Lock out the counters and timers for 10 seconds, enough for the averages to settle
    lockouts[i] = now + 10000ul;

    // Set the period for each pendulum
    ideal_periods[i] = 60000.0 / (first_tempo - (float)i);

    // Initial values for average periods
    average_periods[i] = 60000ul / (long(first_tempo) - long(i));

    // Trigger counts
    trigger_counts[i] = 0;

    // Set the output pins
    pinMode(i + 2, OUTPUT);
  }
}

// The main loop is assumed to take 2-3 ms to run. 1 for analog reads, 1 for
// delay, 1 for the main code loop.
void loop() {
  now = millis();
  if (Serial.available() > 0 ) {
    display_function = Serial.parseInt();
    Serial.print("Switching to function ");
    Serial.print(display_function);
    Serial.println();
  }

  if ( now - switch_time > 2001 ) {
    switch_time = now;
    pendulum_to_view += 1;
    if (pendulum_to_view > 7) {
      pendulum_to_view = 0;
    }
    if (display_function == 0) {
      Serial.print(pendulum_to_view);
      Serial.print(" | where = ");
      Serial.print(where);
      Serial.print(" | imb= ");
      Serial.print(imbalances[pendulum_to_view]);
      Serial.print(" | ideal = ");
      Serial.print(ideal_periods[pendulum_to_view]);
      Serial.print(" | actual = ");
      Serial.print(average_periods[pendulum_to_view]);
      Serial.println();
    } else if (display_function == 1) {
      Serial.print("where");
      for ( j = 0; j < pendulums; j++ ) {
        Serial.print(" | ");
        Serial.print(wheres[j]);
      }
      Serial.println();
    } else if (display_function == 2) {
      Serial.print("imbalances");
      for ( j = 0; j < pendulums; j++ ) {
        Serial.print(" | ");
        Serial.print(imbalances[j]);
      }
      Serial.println();
    } else if (display_function == 3) {
      Serial.print("periods");
      for ( j = 0; j < pendulums; j++ ) {
        Serial.print(" | ");
        Serial.print(ideal_periods[j]);
        Serial.print("/");
        Serial.print(average_periods[j]);
      }
      Serial.println();
    }
  }

  for ( i = 0; i < pendulums; i++ ) {

    // Read the sensor
    sensors[i] = 16 * analogRead(i);

    // average holds a slow-moving long-term average of the sensor reading. The
    // way we compute it should result in insensitivity to spikes.
    // Note: The multiplication factor above allows us to do integer math here.
    // The sensor value is 0-1023, so the average will never be more than 17000.
    if ( sensors[i] > averages[i]) {
      averages[i] = averages[i] + 1;
    }
    if ( sensors[i] < averages[i]) {
      averages[i] = averages[i] - 1;
    }

    // Trigger detection of a magnet entering
    if ((sensors[i] > (averages[i] + trigger_level)) && (lockouts[i] < now )) {

      // Reset the lockout. This prevents spurious triggering which could throw off the position
      lockouts[i] = now + long(ideal_periods[i] * 0.4);

      // Change swing direction.
      pos[i] = !pos[i];

      // The triggers trigger every time the magnet passes the coil. We only want to work on the positive swing.
      if (pos[i]) {

        // Over time we see if the current swing is longer than the previous
        // one. The coil that senses the swing is off-center, so over time we
        // expect the tally to go up (if our assumption of swing direction is
        // correct) or down (if it's not).  Tally the swing imbalance and if
        // it's the reverse of what we expect, reverse the swing directions.
        // Four gives us a nice balance here: It's slow enough that spurious
        // signals will not shift it, and it's fast enough that if it does, it
        // will switch back before the pendulum gets totally out of sync.
        if (now - previous_triggers[i] >= previous_triggers[i] - previous_triggers_2[i]) {
          if (imbalances[i] < 4) {
            imbalances[i]++;
          }
        } else {
          imbalances[i]--;
          if (imbalances[i] < -4) {
            imbalances[i] = 4;
            pos[i] = !pos[i];
          }
        }

        // Where in the cycle should we be?
        where = (now % 60000ul)/ideal_periods[i];
        wheres[i] = where;
        modulo = where - (int)where;

        // These numbers are needed for the PID control loop. We need to know:
        // * How far behind we are (proportional)
        // * How fast we are catching up (derivative)
        // * How much we should offset the value for (integral)

        // proportional
        // The modulo is always positive. Shift it by a quarter, so that we can
        // do calculations around the zero point. We need this because the
        // modulo is circular: If more than 0.75, it is considered to be fast
        // for the next cycle, instead of slow for this one. 0.75 is chosen
        // because we can actively control the cycle from 0.75 down to 0, while
        // if it's bigger, we need to just not power anything and hope that it
        // will slow down enough without losing the count.
        modulo = modulo - 0.25;

        // integral calculations.
        // This is not really an integral calculation, just a long-running
        // moving average. Same result, but both faster-settling and slower to
        // go haywire, I think.
        if ( modulo < 0 ) {
          loop_i = loop_i + 1.0/128.0;

        // Only pulse if the speed is too slow and we are behind
        if (modulo < 0.75 && ideal_periods[i] <= float(now - previous_triggers_2[i] + min(4ul, long(20.0 * modulo)))) {
          should_pulse[i] = true;
        } else {
          should_pulse[i] = false;
        }

        // Update the trigger counts
        trigger_counts[i] = trigger_counts[i] + 1;

        // Update the expected next pulse start and stop times only if we are not actively triggering
        if (trigger_counts[i] > 2) {
          expected_triggers[i] = now + average_periods[i];
          if (should_pulse[i]) {
            pulses[i] = expected_triggers[i] + pulse;
          }
        }
        // Update the average periods
        if (now - previous_triggers_2[i] < average_periods[i]) {
          average_periods[i] -= 1ul;
        } else if (now - previous_triggers_2[i] > average_periods[i]) {
          average_periods[i] += 1ul;
        }
      }

      // Update the previous trigger times
      previous_triggers_2[i] = previous_triggers[i];
      previous_triggers[i] = now;

    }

    min_counts = 10;
    for ( j = 0; j < pendulums; j++ ) {
      min_counts = min(trigger_counts[j], min_counts);
    }
    if (min_counts > 2) {
      for ( j = 0; j < pendulums; j++ ) {
        trigger_counts[j] = 0;
      }
    }

    // Write out the pulse
    if ( now < pulses[i] && now >= expected_triggers[i] && trigger_counts[i] < 2) {
      digitalWrite(i + 2, HIGH);
    } else {
      digitalWrite(i + 2, LOW);
    }
  }

  // wait for the analog-to-digital converter to settle after the last reading
  //delay(1);

}
