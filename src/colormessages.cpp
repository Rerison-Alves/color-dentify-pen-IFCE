#include "colormessages.h"
#include <cstring>

const char* getCongratulationsMessage(Language lang) {
    if (lang == Language::PORTUGUESE) {
        return "Parabens!!!!!! \nvc acertou a cor \nAgora vamos para a proxima cor";
    } else {
        return "Congratulations!!!!!! \nYou got the color right \nNow let's move to the next color";
    }
}


const char* getColorHint(const char* color, Language lang) {
    if (lang == Language::PORTUGUESE) {
        if(color == "vermelho"){
            return "A cor que eu tenho em mente é comum em frutas e flores";
        }else if(color == "roxo"){
            return "A cor que eu tenho em mente é muito bonita mas raramente encontrada na natureza";
        }else if(color == "azul"){
            return "A cor que eu tenho em mente está no elemento base da vida.";
        }else if(color == "preto"){
            return "É uma cor comum aos mais variados tipos de animais.";
        }else if(color == "branco"){
            return "é uma cor que tudo reflete.";
        }else if(color == "cinza"){
            return "qunado se mistura mistura uma cor que tudo reflete e uma cor que tudo absorve, vc o acha .";
        }else if(color == "amarelo"){
            return "é uma das cores de um animal que produz doce.";
        }else if(color == "ciano"){
            return "É uma cor secundária, resultado da mistura de azul e verde.";
        }else if(color == "laranja"){
            return "quem veio primeiro, a fruta ou a cor?.";
        }else if(color == "rosa"){
            return "a cor faz parte do nome de um ser muito famoso do folclore brasileiro.";
        }else if(color == "verde"){
            return "representação da natureza.";
        }else{
            return "Cor não reconhecida";
        }
    } else {
        if(color == "red"){
            return "The color I'm thinking of is common in fruits and flowers.";
        }else if(color == "purple"){
            return "The color I'm thinking of is very beautiful but rarely found in nature.";
        }else if(color == "blue"){
            return "The color I'm thinking of is in the basic element of life.";
        }else if(color == "black"){
            return "It's a color that swallows all light.";
        }else if(color == "white"){
            return "It's a color that reflects all light.";
        }else if(color == "grey"){
            return "When mixing a color that reflects all light with a color that absorbs all light, the color is created";
        }else if(color == "yellow"){
            return "It's a color found on a creature that produce sweetness.";
        }else if(color == "cyan"){
            return "It's the color you get when you mix blue and green.";
        }else if(color == "orange"){
            return "Which came first, the fruit or the color?";
        }else if(color == "pink"){
            return "The color is a key part of the name of a legendary Brazilian folklore figure.";
        }else if(color == "green"){
            return "Representation of nature.";
        }else{
            return "Invalid color";
        }
    }
    return nullptr;
}