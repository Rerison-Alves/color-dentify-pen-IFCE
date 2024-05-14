
#include <iostream>
#include <string>
#include <Arduino.h>


class Sensor {
private:
    // Stores the red. green and blue colors
    int redColor, greenColor, blueColor;

    // Stores the red. green and blue colors
    int redFrequency, greenFrequency, blueFrequency;

    // pins
    int S0, S1, S2, S3, OUT;
    
    
public:
    Sensor(int pin_S0, int pin_S1, int pin_S2, int pin_S3, int pin_OUT){
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

    void reading(){
        // Setting RED (R) filtered photodiodes to be read
        digitalWrite(S2,LOW);
        digitalWrite(S3,LOW);

        // Reading the output frequency
        redFrequency = pulseIn(OUT, LOW);
        // Remaping the value of the RED (R) frequency from 0 to 255
        // You must replace with your own values. Here's an example:
        // redColor = map(redFrequency, 70, 120, 255,0);
        redColor = map(redFrequency, 70, 120, 255,0);

        // Printing the RED (R) value
        Serial.print("R = ");
        Serial.print(redColor);
        delay(10);

        // Setting GREEN (G) filtered photodiodes to be read
        digitalWrite(S2,HIGH);
        digitalWrite(S3,HIGH);

        // Reading the output frequency
        greenFrequency = pulseIn(OUT, LOW);
        // Remaping the value of the GREEN (G) frequency from 0 to 255
        // You must replace with your own values. Here's an example:
        // greenColor = map(greenFrequency, 100, 199, 255, 0);
        greenColor = map(greenFrequency, 50, 150, 255, 0);

        // Printing the GREEN (G) value
        Serial.print(" G = ");
        Serial.print(greenColor);
        delay(10);

        // Setting BLUE (B) filtered photodiodes to be read
        digitalWrite(S2,LOW);
        digitalWrite(S3,HIGH);

        // Reading the output frequency
        blueFrequency = pulseIn(OUT, LOW);
        // Remaping the value of the BLUE (B) frequency from 0 to 255
        // You must replace with your own values. Here's an example:
        // blueColor = map(blueFrequency, 38, 84, 255, 0);
        blueColor = map(blueFrequency, 50, 105, 255, 0);

        // Printing the BLUE (B) value
        Serial.print(" B = ");
        Serial.print(blueColor);
        delay(10);

        // Checks the current detected color and prints
        // a message in the serial monitor
        if(redColor > greenColor && redColor > blueColor){
            Serial.println(" - RED detected!");
        }
        if(greenColor > redColor && greenColor > blueColor){
            Serial.println(" - GREEN detected!");
        }
        if(blueColor > redColor && blueColor > greenColor){
            Serial.println(" - BLUE detected!");
        }
        delay(500);
    }
};

