#include "Llave.h"

//Constructor de la clase
Llave::Llave(float x, float y) {
	
	renderizar = true;

	llave_textura.loadFromFile("assets/images/llave.png");
	llave_sprite.setTexture(llave_textura);

	coordenadas.x = x;
	coordenadas.y = y;

	llave_sprite.setPosition(coordenadas.x, coordenadas.y);
	llave_sprite.setOrigin(llave_sprite.getGlobalBounds().width / 2, llave_sprite.getGlobalBounds().height);

	llave_colisionador = new FloatRect(llave_sprite.getPosition(), (Vector2f)llave_sprite.getTexture()->getSize());

}

//Devuelve el sprite al llamarse, para luego ser renderizado
Sprite Llave::retornarSprite() {

	return llave_sprite;

}

//Devuelve el colisionador del objeto al llamarse, para detectar colisiones
FloatRect Llave::retornarColisionador() {

	return *llave_colisionador;

}

//Retorna si el objeto debe renderizarse en la ventana o no
bool Llave::debeRenderizarse() {

	return renderizar;

}

//Establece mediante un bool pasado por parámetro si el objeto debe renderizarse o no
void Llave::cambiarRender(bool estado) {

	renderizar = estado;

}