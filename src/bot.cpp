#include <Arduino.h>
#include <String.h>
#include <cstdlib>
#include <ctime>
#include "bot.h"

Bot::Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs): 
        _wifi_ssid(wifi_ssid), _wifi_password(wifi_password), _botoken(botoken), _bot_lasttime(), _bot_mtbs(bot_mtbs), _color_read(nullptr),
        _expected_color(nullptr), _numNewMessages(),_novaMenssagem(true),_roll(1),
        _lang(), _secured_client(), _bot(_botoken, _secured_client) {}


void Bot::setup()
{
    Serial.print("Connecting to Wifi SSID ");
    Serial.print(_wifi_ssid);
    WiFi.begin(_wifi_ssid, _wifi_password);
    _secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.print("\nWiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Retrieving time: ");
    configTime(0, 0, "pool.ntp.org"); 
    time_t now = time(nullptr);
    while (now < 24 * 3600)
    {
        Serial.print(".");
        delay(100);
        now = time(nullptr);
    }
    Serial.println(now);
    srand(time(0));

}

void Bot::set_color(const char* color, Language lang)
{
    _color_read = color;
    _lang = lang;
}

void Bot::waitMessage(void * pvParameters)
{
    if ((millis() - _bot_lasttime > _bot_mtbs)&&_novaMenssagem)
    {
        int numNewMessages = _bot.getUpdates(_bot.last_message_received+1);

        
        if(_bot.messages[numNewMessages].text=="play"||_bot.messages[numNewMessages].text=="Play"){
            Serial.println("got response play");
            _novaMenssagem = false;
            _numNewMessages = numNewMessages; 
            int randomColor = rand() % 11;
            Color color = static_cast<Color>(randomColor);
            _expected_color=colorToString(color,_lang);
            _bot.sendMessage(_bot.messages[_numNewMessages].chat_id, "Em que cor to pensando? \ 
            dica da cor:");
            const char* hint = getColorHint(_expected_color,_lang);
            if (hint) {
                _bot.sendMessage(_bot.messages[_numNewMessages].chat_id, hint);
            }
            _roll = _roll+1;
        }else if(_bot.messages[numNewMessages].text=="over"||_bot.messages[numNewMessages].text=="Over"){
            Serial.println("got response over");
            _numNewMessages = numNewMessages;
            _expected_color=nullptr;
            
        }
        
        _bot_lasttime = millis();
    } 
}

void Bot::game()
{
    if(_expected_color!=nullptr){
        bool cor_certa=colorGame();
        if(cor_certa==true || _bot.messages[_numNewMessages].text=="over"||_bot.messages[_numNewMessages].text=="Over"){
            _expected_color = nullptr;
            _novaMenssagem = true;
        }
        delay(2000);
    }
    
  
}

boolean Bot::colorGame() {
    if (_color_read && strcmp(_color_read, _expected_color) == 0) {
        const char* congratilations = getCongratulationsMessage(_lang);
        _bot.sendMessage(_bot.messages[_numNewMessages].chat_id, congratilations);
        
        return true;
    }
    return false;  
}

