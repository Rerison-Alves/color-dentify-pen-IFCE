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
    greenColor = map(greenFrequency, 50, 100, 255, 0);

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
    blueColor = map(blueFrequency, 45, 95, 255, 0);

    // Printing the BLUE (B) value
    Serial.print(" B = ");
    Serial.print(blueColor);
    delay(10);

    // Checks the current detected color and prints
    // a message in the serial monitor

    if (redColor < 80 && greenColor < 80 && blueColor < 80) {
        Serial.println(" - PRETO detectado!");
        return Color::BLACK;
    }

    if (redColor > 380 && greenColor > 380 && blueColor > 380) {
        Serial.println(" - BRANCO detectado!");
        return Color::WHITE;
    }

    if (abs(redColor - greenColor) < DIFF_THRESHOLD && abs(redColor - blueColor) < DIFF_THRESHOLD && abs(greenColor - blueColor) < DIFF_THRESHOLD) {
        Serial.println(" - CINZA detectado!");
        return Color::GREY;
    }

    if (redColor > greenColor && redColor > blueColor) {
        // Red is the predominant color
        if (abs(greenColor - redColor) < DIFF_THRESHOLD) {
            Serial.println(" - YELLOW detected!");
            return Color::YELLOW;
        } else if (abs(greenColor - redColor) < DIFF_THRESHOLD*2) {
            Serial.println(" - ORANGE detected!");
            return Color::ORANGE;
        }else if (abs(blueColor - redColor) < DIFF_THRESHOLD*2) {
            Serial.println(" - PINK detected!");
            return Color::PINK;
        } else {
            Serial.println(" - RED detected!");
            return Color::RED;
        }
    } else if (blueColor > redColor && blueColor > greenColor) {
        // Blue is the predominant color
        if (abs(blueColor - greenColor) < DIFF_THRESHOLD) {
            Serial.println(" - CYAN detected!");
            return Color::CYAN;
        } else if (abs(blueColor - redColor) < DIFF_THRESHOLD*2.5) {
            Serial.println(" - PURPLE detected!");
            return Color::PURPLE;
        }else {
            Serial.println(" - BLUE detected!");
            return Color::BLUE;
        }
    } else if (greenColor > redColor && greenColor > blueColor) {
        // Green is the predominant color
        if (abs(redColor - greenColor) < DIFF_THRESHOLD) {
            Serial.println(" - YELLOW detected!");
            return Color::YELLOW;
        } else if (abs(blueColor - greenColor) < DIFF_THRESHOLD*0.6) {
            Serial.println(" - CYAN detected!");
            return Color::CYAN;
        }else {
            Serial.println(" - GREEN detected!");
            return Color::GREEN;
        }
    } else {
        Serial.println(" - INVALID COLOR detected!");
        return Color::INVALID;
    }
}