#ifndef BOT_H
#define BOT_H
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "language.h" 
#include "colormessages.h"
#include "colors.h"


class Bot {
public:
    Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs);
    void setup();
    void waitMessage(void * pvParameters);
    void game();
    void set_color(const char* color, Language lang);
    boolean colorGame();

private:
    const char* _wifi_ssid;
    const char* _wifi_password;
    const char* _botoken;
    unsigned long _bot_lasttime; 
    const unsigned long _bot_mtbs;
    const char* _color_read;
    const char* _expected_color;
    int _numNewMessages;
    boolean _novaMenssagem;
    int _roll;
    Language _lang;
    WiFiClientSecure _secured_client;
    UniversalTelegramBot _bot;
};








#endif