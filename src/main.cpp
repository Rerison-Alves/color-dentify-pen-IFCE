#include "sensor.h"
#include "speaker.h"
#include "audios/sound_test.h"
#include <Arduino.h>

#define S0 25
#define S1 26
#define S2 27
#define S3 14
#define OUT 13
#define DAC_PIN 25

void setup() {
    // Setting the outputs
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // Setting the OUT as an input
    pinMode(OUT, INPUT);

    // Setting frequency scaling to 20%
    digitalWrite(S0,HIGH);
    digitalWrite(S1,LOW);

    // Begins serial communication

    //criação do controle de audio
    
    
    Serial.begin(115200);
}

void loop() {
    Sensor sensor(S0, S1, S2, S3, OUT);
    sensor.reading();
    Speaker speaker(DAC_PIN);
    speaker.play_audio(roger);
    
    delay(500);
}