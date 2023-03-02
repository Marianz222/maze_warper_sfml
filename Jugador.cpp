#include "Jugador.h"

//Constructor de la clase
Jugador::Jugador(float x, float y, int vidas_totales) {

	//Establece las variables iniciales
	renderizar = true;

	if (vidas_totales < 0) {

		vidas = 1;

	}
	else (vidas = vidas_totales);

	puntaje = 0;
	llaves = 0;

	//Carga y aplica la textura
	jugador_textura.loadFromFile("assets/images/jugador.png");
	jugador_sprite.setTexture(jugador_textura);

	//Fijado inicial de las coordenadas
	coordenadas.x = x;
	coordenadas.y = y;

	//Se asigna la posición inicial del jugador
	jugador_sprite.setPosition(coordenadas.x, coordenadas.y);
	jugador_sprite.setOrigin(jugador_sprite.getGlobalBounds().width / 2, jugador_sprite.getGlobalBounds().height);

	//Se establece la velocidad en ambos ejes
	velocidad_movimiento.x = 1.5;
	velocidad_movimiento.y = 1.5;

}

//Incrementa la cantidad de llaves que tiene el jugador
void Jugador::añadirLlave() {

	llaves++;

}

//Adiciona puntaje al jugador, la cantidad se pasa por parámetro
void Jugador::añadirPuntos(int cantidad) {

	puntaje += cantidad;

}

//Resta una vida al jugador
void Jugador::quitarVida() {

	vidas--;

}

//Devuelve el sprite al llamarse, para luego ser renderizado
Sprite Jugador::retornarSprite() {

	return jugador_sprite;

}

void Jugador::teletransportar(float x, float y) {

	jugador_sprite.setPosition(x, y);

}

void Jugador::mover(float velocidad_x, float velocidad_y, float tiempo) {

	jugador_sprite.setPosition(jugador_sprite.getPosition().x + velocidad_x * tiempo, jugador_sprite.getPosition().y + velocidad_y * tiempo);

}

int Jugador::retornarConteoLlaves() {

	return llaves;

}

int Jugador::retornarPuntaje() {

	return puntaje;

}

void Jugador::reiniciarVariables() {

	puntaje = 0;
	llaves = 0;

}

Vector2f Jugador::retornarPosicion() {

	return coordenadas;

}

bool Jugador::debeRenderizarse() {

	return renderizar;

}

void Jugador::cambiarRender(bool estado) {

	renderizar = estado;

}

Vector2f Jugador::retornarVelocidad() {

	return velocidad_movimiento;

}

void Jugador::ajustarVelocidad(float x, float y) {

	velocidad_movimiento.x = x;
	velocidad_movimiento.y = y;

}

//Método no utilizado en el resultado final
FloatRect Jugador::retornarColisionador() {

	return jugador_sprite.getGlobalBounds();

}