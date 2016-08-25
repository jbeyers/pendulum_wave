// Flash a light on each swing of the pendulum, depending on which input is set

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
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(A0, OUTPUT);
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
    pulse = 100;
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
    if (!(digitalRead(2)) && progress >= next_1 && progress <= next_1 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_1 + pulse) {
        cyc1 = cyc1 + 1;
        digitalWrite(A0, LOW);
    }

    next_2 = 60000*cyc2/period_2;
    if (!(digitalRead(3)) && progress >= next_2 && progress <= next_2 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_2 + pulse) {
        cyc2 = cyc2 + 1;
        digitalWrite(A0, LOW);
    }

    next_3 = 60000*cyc3/period_3;
    if (!(digitalRead(4)) && progress >= next_3 && progress <= next_3 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_3 + pulse) {
        cyc3 = cyc3 + 1;
        digitalWrite(A0, LOW);
    }

    next_4 = 60000*cyc4/period_4;
    if (!(digitalRead(5)) && progress >= next_4 && progress <= next_4 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_4 + pulse) {
        cyc4 = cyc4 + 1;
        digitalWrite(A0, LOW);
    }

    next_5 = 60000*cyc5/period_5;
    if (!(digitalRead(6)) && progress >= next_5 && progress <= next_5 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_5 + pulse) {
        cyc5 = cyc5 + 1;
        digitalWrite(A0, LOW);
    }

    next_6 = 60000*cyc6/period_6;
    if (!(digitalRead(7)) && progress >= next_6 && progress <= next_6 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_6 + pulse) {
        cyc6 = cyc6 + 1;
        digitalWrite(A0, LOW);
    }

    next_7 = 60000*cyc7/period_7;
    if (!(digitalRead(8)) && progress >= next_7 && progress <= next_7 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_7 + pulse) {
        cyc7 = cyc7 + 1;
        digitalWrite(A0, LOW);
    }

    next_8 = 60000*cyc8/period_8;
    if (!(digitalRead(9)) && progress >= next_8 && progress <= next_8 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_8 + pulse) {
        cyc8 = cyc8 + 1;
        digitalWrite(A0, LOW);
    }

    next_9 = 60000*cyc9/period_9;
    if (!(digitalRead(10)) && progress >= next_9 && progress <= next_9 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_9 + pulse) {
        cyc9 = cyc9 + 1;
        digitalWrite(A0, LOW);
    }

    next_10 = 60000*cyc10/period_10;
    if (!(digitalRead(11)) && progress >= next_10 && progress <= next_10 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_10 + pulse) {
        cyc10 = cyc10 + 1;
        digitalWrite(A0, LOW);
    }

    next_11 = 60000*cyc11/period_11;
    if (!(digitalRead(12)) && progress >= next_11 && progress <= next_11 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_11 + pulse) {
        cyc11 = cyc11 + 1;
        digitalWrite(A0, LOW);
    }

    next_12 = 60000*cyc12/period_12;
    if (!(digitalRead(13)) && progress >= next_12 && progress <= next_12 + pulse) {
        digitalWrite(A0, HIGH);
    }
    if (progress > next_12 + pulse) {
        cyc12 = cyc12 + 1;
        digitalWrite(A0, LOW);
    }
}
