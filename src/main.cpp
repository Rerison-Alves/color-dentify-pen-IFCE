#include "sensor.h"
#include "oled.h"
#include <Arduino.h>

//Definindo pinos sensor TCS230
#define S0 25
#define S1 26
#define S2 27
#define S3 14
#define OUT 13

//Definindo tela oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SDA_PIN 21
#define SCK_PIN 22

OledDisplay oled(SCREEN_WIDTH, SCREEN_HEIGHT, SDA_PIN, SCK_PIN);

void setup() {
    // Begins serial communication
    Serial.begin(9600);

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

    // Display message on oled screen
    oled.begin();
    oled.displayText("Hello World");
}

void loop() {
    Sensor sensor(S0, S1, S2, S3, OUT);
    sensor.reading();
    delay(500);
}