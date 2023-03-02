#pragma once

//Inclusión de librerias
#include <SFML/Graphics.hpp>

using namespace sf;

class Celda {

private:

	bool renderizar;
	Texture celda_textura;
	Sprite celda_sprite;
	Vector2f coordenadas;
	FloatRect* celda_colisionador;

public:

	Celda(float x, float y);
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	bool debeRenderizarse();
	void cambiarRender(bool estado);

};

