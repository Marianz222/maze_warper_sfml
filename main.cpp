//Inclusión de librerias
#include <iostream>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Juego.h"

using namespace std;
using namespace sf;

int main() {

    //Crea el objeto de juego principal para entrar en el bucle y comenzar
    Juego juego;
    juego.buclePrincipal();

    return 0;

}