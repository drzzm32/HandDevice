#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include "Color.h"

Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

void setup() {
    tft.reset();
    tft.begin(tft.readID());
    tft.setRotation(1);
    tft.setTextColor(0xFFFF);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.fillScreen(0x0000);
    Serial1.begin(9600);
}

void loop() {
    if (Serial1.available() > 0)
        tft.print((char)Serial1.read()); 
}
