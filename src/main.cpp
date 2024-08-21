#include "sensor.h"
#include "speaker.h"
#include <SPIFFS.h>
#include <AudioFileSourceSPIFFS.h>
#include <AudioGeneratorWAV.h>
#include <AudioOutputI2SNoDAC.h>


#include <Arduino.h>
#include <XT_DAC_Audio.h>

#define S0 25
#define S1 26
#define S2 27
#define S3 14
#define OUT 13
#define DAC_PIN 25

#define I2S_SPEAKER_SERIAL_CLOCK GPIO_NUM_4 // BCLK
#define I2S_SPEAKER_LEFT_RIGHT_CLOCK GPIO_NUM_5 // WSEL
#define I2S_SPEAKER_SERIAL_DATA GPIO_NUM_26

AudioGeneratorWAV *wav;
AudioFileSourceSPIFFS *file;
AudioOutputI2SNoDAC *out;

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
    
    if (!SPIFFS.begin(true)) {
    Serial.println("Erreur lors de l'initialisation de SPIFFS");
    return;
    }

    file = new AudioFileSourceSPIFFS("/portugues/amarelo.wav");
    out = new AudioOutputI2SNoDAC();
    out->SetPinout(I2S_SPEAKER_SERIAL_CLOCK, I2S_SPEAKER_LEFT_RIGHT_CLOCK, I2S_SPEAKER_SERIAL_DATA);
    wav = new AudioGeneratorWAV();
    wav->begin(file, out);
    
    
    Serial.begin(115200);
}

void loop() {
    if (wav->isRunning()) {
        if (wav->loop()) {
        // Le fichier WAV est toujours en lecture
        } else {
            Serial.println("Lecture du fichier WAV terminée.");
            wav->stop();
            file->close();
        }
  }
   
}