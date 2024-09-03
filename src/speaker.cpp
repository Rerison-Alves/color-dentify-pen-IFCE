#include "speaker.h"
#include <Arduino.h>

#define ORIGINAL_SAMPLE_RATE 16000

Speaker::Speaker(uint8_t dacPin, float timbreFactor, float volumeFactor)
        : _dacPin(dacPin), _timbreFactor(timbreFactor), _volumeFactor(volumeFactor), _language(Language::ENGLISH) {}

void Speaker::begin() {
    if (!SPIFFS.begin(true)) {
        Serial.println("Falha ao montar o sistema de arquivos.");
    }

    ledcSetup(0, ORIGINAL_SAMPLE_RATE * _timbreFactor, 8);
    ledcAttachPin(_dacPin, 0);
}

void Speaker::setLanguage(Language language) {
    _language = language;
}

void Speaker::playColorSound(Color color) {
    const char* filePath = getFilePath(color);
    if (filePath != nullptr) {
        playAudio(filePath);
    } else {
        Serial.println("Cor inválida!");
    }
}

const char* Speaker::getFilePath(Color color) {
    static String filePath;
    const char* colorStr = colorToString(color, _language);

    if (_language == Language::PORTUGUESE) {
        if (strcmp(colorStr, "invalido") == 0) return nullptr;
        filePath = "/portugues/" + String(colorStr) + ".wav";
    } else if (_language == Language::ENGLISH) {
        if (strcmp(colorStr, "invalid") == 0) return nullptr;
        filePath = "/ingles/" + String(colorStr) + ".wav";
    } else {
        return nullptr;
    }

    return filePath.c_str();
}

void Speaker::playAudio(const char* filePath) {
    File file = SPIFFS.open(filePath, "r");
    if (!file) {
        Serial.println("Falha ao abrir o arquivo.");
        return;
    }

    file.seek(44); // Pula o cabeçalho WAV

    while (file.available()) {
        int16_t sample = file.read() | (file.read() << 8);

        // Amplifica e clampeia o valor do sample diretamente
        uint8_t dacValue = constrain((sample * _volumeFactor) / 256, 0, 255);

        // Escreve o valor no DAC
        ledcWrite(0, dacValue);

        // Aguarda até o próximo sample
        delayMicroseconds(1000000 / (ORIGINAL_SAMPLE_RATE * _timbreFactor));
    }
    delay(200);

    file.close();
}
