#include <Arduino.h>
#include "speaker.h"
#include "sensor.h"

#define S0 25
#define S1 26
#define S2 27
#define S3 14
#define OUT 13
#define DAC_PIN 25

Sensor sensor(S0, S1, S2, S3, OUT);
Speaker speaker(DAC_PIN, 2.0, 15); // DacPin, TimbreFactor, VolumeFactor
Language lang(Language::PORTUGUESE);

void setup() {
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
}

void loop() {
    Color colorread = sensor.reading();
    speaker.playColorSound(colorread);
    delay(500);
}