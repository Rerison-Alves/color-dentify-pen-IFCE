#include "sensor.h"
#include <Arduino.h>

#define S0 25
#define S1 26
#define S2 27
#define S3 14
#define OUT 13

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

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
    Serial.begin(9600);
}

void loop() {
    Sensor sensor(S0, S1, S2, S3, OUT);
    sensor.reading();
    delay(500);
}