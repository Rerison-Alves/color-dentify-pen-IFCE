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