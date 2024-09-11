#ifndef COLORS_H
#define COLORS_H

#include "language.h"

// Enum de cores em inglês
enum class Color {
    BLACK,
    WHITE,
    GREY,
    YELLOW,
    BLUE,
    CYAN,
    ORANGE,
    PINK,
    PURPLE,
    GREEN,
    RED,
    INVALID // Usado para representar uma cor inválida
};

// Função para converter um enum Color para uma string de cor, considerando o idioma
const char* colorToString(Color color, Language language);

#endif // COLORS_H
