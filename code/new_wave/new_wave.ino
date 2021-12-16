#include <Servo.h> 

// Create the servo objects
Servo servox;

int low_pos;
int high_pos;
unsigned long period;
unsigned long low_time;
unsigned long current;
unsigned long new_millis;

void setup() { 
  servox.attach(9);  // Attach the servo
  current = millis();
  period = 1022;
  low_time = period*500/1000;
  low_pos = 90;
  // high_pos = 93;
  high_pos = 145;
  pinMode(13, INPUT_PULLUP);
} 

void loop() { 
  if (millis() > current + period) {
    current = current + period;
    servox.write(low_pos);
  } else if ((millis() > current + low_time) && digitalRead(13)) {
    servox.write(high_pos);
  }
}
