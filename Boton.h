#pragma once

#include <SFML/Graphics.hpp>

#include <cstdlib>

using namespace std;
using namespace sf;

class Boton {

private:

	Texture boton_textura_normal;
	Texture boton_textura_seleccion;
	bool cursor_sobrepuesto;
	Sprite boton_sprite;
	Vector2f coordenadas;
	FloatRect* boton_colisionador;

public:

	Boton(string directorio_normal, string directorio_seleccion, float x, float y);
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	void intercambiarTexturas(bool normal);

};

