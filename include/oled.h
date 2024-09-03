#ifndef OLED_H
#define OLED_H

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

class OledDisplay {
public:
    OledDisplay(int screenWidth, int screenHeight, int sdaPin, int sckPin);
    void begin();
    void displayText(const char* text);

private:
    int _screenWidth;
    int _screenHeight;
    int _sdaPin;
    int _sckPin;
    Adafruit_SSD1306 _display;
};

#endif