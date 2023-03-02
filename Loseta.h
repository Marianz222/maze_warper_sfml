#pragma once

//Inclusión de librerias
#include <SFML/Graphics.hpp>

using namespace sf;

class Loseta {

private:

	bool renderizar;
	Texture loseta_base;
	Texture loseta_luminosa;
	Texture loseta_bloqueada;
	Texture loseta_limitante;
	Texture loseta_fondo;

	Vector2f coordenadas;
	Texture loseta_textura;
	Sprite loseta_sprite;
	int estado;

public:

	Loseta(float x, float y, int nuevo_estado);
	Sprite retornarSprite();
	int retornarEstado();
	Vector2f retornarPosicion();
	FloatRect retornarColisionador();
	bool debeRenderizarse();
	void cambiarRender(bool estado);

};