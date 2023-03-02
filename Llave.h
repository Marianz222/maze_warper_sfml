#pragma once

//Inclusión de librerias
#include <SFML/Graphics.hpp>

using namespace sf;

class Llave {

private:

	bool renderizar;
	Texture llave_textura;
	Sprite llave_sprite;
	Vector2f coordenadas;
	FloatRect* llave_colisionador;

public:

	Llave(float x, float y);
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	bool debeRenderizarse();
	void cambiarRender(bool estado);

};
