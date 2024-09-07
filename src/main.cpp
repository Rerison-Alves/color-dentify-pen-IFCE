#include <Arduino.h>
#include "speaker.h"
#include "sensor.h"
#include "oled.h"
#include "bot.h"

#define S0 4
#define S1 5
#define S2 18
#define S3 19
#define OUT 23
#define DAC_PIN 25

Sensor sensor(S0, S1, S2, S3, OUT);
Speaker speaker(DAC_PIN, 2.0, 15); // DacPin, TimbreFactor, VolumeFactor
Language lang(Language::PORTUGUESE);

//Definindo tela oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SDA_PIN 21
#define SCK_PIN 22

OledDisplay oled(SCREEN_WIDTH, SCREEN_HEIGHT, SDA_PIN, SCK_PIN);

//Definindo o bot
const char* WIFI_SSID = "S20";
const char* WIFI_PASSWORD = "kust8362";
const unsigned long BOT_MTBS = 1000;
#define BOTtoken "7528571819:AAHvQSn3wAFr7nv_YvQMbes745q_RdBX_1o"

Bot bot(WIFI_SSID,WIFI_PASSWORD,BOTtoken,BOT_MTBS);


void playColorSoundTask(Color detectedColor) {
    speaker.playColorSound(detectedColor);// Reproduz o som da cor detectada
    vTaskDelete(NULL);  // Deleta a task após execução
}

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


    //speaker.begin();
    //speaker.setLanguage(lang);

    //oled.begin();

    bot.setup();
}

void loop() {
    //Color colorread = sensor.reading();
    //oled.displayText(colorToString(colorread,lang));
    //speaker.playColorSound(colorread);
    bot.waitMessage(nullptr);
    delay(500);
}