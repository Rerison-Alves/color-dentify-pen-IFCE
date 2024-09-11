#include "oled.h"
#include <Wire.h>

OledDisplay::OledDisplay(int screenWidth, int screenHeight, int sdaPin, int sckPin)
        : _screenWidth(screenWidth), _screenHeight(screenHeight), _sdaPin(sdaPin), _sckPin(sckPin), _display(screenWidth, screenHeight, &Wire, -1) {}

void OledDisplay::begin() {
    Wire.begin(_sdaPin, _sckPin);
    if (!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    _display.clearDisplay();
    _display.display();
}

void OledDisplay::displayText(const char* text) {
    _display.clearDisplay();
    _display.setTextSize(2);
    _display.setTextColor(WHITE);
    _display.setCursor(0, 28);
    _display.print(text);
    _display.display();
}