// This is a test program to check the period of a pendulum on each swing. Expected period is about 1 second. The program shows the period in milliseconds for each completed swing.

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int magnet_out = 2;
const int level_off = 8;
// for magnet
const float period_1 = 60.0;
unsigned long pulse = 16;

int sensorValue = 0;        // value read from the pot
unsigned long curtime;
int trig = 400;
int count;
int period;
float bpm;
float avg = 400.0;
int tracker = 400;
int cyc = 0;
bool latch = false;
unsigned long latch_time = 0;
float roller[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float roller_sum = 0.0;

// for magnet
unsigned long curtime1;
unsigned long progress;
int cyc1;
unsigned long next_1;


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  curtime = millis();
  count = 0;
  // For magnet
  curtime1 = millis();
  pinMode(magnet_out, OUTPUT);
  cyc1 = 0;
  latch_time = millis();
}


void loop() {
  sensorValue = analogRead(analogInPin);
  if (sensorValue < tracker ) {
    avg = avg - 0.125;
  }
  if (sensorValue > tracker ) {
    avg = avg + 0.125;
  }
  tracker = int(avg);
  if (sensorValue < trig ) {
    trig--;
  }
  if (sensorValue > trig ) {
    trig++;
  }
  if ((trig > tracker + level_off) && !latch ) {
    latch = true;
    latch_time = millis();
    count++;
    if (count == 20) {
      count = 0;
    }
    period = millis() - curtime;
    curtime = curtime + period;
    bpm = 60000.0/period;
    roller_sum = roller_sum + bpm - roller[count];
    roller[count] = bpm;
    Serial.print("bpm = ");
    Serial.print(bpm);
    Serial.print(" avg = ");
    Serial.print(roller_sum/20.0);
    Serial.println();
  }
  // We expect a trigger every second or so, so unlatch after 750ms
  if ( millis() - latch_time > 750 ) {
    latch = false;
  }
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
//  cyc++;
//  if (cyc > 1000) {
//    cyc = 0;
//    Serial.print("tracker = ");
//    Serial.print(tracker);
//    Serial.print("trig = ");
//    Serial.print(trig);
//    Serial.println();
//  }
  delay(2);

  // Trigger the magnet
  if ( millis() - latch_time < pulse && bpm < period_1) {
    digitalWrite(magnet_out, HIGH);
  } else {
    digitalWrite(magnet_out, LOW);
  }

  // For magnet
  // Get progress as a millisecond value in the cycle
//  progress = millis() - curtime1;
//  if (progress >= 60000) {
//      curtime1 = curtime1 + 60000;
//      progress = millis() - curtime1;
//      cyc1 = 0;
//  }
//
//  next_1 = 60000*cyc1/period_1;
//  if (progress >= next_1 && progress <= next_1 + pulse && bpm < 61.0) {
//      digitalWrite(magnet_out, HIGH);
//  }
//  if (progress > next_1 + pulse) {
//      cyc1 = cyc1 + 1;
//      digitalWrite(magnet_out, LOW);
//  }
}
