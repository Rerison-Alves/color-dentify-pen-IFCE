#include <Arduino.h>
#include "speaker.h"
#include "sensor.h"
#include "oled.h"

#define S0 4
#define S1 5
#define S2 18
#define S3 19
#define OUT 23

Sensor sensor(S0, S1, S2, S3, OUT);

#define DAC_PIN 25

Speaker speaker(DAC_PIN, 2.0, 15); // DacPin, TimbreFactor, VolumeFactor
Language lang(Language::PORTUGUESE);

//Definindo tela oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SDA_PIN 21
#define SCK_PIN 22

OledDisplay oled(SCREEN_WIDTH, SCREEN_HEIGHT, SDA_PIN, SCK_PIN);

void setup() {
  // Begins serial communication
    Serial.begin(115200);
  
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    pinMode(OUT, INPUT);

    digitalWrite(S0,HIGH);
    digitalWrite(S1,LOW);

    speaker.begin();
    speaker.setLanguage(lang);

    oled.begin();
}

void loop() {
    Color colorread = sensor.reading();
    oled.displayText(colorToString(colorread,lang));
    speaker.playColorSound(colorread);
    delay(500);
}