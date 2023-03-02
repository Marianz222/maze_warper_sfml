#include "Boton.h"

Boton::Boton(string directorio_normal, string directorio_seleccion, float x, float y) {

	cursor_sobrepuesto = false;

	boton_textura_normal.loadFromFile(directorio_normal);
	boton_textura_seleccion.loadFromFile(directorio_seleccion);

	coordenadas.x = x;
	coordenadas.y = y;

	boton_sprite.setTexture(boton_textura_normal);
	boton_sprite.setPosition(coordenadas.x, coordenadas.y);

	boton_colisionador = new FloatRect(boton_sprite.getPosition(), (Vector2f)boton_sprite.getTexture()->getSize());

}

Sprite Boton::retornarSprite() {

	return boton_sprite;

}

FloatRect Boton::retornarColisionador() {

	return *boton_colisionador;

}

void Boton::intercambiarTexturas(bool normal) {

	if (normal) {

		boton_sprite.setTexture(boton_textura_normal);

	}
	else {

		boton_sprite.setTexture(boton_textura_seleccion);

	}

}
