#pragma once

//Inclusión de librerias
#include <SFML/Graphics.hpp>

using namespace sf;

class Portal {

private:

	Texture portal_activo_textura;
	Texture portal_inactivo_textura;

	Sprite portal_sprite;
	Vector2f coordenadas;
	bool esta_activo;
	FloatRect* portal_colisionador;

public:

	Portal(float x, float y, bool activo);
	void cambiarEstado(bool nuevo_estado);
	bool retornarEstado();
	Sprite retornarSprite();
	FloatRect retornarColisionador();
	void actualizarTexturas();

};

