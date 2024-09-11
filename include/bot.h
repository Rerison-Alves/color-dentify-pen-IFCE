#ifndef BOT_H
#define BOT_H
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "language.h" 

class Bot {
public:
    Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs);
    void setup();
    void waitMessage(void * pvParameters);
    void handleNewMessages(int numNewMessages);
    void set_color(const char* color);
    void set_color(const char* color, Language lang);
    void redGame(int chat_id);
    void purpleGame(int chat_id);
    void blueGame(int chat_id);
    boolean vermelho(int chat_id);
    boolean red(int chat_id);
    boolean roxo(int chat_id);
    boolean purple(int chat_id);
    boolean azul(int chat_id);
    boolean blue(int chat_id);

private:
    const char* _wifi_ssid;
    const char* _wifi_password;
    const char* _botoken;
    unsigned long _bot_lasttime; 
    const unsigned long _bot_mtbs;
    const char* _color_read;
    Language _lang;
    WiFiClientSecure _secured_client;
    UniversalTelegramBot _bot;
};








#endif