#include <Arduino.h>
#include <String.h>
#include "bot.h"

Bot::Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs): 
        _wifi_ssid(wifi_ssid), _wifi_password(wifi_password), _botoken(botoken), _bot_lasttime(), _bot_mtbs(bot_mtbs), _color_read(nullptr), 
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

}

void Bot::set_color(const char* color, Language lang)
{
    _color_read = color;
    _lang = lang;
}

void Bot::waitMessage(void * pvParameters)
{
    if (millis() - _bot_lasttime > _bot_mtbs)
    {
        int numNewMessages = _bot.getUpdates(_bot.last_message_received + 1);

        Serial.println("got response");
        handleNewMessages(numNewMessages);
        
        

        _bot_lasttime = millis();
    } 
}

void Bot::handleNewMessages(int numNewMessages)
{
  
   
    if(_bot.messages[numNewMessages].text=="play"){

        _bot.sendMessage(_bot.messages[numNewMessages].chat_id, "Que os jogos começem!!! \ 
        Antes de comerçarmos a brincadeira preciso te dá uma dica:");
       
        redGame(numNewMessages);
        purpleGame(numNewMessages);
        blueGame(numNewMessages);
        if(_lang==Language::PORTUGUESE){
            _bot.sendMessage(_bot.messages[numNewMessages].chat_id, "Meus parabens, vc conseguiu finalizar o meu jogo!!!!!");
        }else{
            _bot.sendMessage(_bot.messages[numNewMessages].chat_id, "You rock! You beat my game!!!!!");
        }
       
    }
    
  
}

boolean Bot::vermelho(int chat_id)
{
    if(_color_read=="vermelho"){
        const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        _color_read = nullptr;
        return false;
    }
    return true;
}
boolean Bot::red(int chat_id)
{
    if(_color_read=="red"){
        const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        _color_read = nullptr;
        return false;
    }
    return true;
}

boolean Bot::roxo(int chat_id)
{
    if(_color_read=="roxo"){
        const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        _color_read = nullptr;
        return false;
    }
    return true;
}
boolean Bot::purple(int chat_id)
{
    if(_color_read=="purple"){
       const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        _color_read = nullptr;
        return false;
    }
    return true;
}

boolean Bot::azul(int chat_id)
{
    if(_color_read=="azul"){
       const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        _color_read = nullptr;
        return false;
    }
    return true;
}
boolean Bot::blue(int chat_id)
{
    if(_color_read=="blue"){
       const char *congratilations = 
        "Parabens!!!!!! \ 
        vc acertou a cor \ 
        Agora vamos para a proxima cor";
        _bot.sendMessage(_bot.messages[chat_id].chat_id, congratilations);
        return false;
    }
    return true;
}

void Bot::redGame(int chat_id)
{
    bool cor_errada = true;
    _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente é comum em frutas e flores");
    
    while(cor_errada)
    {
        const char* last_color = _color_read;
        
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=vermelho(chat_id); 
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=red(chat_id);
            
        }
    }
    
}


void Bot::purpleGame(int chat_id)
{
    bool cor_errada = true;
    _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente é muito bonita mas raramente encontrada na naturaza");

    while(cor_errada) 
    {
        const char* last_color = _color_read;
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=roxo(chat_id);
            
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=purple(chat_id);
            
        }
    }

}

void Bot::blueGame(int chat_id)
{
    bool cor_errada = true;
    _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente está no lemento base da vida.");
    while(cor_errada)
    {
        const char* last_color = _color_read;
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=azul(chat_id);
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            cor_errada=blue(chat_id);
        }
    }

}

