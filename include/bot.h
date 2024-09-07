#ifndef BOT_H
#define BOT_H
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class Bot {
public:
    Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs);
    void setup();
    void waitMessage(void * pvParameters);
    void handleNewMessages(int numNewMessages);

private:
    const char* _wifi_ssid;
    const char* _wifi_password;
    const char* _botoken;
    unsigned long _bot_lasttime; 
    const unsigned long _bot_mtbs;
    WiFiClientSecure _secured_client;
    UniversalTelegramBot _bot;
};








#endif