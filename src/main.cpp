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

Sensor sensor(S0, S1, S2, S3, OUT);

#define DAC_PIN 25

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
#define BOTtoken "7413577911:AAGfqrVmK7rowG6zBm0oddPdxTZmHwMx7w0"

Bot bot(WIFI_SSID,WIFI_PASSWORD,BOTtoken,BOT_MTBS);
TaskHandle_t TaskBot;

void taskBot(void * pvParameters)
{
    while (true)
    {
        //bot.waitMessage(nullptr);
        delay(100);
    }
    
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

    speaker.begin();
    speaker.setLanguage(lang);

    oled.begin();

    bot.setup();
    //xTaskCreatePinnedToCore(taskBot,   /* Task function. */"TaskBot",     /* name of task. */10000,       /* Stack size of task */NULL,        /* parameter of the task */1,           /* priority of the task */&TaskBot,      /* Task handle to keep track of created task */1);          /* pin task to core 1 */
}

void loop() {
    bot.waitMessage(nullptr);
    Color colorread = sensor.reading();
    oled.displayText(colorToString(colorread,lang));
    speaker.playColorSound(colorread);
    bot.set_color(colorToString(colorread,lang),lang);
    bot.game();
    delay(250);
}