#ifndef SPEAKER_H
#define SPEAKER_H

#include <FS.h>
#include <SPIFFS.h>
#include "colors.h"
#include "language.h"

class Speaker {
public:
    Speaker(uint8_t dacPin, float timbreFactor = 1.0, float volumeFactor = 1.0);
    void begin();
    void setLanguage(Language language);
    void playColorSound(Color color);

private:
    uint8_t _dacPin;
    float _timbreFactor;
    float _volumeFactor;
    Language _language;
    const char* getFilePath(Color color);
    void playAudio(const char* filePath);
};

#endif // SPEAKER_H
