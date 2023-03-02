#include "Portal.h"

//Constructor de la clase
Portal::Portal(float x, float y, bool activo) {

	portal_activo_textura.loadFromFile("assets/images/portal_activo.png");
	portal_inactivo_textura.loadFromFile("assets/images/portal_inactivo.png");

	coordenadas.x = x;
	coordenadas.y = y;

	portal_sprite.setPosition(coordenadas.x, coordenadas.y);
	portal_sprite.setOrigin(portal_sprite.getGlobalBounds().width / 2, portal_sprite.getGlobalBounds().height);

	esta_activo = activo;

	if (esta_activo) {

		portal_sprite.setTexture(portal_activo_textura);

	}
	else {

		portal_sprite.setTexture(portal_inactivo_textura);

	}

	portal_colisionador = new FloatRect(portal_sprite.getPosition(), (Vector2f)portal_sprite.getTexture()->getSize());

}

//Cambia el estado del portal, para determinar si puede ser usado o no
void Portal::cambiarEstado(bool nuevo_estado) {

	esta_activo = nuevo_estado;

}

//Devuelve el sprite al llamarse, para luego ser renderizado
Sprite Portal::retornarSprite() {

	return portal_sprite;

}

//Devuelve el colisionador del objeto, usado para deteccion de colisiones
FloatRect Portal::retornarColisionador() {

	return *portal_colisionador;

}

//Devuelve el estado (activo o inactivo) del portal
bool Portal::retornarEstado() {

	return esta_activo;

}

//Fija la textura del portal dependiendo de su estado, intercambia entre la textura activa e inactiva
void Portal::actualizarTexturas() {

	if (esta_activo) {

		portal_sprite.setTexture(portal_activo_textura);

	}
	else {

		portal_sprite.setTexture(portal_inactivo_textura);

	}

}
