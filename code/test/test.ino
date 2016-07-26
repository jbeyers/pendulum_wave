// This is a test program to check the period of a pendulum on each swing. Expected period is about 1 second. The program shows the period in milliseconds for each completed swing.

unsigned long current;
unsigned long newtime;
unsigned long period;

void setup()

{

    Serial.begin(9600);
    current = millis();
    pinMode(7, INPUT_PULLUP);


}

void loop() {

    newtime = millis();
    period = newtime - current;
    if (digitalRead(7) && period > 750) {
        Serial.println(period); 
        current = newtime;
    }
}
