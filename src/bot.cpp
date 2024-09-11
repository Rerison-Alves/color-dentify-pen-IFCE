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

        while (numNewMessages)
        {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = _bot.getUpdates(_bot.last_message_received + 1);
        }

        _bot_lasttime = millis();
    } 
}

void Bot::handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
   
    if(_bot.messages[i].text=="play"){
        _bot.sendMessage(_bot.messages[i].chat_id, "Que os jogos começem!!!");
        _bot.sendMessage(_bot.messages[i].chat_id, "Antes de comerçarmos a brincadeira preciso te dá uma dica:");
       
        redGame(i);
        purpleGame(i);
        blueGame(i);
        if(_lang==Language::PORTUGUESE){
            _bot.sendMessage(_bot.messages[i].chat_id, "Meus parabens, vc conseguiu finalizar o meu jogo!!!!!");
        }else{
            _bot.sendMessage(_bot.messages[i].chat_id, "You rock! You beat my game!!!!!");
        }
       
    }
    
  }
}

boolean Bot::vermelho(int chat_id)
{
    if(_color_read=="vermelho"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Parabens!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "vc acertou a cor");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Agora vamos para a proxima cor");
        _color_read = nullptr;
        return false;
    }else{
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Sinto muito");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Essa não é a cor que estou pensando");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "não desista!!! continue tentando");
        _color_read = nullptr;
        return true;
    }
}
boolean Bot::red(int chat_id)
{
    if(_color_read=="red"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Congratulations!!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "That's exactly the color I was thinking of! ");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Next, let's try another color.");
        _color_read = nullptr;
        return false;
    }else{
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "I'm so sorry.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "I had a different color in mind.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Keep going! You can do it!!!");
        _color_read = nullptr;
        return true;
    }
}

boolean Bot::roxo(int chat_id)
{
    if(_color_read=="roxo"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Parabens!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "vc acertou a cor.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Agora vamos para a proxima cor.");
        _color_read = nullptr;
        return false;
    }else{
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Sinto muito");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Essa não é a cor que estou pensando");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "não desista!!! continue tentando");
        _color_read = nullptr;
        return true;
    }
}
boolean Bot::purple(int chat_id)
{
    if(_color_read=="purple"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Congratulations!!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "That's exactly the color I was thinking of! ");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Next, let's try another color.");
        _color_read = nullptr;
        return false;
    }else{
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "I'm so sorry.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "I had a different color in mind.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Keep going! You can do it!!!");
        _color_read = nullptr;
        return true;
    }
}

boolean Bot::azul(int chat_id)
{
    if(_color_read=="azul"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Parabens!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "vc acertou a cor");
        _color_read = nullptr;
        return false;
    }else{
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Sinto muito");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Essa não é a cor que estou pensando");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "não desista!!! continue tentando");
        _color_read = nullptr;
        return true;
    }
}
boolean Bot::blue(int chat_id)
{
    if(_color_read=="blue"){
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Congratulations!!!!!!!");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "That's exactly the color I was thinking of! ");
        return false;
    }else{
         _bot.sendMessage(_bot.messages[chat_id].chat_id, "I'm so sorry.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "I had a different color in mind.");
        _bot.sendMessage(_bot.messages[chat_id].chat_id, "Keep going! You can do it!!!");
        return true;
    }
}

void Bot::redGame(int chat_id)
{
    bool cor_errada = true;
    _color_read = nullptr;
    
    while(cor_errada)
    {
        
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente é comum em frutas e flores");
            cor_errada=vermelho(chat_id);    
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "The color I'm visualizing is typical of many fruits and blooms.");
            cor_errada=red(chat_id);
        }
    }
    
}


void Bot::purpleGame(int chat_id)
{
    bool cor_errada = true;
    _color_read = nullptr;

    while(cor_errada)
    {
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente é muito bonita mas raramente encontrada na naturaza");
            cor_errada=roxo(chat_id);
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "The color I have in mind is a beautiful shade, but it's not often seen in nature.");
            cor_errada=purple(chat_id);
        }
    }

}

void Bot::blueGame(int chat_id)
{
    bool cor_errada = true;
    _color_read = nullptr;

    while(cor_errada)
    {
        if(_lang==Language::PORTUGUESE){
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "A cor que eu tenho em mente está no lemento base da vida.");
            cor_errada=azul(chat_id);
        }else{
            if(_color_read==nullptr){
                delay(10);
                continue;
            }
            _bot.sendMessage(_bot.messages[chat_id].chat_id, "The color I'm thinking of is present in the fundamental element of life.");
            cor_errada=blue(chat_id);
        }
    }

}

