#pragma once

#include <SFML/Audio.hpp>

using namespace sf;

class Mezclador {

private:

	bool silenciado;

	SoundBuffer recoger_llave_buffer;
	Sound recoger_llave;

	SoundBuffer recoger_celda_buffer;
	Sound recoger_celda;

	SoundBuffer portal_abierto_buffer;
	Sound portal_abierto;

	SoundBuffer ingreso_portal_buffer;
	Sound ingreso_portal;


public:

	Mezclador();
	void reproducirAudio(int sonido);
	bool estaSilenciado();
	void silenciar(bool estado);

};

