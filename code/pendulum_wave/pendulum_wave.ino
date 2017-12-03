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

void setup() {
  Serial.begin(9600);
  // initialize serial communications at 9600 bps:
  now = millis();
  switch_time = now;
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
  if ( now - switch_time > 2001 ) {
    switch_time = now;
    pendulum_to_view += 1;
    if (pendulum_to_view > 7) {
      pendulum_to_view = 0;
    }
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
    Serial.print("triggers: ");
    for ( j = 0; j < pendulums; j++ ) {
      Serial.print(" | ");
      Serial.print(expected_triggers[j]);
    }
    Serial.println();
    Serial.print("pulses  : ");
    for ( j = 0; j < pendulums; j++ ) {
      Serial.print(" | ");
      Serial.print(pulses[j]);
    }
    Serial.println();
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

      // Reset the lockout
      lockouts[i] = now + long(ideal_periods[i] * 0.4);

      // Change swing direction.
      pos[i] = !pos[i];

      // The triggers trigger every time the magnet passes the coil. We only want to work on the positive swing.
      if (pos[i]) {

        // Tally the swing imbalance and if it's the reverse of what we expect, reverse the swing directions.
        if (now - previous_triggers[i] >= previous_triggers[i] - previous_triggers_2[i]) {
          if (imbalances[i] < 30) {
            imbalances[i]++;
          }
        } else {
          imbalances[i]--;
          if (imbalances[i] < -30) {
            imbalances[i] = 0;
            pos[i] = !pos[i];
          }
        }

        // Where in the cycle should we be?
        where = (now % 60000ul)/ideal_periods[i];
        modulo = where - (int)where;

        // Only pulse if the speed is too slow and we are behind
        if (modulo < 0.85 && ideal_periods[i] <= float(now - previous_triggers_2[i] + min(4ul, long(10.0 * modulo)))) {
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
