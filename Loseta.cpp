#include "Loseta.h"

//Constructor de la clase
Loseta::Loseta(float x, float y, int nuevo_estado) {

	renderizar = true;

	loseta_base.loadFromFile("assets/images/loseta_solida.png");
	loseta_luminosa.loadFromFile("assets/images/loseta_luminosa.png");
	loseta_bloqueada.loadFromFile("assets/images/loseta_bloqueada.png");
	loseta_limitante.loadFromFile("assets/images/loseta_limitante.png");
	loseta_fondo.loadFromFile("assets/images/loseta_fondo.png");

	estado = nuevo_estado;

	coordenadas.x = x;
	coordenadas.y = y;

	loseta_sprite.setOrigin(coordenadas.x, coordenadas.y);
	
	switch (estado) {

	case 0:

		loseta_sprite.setTexture(loseta_fondo);

		break;

	case 1:

		loseta_sprite.setTexture(loseta_base);

		break;

	case 2:

		loseta_sprite.setTexture(loseta_luminosa);

		break;

	case 3:

		loseta_sprite.setTexture(loseta_bloqueada);

		break;

	case 4:

		loseta_sprite.setTexture(loseta_limitante);

		break;

	}

}

//Devuelve el sprite al llamarse, para luego ser renderizado
Sprite Loseta::retornarSprite() {

	return loseta_sprite;

}

int Loseta::retornarEstado() {

	return estado;

}

Vector2f Loseta::retornarPosicion() {

	return coordenadas;

}

bool Loseta::debeRenderizarse() {

	return renderizar;

}

void Loseta::cambiarRender(bool estado) {

	renderizar = estado;

}

FloatRect Loseta::retornarColisionador() {

	return loseta_sprite.getGlobalBounds();

}