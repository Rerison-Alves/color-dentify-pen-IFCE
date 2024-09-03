#include "sensor.h"
#include <Arduino.h>

Sensor::Sensor(int pin_S0, int pin_S1, int pin_S2, int pin_S3, int pin_OUT) {
    // set pins
    S0 = pin_S0;
    S1 = pin_S1;
    S2 = pin_S2;
    S3 = pin_S3;
    OUT = pin_OUT;

    // set colors
    redColor = 0;
    greenColor = 0;
    blueColor = 0;

    // set frequencies
    redFrequency = 0;
    greenFrequency = 0;
    blueFrequency = 0;
}

Color Sensor::reading() {
    // Setting RED (R) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);

    // Reading the output frequency
    redFrequency = pulseIn(OUT, LOW);
    // Remaping the value of the RED (R) frequency from 0 to 255
    redColor = map(redFrequency, 50, 100, 255, 0);

    // Printing the RED (R) value
    Serial.print("R = ");
    Serial.print(redColor);
    delay(10);

    // Setting GREEN (G) filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);

    // Reading the output frequency
    greenFrequency = pulseIn(OUT, LOW);
    // Remaping the value of the GREEN (G) frequency from 0 to 255
    greenColor = map(greenFrequency, 50, 170, 255, 0);

    // Printing the GREEN (G) value
    Serial.print(" G = ");
    Serial.print(greenColor);
    delay(10);

    // Setting BLUE (B) filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);

    // Reading the output frequency
    blueFrequency = pulseIn(OUT, LOW);
    // Remaping the value of the BLUE (B) frequency from 0 to 255
    blueColor = map(blueFrequency, 50, 105, 255, 0);

    // Printing the BLUE (B) value
    Serial.print(" B = ");
    Serial.print(blueColor);
    delay(10);

    // Checks the current detected color and prints
    // a message in the serial monitor
    if (redColor > greenColor && redColor > blueColor) {
        if (greenColor > blueColor) {
            if (redColor - greenColor < 20) {
                Serial.println(" - LARANJA detectado!");
                return Color::ORANGE;
            }
            Serial.println(" - VERMELHO detectado!");
            return Color::RED;
        } else {
            Serial.println(" - ROSA detectado!");
            return Color::PINK;
        }
    }
    if (greenColor > redColor && greenColor > blueColor) {
        if (blueColor > redColor) {
            if (greenColor - blueColor < 20) {
                Serial.println(" - VERDE detectado!");
                return Color::GREEN;
            }
            Serial.println(" - AMARELO detectado!");
            return Color::YELLOW;
        } else {
            Serial.println(" - VERDE detectado!");
            return Color::GREEN;
        }
    }
    if (blueColor > redColor && blueColor > greenColor) {
        if (redColor > greenColor) {
            Serial.println(" - ROXO detectado!");
            return Color::PURPLE;
        } else {
            Serial.println(" - AZUL detectado!");
            return Color::BLUE;
        }
    }

    Serial.println("Nenhuma cor foi detectada!");
    return Color::INVALID;
}