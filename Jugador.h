#pragma once

//Inclusión de librerias
#include <SFML/Graphics.hpp>

using namespace sf;

class Jugador {

private:

	Texture jugador_textura;
	Sprite jugador_sprite;
	bool renderizar;
	int llaves;
	int vidas;
	int puntaje;
	Vector2f coordenadas;
	Vector2f velocidad_movimiento;

	FloatRect jugador_colisionador;

public:

	Jugador(float x, float y, int vidas_totales);
	void añadirLlave();
	void añadirPuntos(int cantidad);
	void quitarVida();
	Sprite retornarSprite();
	int retornarConteoLlaves();
	int retornarPuntaje();
	void reiniciarVariables();
	Vector2f retornarPosicion();
	bool debeRenderizarse();
	void cambiarRender(bool estado);

	Vector2f retornarVelocidad();
	void ajustarVelocidad(float x, float y);

	void teletransportar(float x, float y);
	void mover(float velocidad_x, float velocidad_y, float tiempo);

	FloatRect retornarColisionador();

};

