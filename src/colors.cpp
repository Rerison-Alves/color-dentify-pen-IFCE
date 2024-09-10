#include "colors.h"

// Função para converter um enum Color para uma string de cor, considerando o idioma
const char* colorToString(Color color, Language language) {
    if (language == Language::PORTUGUESE) {
        switch (color) {
            case Color::BLACK: return "preto";
            case Color::WHITE: return "branco";
            case Color::GREY: return "cinza";
            case Color::YELLOW: return "amarelo";
            case Color::BLUE: return "azul";
            case Color::ORANGE: return "laranja";
            case Color::PINK: return "rosa";
            case Color::PURPLE: return "roxo";
            case Color::GREEN: return "verde";
            case Color::RED: return "vermelho";
            default: return "invalido";
        }
    } else if (language == Language::ENGLISH) {
        switch (color) {
            case Color::BLACK: return "black";
            case Color::WHITE: return "white";
            case Color::GREY: return "grey";
            case Color::YELLOW: return "yellow";
            case Color::BLUE: return "blue";
            case Color::ORANGE: return "orange";
            case Color::PINK: return "pink";
            case Color::PURPLE: return "purple";
            case Color::GREEN: return "green";
            case Color::RED: return "red";
            default: return "invalid";
        }
    }
    return "invalid";
}
