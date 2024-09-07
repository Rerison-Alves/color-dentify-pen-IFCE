#include <Arduino.h>
#include "bot.h"

Bot::Bot(const char* wifi_ssid, const char* wifi_password, const char* botoken, const unsigned long bot_mtbs): 
        _wifi_ssid(wifi_ssid), _wifi_password(wifi_password), _botoken(botoken), _bot_lasttime(), _bot_mtbs(bot_mtbs), 
        _secured_client(), _bot(_botoken, _secured_client) {}


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

void Bot::waitMessage(void * pvParameters)
{
    while(true){

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
        delay(10);
    }
}

void Bot::handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    if (_bot.messages[i].type == "channel_post")
    {
      _bot.sendMessage(_bot.messages[i].chat_id, _bot.messages[i].chat_title + " " + _bot.messages[i].text, "");
    }
    else
    {
      _bot.sendMessage(_bot.messages[i].chat_id, _bot.messages[i].text, "");
    }
  }
}

