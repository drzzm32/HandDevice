#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "Keypad.hpp"
#include "Color.h"

Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
Keypad pad;

char inputBuf[128];
uint8_t inputPtr;
void getInput() {
    if (pad.get(KeyS)) {
        inputPtr = inputPtr > 0 ? inputPtr - 1 : 0;
    } else if (pad.get(Key1)) {
        inputBuf[inputPtr] = '1';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key2)) {
        inputBuf[inputPtr] = '2';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key3)) {
        inputBuf[inputPtr] = '3';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key4)) {
        inputBuf[inputPtr] = '4';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key5)) {
        inputBuf[inputPtr] = '5';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key6)) {
        inputBuf[inputPtr] = '6';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key7)) {
        inputBuf[inputPtr] = '7';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key8)) {
        inputBuf[inputPtr] = '8';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key9)) {
        inputBuf[inputPtr] = '9';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(Key0)) {
        inputBuf[inputPtr] = '0';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(KeyA)) {
        inputBuf[inputPtr] = 'A';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(KeyB)) {
        inputBuf[inputPtr] = 'B';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(KeyC)) {
        inputBuf[inputPtr] = 'C';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    } else if (pad.get(KeyD)) {
        inputBuf[inputPtr] = 'D';
        inputPtr = inputPtr < 127 ? inputPtr + 1 : 127;
        inputBuf[inputPtr] = '\0';
    }
}

void setup() {
    pad.begin();
    inputBuf[0] = '\0'; inputPtr = 0;
    
    tft.reset();
    tft.begin(tft.readID());
    tft.setRotation(1);
    tft.setTextColor(0x0000);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.fillScreen(0xFFFF);

    Serial.begin(9600);
}

void loop() {
    //pad.scan();
    //getInput();
    //tft.setCursor(0, 0);
    //tft.println(inputBuf);

    if (Serial.available() > 0) {
        tft.print((char)Serial.read());
    }
}
