#include "Mezclador.h"

//Constructor de la clase
Mezclador::Mezclador() {

	silenciado = false;

	//Cargar sonido: Llave
	recoger_llave_buffer.loadFromFile("assets/sounds/recoger_llave.wav");
	recoger_llave.setBuffer(recoger_llave_buffer);

	//Cargar sonido: Portal
	portal_abierto_buffer.loadFromFile("assets/sounds/portal_abierto.wav");
	portal_abierto.setBuffer(portal_abierto_buffer);

	//Cargar sonido: Celda
	recoger_celda_buffer.loadFromFile("assets/sounds/recoger_celda.wav");
	recoger_celda.setBuffer(recoger_celda_buffer);
	
	//Cargar sonido: Boton
	ingreso_portal_buffer.loadFromFile("assets/sounds/ingreso_portal.wav");
	ingreso_portal.setBuffer(ingreso_portal_buffer);

}

//Reproduce un sonido pasado por parámetro
void Mezclador::reproducirAudio(int sonido) {

	switch (sonido) {

	case 1:

		recoger_llave.play();

		break;

	case 2:

		portal_abierto.play();

		break;

	case 3:

		recoger_celda.play();

		break;

	case 4:

		ingreso_portal.play();

		break;
	}

}

//Devuelve true si el mezclador está silenciado
bool Mezclador::estaSilenciado() {

	return silenciado;

}

//Hace que el mezclador no reproduzca ningun sonido, usado para el modo de ensordecimiento del juego
void Mezclador::silenciar(bool estado) {

	silenciado = estado;

}