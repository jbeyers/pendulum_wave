// This is a test program to check the period of a pendulum on each swing. Expected period is about 1 second. The program shows the period in milliseconds for each completed swing.

unsigned long curtime;
unsigned long progress;
int period_1;
int period_2;
int period_3;
int period_4;
int period_5;
int period_6;
int period_7;
int period_8;
int period_9;
int period_10;
int period_11;
int period_12;
int cyc1;
int cyc2;
int cyc3;
int cyc4;
int cyc5;
int cyc6;
int cyc7;
int cyc8;
int cyc9;
int cyc10;
int cyc11;
int cyc12;
unsigned long next_1;
unsigned long next_2;
unsigned long next_3;
unsigned long next_4;
unsigned long next_5;
unsigned long next_6;
unsigned long next_7;
unsigned long next_8;
unsigned long next_9;
unsigned long next_10;
unsigned long next_11;
unsigned long next_12;
unsigned long pulse;

void setup()

{
    curtime = millis();
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    cyc1 = 0;
    cyc2 = 0;
    cyc3 = 0;
    cyc4 = 0;
    cyc5 = 0;
    cyc6 = 0;
    cyc7 = 0;
    cyc8 = 0;
    cyc9 = 0;
    cyc10 = 0;
    cyc11 = 0;
    cyc12 = 0;
    period_1 = 64;
    period_2 = period_1 - 1;
    period_3 = period_2 - 1;
    period_4 = period_3 - 1;
    period_5 = period_4 - 1;
    period_6 = period_5 - 1;
    period_7 = period_6 - 1;
    period_8 = period_7 - 1;
    period_9 = period_8 - 1;
    period_10 = period_9 - 1;
    period_11 = period_10 - 1;
    period_12 = period_11 - 1;
    pulse = 4;
}

void loop() {
    // Get progress as a millisecond value in the cycle
    progress = millis() - curtime;
    if (progress >= 60000) {
        curtime = curtime + 60000;
        progress = millis() - curtime;
        cyc1 = 0;
        cyc2 = 0;
        cyc3 = 0;
        cyc4 = 0;
        cyc5 = 0;
        cyc6 = 0;
        cyc7 = 0;
        cyc8 = 0;
        cyc9 = 0;
        cyc10 = 0;
        cyc11 = 0;
        cyc12 = 0;
    }

    // We trust that the loop completes in less than a millisecond

    next_1 = 60000*cyc1/period_1;
    if (progress >= next_1 && progress <= next_1 + pulse) {
        digitalWrite(1 + 1, HIGH);
    }
    if (progress > next_1 + pulse) {
        cyc1 = cyc1 + 1;
        digitalWrite(1 + 1, LOW);
    }

    next_2 = 60000*cyc2/period_2;
    if (progress >= next_2 && progress <= next_2 + pulse) {
        digitalWrite(2 + 1, HIGH);
    }
    if (progress > next_2 + pulse) {
        cyc2 = cyc2 + 1;
        digitalWrite(2 + 1, LOW);
    }

    next_3 = 60000*cyc3/period_3;
    if (progress >= next_3 && progress <= next_3 + pulse) {
        digitalWrite(3 + 1, HIGH);
    }
    if (progress > next_3 + pulse) {
        cyc3 = cyc3 + 1;
        digitalWrite(3 + 1, LOW);
    }

    next_4 = 60000*cyc4/period_4;
    if (progress >= next_4 && progress <= next_4 + pulse) {
        digitalWrite(4 + 1, HIGH);
    }
    if (progress > next_4 + pulse) {
        cyc4 = cyc4 + 1;
        digitalWrite(4 + 1, LOW);
    }

    next_5 = 60000*cyc5/period_5;
    if (progress >= next_5 && progress <= next_5 + pulse) {
        digitalWrite(5 + 1, HIGH);
    }
    if (progress > next_5 + pulse) {
        cyc5 = cyc5 + 1;
        digitalWrite(5 + 1, LOW);
    }

    next_6 = 60000*cyc6/period_6;
    if (progress >= next_6 && progress <= next_6 + pulse) {
        digitalWrite(6 + 1, HIGH);
    }
    if (progress > next_6 + pulse) {
        cyc6 = cyc6 + 1;
        digitalWrite(6 + 1, LOW);
    }

    next_7 = 60000*cyc7/period_7;
    if (progress >= next_7 && progress <= next_7 + pulse) {
        digitalWrite(7 + 1, HIGH);
    }
    if (progress > next_7 + pulse) {
        cyc7 = cyc7 + 1;
        digitalWrite(7 + 1, LOW);
    }

    next_8 = 60000*cyc8/period_8;
    if (progress >= next_8 && progress <= next_8 + pulse) {
        digitalWrite(8 + 1, HIGH);
    }
    if (progress > next_8 + pulse) {
        cyc8 = cyc8 + 1;
        digitalWrite(8 + 1, LOW);
    }

    next_9 = 60000*cyc9/period_9;
    if (progress >= next_9 && progress <= next_9 + pulse) {
        digitalWrite(9 + 1, HIGH);
    }
    if (progress > next_9 + pulse) {
        cyc9 = cyc9 + 1;
        digitalWrite(9 + 1, LOW);
    }

    next_10 = 60000*cyc10/period_10;
    if (progress >= next_10 && progress <= next_10 + pulse) {
        digitalWrite(10 + 1, HIGH);
    }
    if (progress > next_10 + pulse) {
        cyc10 = cyc10 + 1;
        digitalWrite(10 + 1, LOW);
    }

    next_11 = 60000*cyc11/period_11;
    if (progress >= next_11 && progress <= next_11 + pulse) {
        digitalWrite(11 + 1, HIGH);
    }
    if (progress > next_11 + pulse) {
        cyc11 = cyc11 + 1;
        digitalWrite(11 + 1, LOW);
    }

    next_12 = 60000*cyc12/period_12;
    if (progress >= next_12 && progress <= next_12 + pulse) {
        digitalWrite(12 + 1, HIGH);
    }
    if (progress > next_12 + pulse) {
        cyc12 = cyc12 + 1;
        digitalWrite(12 + 1, LOW);
    }
}
