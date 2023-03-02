#include "Celda.h"

Celda::Celda(float x, float y) {

	renderizar = true;

	celda_textura.loadFromFile("assets/images/celda.png");
	celda_sprite.setTexture(celda_textura);

	coordenadas.x = x;
	coordenadas.y = y;

	celda_sprite.setPosition(coordenadas.x, coordenadas.y);
	celda_sprite.setOrigin(celda_sprite.getGlobalBounds().width / 2, celda_sprite.getGlobalBounds().height);

	celda_colisionador = new FloatRect(celda_sprite.getPosition(), (Vector2f)celda_sprite.getTexture()->getSize());

}

//Devuelve el sprite del objeto
Sprite Celda::retornarSprite() {

	return celda_sprite;

}

//Devuelve el colisionador del objeto, usado para colisiones
FloatRect Celda::retornarColisionador() {

	return *celda_colisionador;

}

//Determina si el objeto debe o no ser renderizado en la ventana
bool Celda::debeRenderizarse() {

	return renderizar;

}

//Establece si el objeto deberá renderizarse o no mediante un bool
void Celda::cambiarRender(bool estado) {

	renderizar = estado;

}