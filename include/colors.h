#ifndef COLORS_H
#define COLORS_H

#include "language.h"

// Enum de cores em inglês com valores específicos
enum class Color {
    BLACK = 0,
    WHITE = 1,
    GREY = 2,
    YELLOW = 3,
    BLUE = 4,
    CYAN = 5,
    ORANGE = 6,
    PINK = 7,
    PURPLE = 8,
    GREEN = 9,
    RED = 10,
    INVALID = -1 // Usado para representar uma cor inválida
};

// Função para converter um enum Color para uma string de cor, considerando o idioma
const char* colorToString(Color color, Language language);

#endif // COLORS_H
