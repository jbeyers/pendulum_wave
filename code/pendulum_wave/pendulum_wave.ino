const int trigger_level = 128; // deviation from average needed for the sensor to trigger.
const float first_tempo = 61.0; // Tempo in bpm of the first pendulum
//const unsigned long pulse = 36ul; // Driver pulse length in milliseconds.
const unsigned long pulse = 24ul; // Driver pulse length in milliseconds.
const unsigned long lockout = 350ul; // Sensor lockout after triggered, in milliseconds.
const int pendulums = 8;

unsigned long now; // The millis count for the current main loop
int sensors[pendulums]; // The immediate sensor readings
int averages[pendulums]; // Sensor long-term averages
int triggers[pendulums]; // The fast moving sensor trigger values
int trigger_levels[pendulums]; // The fast moving sensor trigger values
unsigned long lockouts[pendulums]; // Trackers for the lockout timings
unsigned long pulses[pendulums]; // Trackers for the pulses
float periods[pendulums]; // Swing period for each pendulum. Needed to accurately control speed.
unsigned long previous_triggers[pendulums]; // Keep the previous swing trigger timestamps for imbalance calculations.
unsigned long previous_triggers_2[pendulums]; // Keep the previous swing trigger timestamps for imbalance calculations.
int imbalances[pendulums]; // Track imbalance in the swing length.
bool pos[pendulums]; // flag if this is a positive or negative swing direction. positive is the one taking longer.
float where; // Computes where in the cycle we are.
float modulo; // computes where in the swing we are.
int i; // Loop iterator
int pendulum_to_view = 0; //Which pendulum to view
unsigned long second_timer;
unsigned long switch_time;

void setup() {
  Serial.begin(9600);
  // initialize serial communications at 9600 bps:
  now = millis();
  switch_time = now;
  for ( i = 0; i < pendulums; i++ ) {

    // Lock out the counters and timers for 10 seconds, enough for the averages to settle
    lockouts[i] = now + 10000ul;

    // Set the period for each pendulum
    periods[i] = 60000.0 / (first_tempo - (float)i);

    // Set the output pins
    pinMode(i + 2, OUTPUT);
    trigger_levels[i] = trigger_level;
  }
}

// The main loop is assumed to take 2-3 ms to run. 1 for analog reads, 1 for
// delay, 1 for the main code loop.
void loop() {
  //if (Serial.available() > 0 ) {
  if (now - switch_time > 3500ul ) {
    //pendulum_to_view = Serial.parseInt();
    pendulum_to_view = pendulum_to_view + 1;
    if (pendulum_to_view > 7) {
      pendulum_to_view = 0;
    }
    Serial.print("Switching to pendulum ");
    Serial.print(pendulum_to_view);
    Serial.println();
    switch_time = now;
  }
  now = millis();
  for ( i = 0; i < pendulums; i++ ) {

    // Read the sensor
    sensors[i] = 16 * analogRead(i);

    // average holds a slow-moving long-term average of the sensor reading. The
    // way we compute it should result in insensitivity to spikes.
    // Note: The multiplication factor of 8 allows us to do integer math here.
    // The sensor value is 0-1023, so the average will never be more than 9000.
    if ( sensors[i] > averages[i]) {
      averages[i] = averages[i] + 1;
    }
    if ( sensors[i] < averages[i]) {
      averages[i] = averages[i] - 1;
    }

    // Much faster average for picking up changes
    if ( sensors[i] > triggers[i] ) {
      triggers[i] = triggers[i] + 16;
    }
    if ( sensors[i] < triggers[i] ) {
      triggers[i] = triggers[i] - 16;
    }

    // Trigger detection of a magnet entering
    if ((sensors[i] > (averages[i] + trigger_level)) && (lockouts[i] < now )) {
      // Reset the lockout
      lockouts[i] = now + lockout;

      // Change swing direction.
      pos[i] = !pos[i];

      // Tally the swing imbalance and if it's the reverse of what we expect, reverse the swing directions.
      if (pos[i]) {
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
        where = (now % 60000ul)/periods[i];
        modulo = where - (int)where;

        // The trigger is too sensitive
        if (now - previous_triggers_2[i] < (long)periods[i] - 100ul) {
          trigger_levels[i] = trigger_levels[i] + 1;
        }

        // Only pulse if the speed is too slow or if we are behind
        // TODO: This is overly simplistic
        if (modulo < 0.70 && periods[i] <= (float)(now - previous_triggers_2[i])) {
          if ( i == pendulum_to_view ) {
            Serial.print("pulsing");
            Serial.println();
            pulses[i] = now + pulse;
            digitalWrite(i + 2, HIGH);
          }
        }
        if ( i == pendulum_to_view ) {
          Serial.print(i);
          Serial.print(" | where = ");
          Serial.print(where);
          Serial.print(" | imbalance = ");
          Serial.print(imbalances[i]);
          Serial.print(" | expected period = ");
          Serial.print(periods[i]);
          Serial.print(" | actual period = ");
          Serial.print(now - previous_triggers_2[i]);
          Serial.println();
        }

      }
      previous_triggers_2[i] = previous_triggers[i];
      previous_triggers[i] = now;
    }

    // Write out the pulse
    if ( now < pulses[i] ) {
      digitalWrite(i + 2, HIGH);
    } else {
      digitalWrite(i + 2, LOW);
    }

  }
  if (now - second_timer > 1000ul) {
    for ( i = 0; i < pendulums; i++ ) {
      // The trigger is not sensitive enough
      if (now - previous_triggers_2[i] > (unsigned long)periods[i] + 200ul) {
        trigger_levels[i] = trigger_levels[i] - 10;
      }
    }
    second_timer+=1000ul;
  }

  // wait for the analog-to-digital converter to settle after the last reading
  //delay(1);

}
