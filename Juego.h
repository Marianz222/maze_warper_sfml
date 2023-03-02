#pragma once

//Inclusión de clases
#include "Loseta.h"
#include "Jugador.h"
#include "Llave.h"
#include "Portal.h"
#include "Celda.h"
#include "Boton.h"
#include "Mezclador.h"

//Inclusión de librerias
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Juego {

private:

	//Variables generales: Propiedades de ventana, valor del cronometro, gestion de eventos...
	Vector2i resolucion;
	RenderWindow * ventana;
	int tiempo_nivel;
	int cronometro;
	bool juego_terminado;
	Event * gestor_eventos;
	bool cursor_modificado;

	//Variables de interfaz
	Font titan_fuente;
	Font format_fuente;
	Text puntaje_texto;
	Text tiempo_texto;
	Text titulo_texto;
	Text fin_texto;
	
	//Variables de sprite y textura para el cursor personalizado
	Texture cursor_textura;
	Sprite cursor_sprite;

	//Variables propias del juego, Jugador, Nivel, Portal y Llave
	Loseta * cuadrilla[18][15];

	//Objetos y variables de juego
	Celda* celdas[12];
	Jugador* jugador;
	Llave* llave;
	Portal* portal;
	Boton* boton_reset;
	int puntaje_requerido;
	int llaves_requeridas;
	Mezclador* mezclador;
	bool audio_activo;

	//Variables de control de tiempo
	Clock reloj;
	float tiempo_delta;
	int tiempo_inferior;
	int tiempo_segundos;

	RectangleShape nextPositionShape;

public:

	Juego();
	void crearMapa();
	void crearCeldas();
	void crearTexto();
	void procesarEventos();
	void controlTeclado();
	void buclePrincipal();
	void establecerCronometro(int tiempo);
	void colisionObjetos();
	void renderizar();
	void activarCursorPersonalizado(bool estado);
	void actualizarCronometro();
	void colorearTexto();
	void reiniciar();
	void desbloquearLosetas();
	void activarPortal();

};

