#include <Arduino.h>
#include "speaker.h"
#include "sensor.h"
#include "oled.h"
#include "bot.h"

//Definindo o botao
#define BUTTON 14

volatile bool buttonPressed = false;

//Definindo o sensor
#define S0 4
#define S1 5
#define S2 18
#define S3 19
#define OUT 23

Sensor sensor(S0, S1, S2, S3, OUT);

//Definindo o speaker
#define DAC_PIN 25

Speaker speaker(DAC_PIN, 2.0, 15); // DacPin, TimbreFactor, VolumeFactor
Language lang(Language::PORTUGUESE);

//Definindo a tela oled
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

void toggleLanguage() {
    if (lang == Language::PORTUGUESE) {
        lang = Language::ENGLISH;
        Serial.println("Language changed to English");
        oled.displayText("Lang: \nEnglish");
    } else {
        lang = Language::PORTUGUESE;
        Serial.println("Idioma alterado para Português");
        oled.displayText("Lang: \nPortuguese");
    }
    speaker.setLanguage(lang);
    delay(3000);
}

void IRAM_ATTR handleButtonPress() {
    // Define que o botão foi pressionado, controlando com debounce
    buttonPressed = true;
}

void setup() {
  // Begins serial communication
    Serial.begin(115200);

    pinMode(BUTTON, INPUT);
  
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

    //bot.setup();

    attachInterrupt(digitalPinToInterrupt(BUTTON), handleButtonPress, FALLING);
}

void loop() {
    //bot.waitMessage(nullptr);
    Color colorread = sensor.reading();
    oled.displayText(colorToString(colorread,lang));
    speaker.playColorSound(colorread);
    //bot.set_color(colorToString(colorread,lang),lang);
    //bot.game();
    if (buttonPressed) {
        toggleLanguage();
        buttonPressed = false;
    }
    delay(250);
}