// Light up leds to cumulatively show how far out of time a swinging pendulum is.

unsigned long curtime;
long laston;
long lastoff;
long starttime;
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
long errorband;
long erro;
long swings;

void setup()
{
    Serial.begin(9600);
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
    pinMode(A0, INPUT);
    digitalWrite(A0, HIGH);

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
    errorband = 20;
}

void loop() {
    curtime = millis();
    if (digitalRead(A0)) {
        if ((curtime - lastoff) > 3000) {
            //Reset the timer
            swings = -1;
            starttime = 0;
            erro = 0;
        }
        laston = curtime;
    } else {
        // Prevent triggering more than twice a second
        if ((curtime - lastoff) > 300) {
            swings = swings + 1;
            if (swings == 0) {
                starttime = (long)curtime;
            }
            erro = (60000*swings/period_5 - ((long)curtime - starttime))/errorband;
            Serial.print(60000*swings/period_5); 
            Serial.print("|"); 
            Serial.print(curtime - starttime); 
            Serial.print("|"); 
            Serial.println(erro); 
            lastoff = curtime;
        }
    }
    // We trust that the loop completes in less than a millisecond

    if (erro < -5) {
        digitalWrite(2, HIGH);
    } else {
        digitalWrite(2, LOW);
    }

    if (erro >= -5 && erro < -4) {
        digitalWrite(3, HIGH);
    } else {
        digitalWrite(3, LOW);
    }

    if (erro >= -4 && erro < -3) {
        digitalWrite(4, HIGH);
    } else {
        digitalWrite(4, LOW);
    }

    if (erro >= -3 && erro < -2) {
        digitalWrite(5, HIGH);
    } else {
        digitalWrite(5, LOW);
    }

    if (erro >= -2 && erro < -1) {
        digitalWrite(6, HIGH);
    } else {
        digitalWrite(6, LOW);
    }

    if (erro >= -1 && erro < 0) {
        digitalWrite(7, HIGH);
    } else {
        digitalWrite(7, LOW);
    }

    if (erro >= 0 && erro < 1) {
        digitalWrite(8, HIGH);
    } else {
        digitalWrite(8, LOW);
    }

    if (erro >= 1 && erro < 2) {
        digitalWrite(9, HIGH);
    } else {
        digitalWrite(9, LOW);
    }

    if (erro >= 2 && erro < 3) {
        digitalWrite(10, HIGH);
    } else {
        digitalWrite(10, LOW);
    }

    if (erro >= 3 && erro < 4) {
        digitalWrite(11, HIGH);
    } else {
        digitalWrite(11, LOW);
    }

    if (erro >= 4 && erro < 5) {
        digitalWrite(12, HIGH);
    } else {
        digitalWrite(12, LOW);
    }

    if (erro >= 5) {
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }
}
