#include <Arduino.h>

typedef enum {
    Key1 = 0x0001,
    Key2 = 0x0002,
    Key3 = 0x0004,
    KeyA = 0x0008,
    Key4 = 0x0010,
    Key5 = 0x0020,
    Key6 = 0x0040,
    KeyB = 0x0080,
    Key7 = 0x0100,
    Key8 = 0x0200,
    Key9 = 0x0400,
    KeyC = 0x0800,
    KeyS = 0x1000,
    Key0 = 0x2000,
    KeyH = 0x4000,
    KeyD = 0x8000
} Key;

class Keypad {
protected:
    uint16_t state;

public:
    Keypad() {
        state = 0;
    }

    void begin() {
        pinMode(31, OUTPUT);
        pinMode(33, OUTPUT);
        pinMode(35, OUTPUT);
        pinMode(37, OUTPUT);
        pinMode(39, INPUT);
        pinMode(41, INPUT);
        pinMode(43, INPUT);
        pinMode(45, INPUT);

        digitalWrite(31, LOW);
        digitalWrite(33, LOW);
        digitalWrite(35, LOW);
        digitalWrite(37, LOW);
    }

    void scan() {
        state = 0;

        digitalWrite(31, HIGH);
        if (digitalRead(39) == HIGH) {
            delay(1);
            if (digitalRead(39) == HIGH)
                state |= KeyD;
        }
        if (digitalRead(41) == HIGH) {
            delay(1);
            if (digitalRead(39) == HIGH)
                state |= KeyC;
        }
        if (digitalRead(43) == HIGH) {
            delay(1);
            if (digitalRead(43) == HIGH)
                state |= KeyB;
        }
        if (digitalRead(45) == HIGH) {
            delay(1);
            if (digitalRead(43) == HIGH)
                state |= KeyA;
        }
        digitalWrite(31, LOW);

        digitalWrite(33, HIGH);
        if (digitalRead(39) == HIGH) {
            delay(1);
            if (digitalRead(39) == HIGH)
                state |= KeyH;
        }
        if (digitalRead(41) == HIGH) {
            delay(1);
            if (digitalRead(41) == HIGH)
                state |= Key9;
        }
        if (digitalRead(43) == HIGH) {
            delay(1);
            if (digitalRead(43) == HIGH)
                state |= Key6;
        }
        if (digitalRead(45) == HIGH) {
            delay(1);
            if (digitalRead(45) == HIGH)
                state |= Key3;
        }
        digitalWrite(33, LOW);

        digitalWrite(35, HIGH);
        if (digitalRead(39) == HIGH) {
            delay(1);
            if (digitalRead(39) == HIGH)
                state |= Key0;
        }
        if (digitalRead(41) == HIGH) {
            delay(1);
            if (digitalRead(41) == HIGH)
                state |= Key8;
        }
        if (digitalRead(43) == HIGH) {
            delay(1);
            if (digitalRead(43) == HIGH)
                state |= Key5;
        }
        if (digitalRead(45) == HIGH) {
            delay(1);
            if (digitalRead(45) == HIGH)
                state |= Key2;
        }
        digitalWrite(35, LOW);

        digitalWrite(37, HIGH);
        if (digitalRead(39) == HIGH) {
            delay(1);
            if (digitalRead(39) == HIGH)
                state |= KeyS;
        }
        if (digitalRead(41) == HIGH) {
            delay(1);
            if (digitalRead(41) == HIGH)
                state |= Key7;
        }
        if (digitalRead(43) == HIGH) {
            delay(1);
            if (digitalRead(43) == HIGH)
                state |= Key4;
        }
        if (digitalRead(45) == HIGH) {
            delay(1);
            if (digitalRead(45) == HIGH)
                state |= Key1;
        }
        digitalWrite(37, LOW);
    }

    bool get(Key key) {
        return state & key;
    }
};