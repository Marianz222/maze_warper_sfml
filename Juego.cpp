#include "Juego.h"

#include <iostream>

using namespace std;

//Constructor de la clase
Juego::Juego() {

	//Establece todas las variables básicas para iniciar
	juego_terminado = false;
	resolucion.x = 1408;
	resolucion.y = 960;
	tiempo_nivel = 40;

	//Variables de tiempo
	cronometro = tiempo_nivel;
	tiempo_inferior = 0;
	tiempo_segundos = 0;

	//Creación de la ventana y el gestor de eventos
	ventana = new RenderWindow(VideoMode(resolucion.x, resolucion.y, 32), "Maze Warper");
	gestor_eventos = new Event;

	//Establece el framerate y oculta el cursor
	ventana->setFramerateLimit(60);
	ventana->setMouseCursorVisible(false);
	activarCursorPersonalizado(true);

	//Establece los datos de fuente y texto
	titan_fuente.loadFromFile("assets/fonts/titan.otf");
	format_fuente.loadFromFile("assets/fonts/format1452.otf");
	tiempo_texto.setFont(format_fuente);
	puntaje_texto.setFont(titan_fuente);
	tiempo_texto.setCharacterSize(35);
	titulo_texto.setFont(titan_fuente);
	fin_texto.setFont(titan_fuente);

	//Reposiciona la ventana a la esquina superior izquierda
	Vector2i posicion_ventana;
	posicion_ventana.x = 0;
	posicion_ventana.y = 0;
	ventana->setPosition(posicion_ventana);

	//Carga y aplicación de textura para el cursor y el boton
	cursor_textura.loadFromFile("assets/images/cursor.png");
	cursor_sprite.setTexture(cursor_textura);
	cursor_sprite.setOrigin(32.f, 32.f);
	cursor_sprite.setScale(0.8f, 0.8f);

	//Creación del botón de reset, único botón del juego
	boton_reset = new Boton("assets/images/boton_reset.png", "assets/images/boton_reset_seleccionado.png", 1275.0, 5.0);

	//Se fija la cantidad de llaves requeridas para abrir las puertas y la cantidad de puntos requeridos para abrir el portal
	llaves_requeridas = 1;
	puntaje_requerido = 1100;

	//Llamada a los métodos de creación de elementos de juego principales: Tablero, Celdas y Textos
	crearMapa();
	crearCeldas();
	crearTexto();
	
	//Creación de los objetos de juego
	jugador = new Jugador(160, 192, 3);
	llave = new Llave(800.0, 192.0);
	portal = new Portal(512.0, 64.0, false);

	//Creación del objeto que maneja el audio y la variable de control de audio
	mezclador = new Mezclador();
	audio_activo = false;

}

//Método encargado de generar el mapa usando la matriz de la clase
void Juego::crearMapa() {

	//Cada loseta recibe un valor de estado:
	// 0 = Vacío
	// 1 = Loseta Normal
	// 2 = Loseta Luminosa
	// 3 = Loseta Bloqueada
	// 4 = Loseta Limitadora
	cuadrilla[0][0] = new Loseta(0.0, 0.0, 4);
	cuadrilla[0][1] = new Loseta(0.0, -64.0, 4);
	cuadrilla[0][2] = new Loseta(0.0, -128.0, 4);
	cuadrilla[0][3] = new Loseta(0.0, -192.0, 4);
	cuadrilla[0][4] = new Loseta(0.0, -256.0, 4);
	cuadrilla[0][5] = new Loseta(0.0, -320.0, 4);
	cuadrilla[0][6] = new Loseta(0.0, -384.0, 4);
	cuadrilla[0][7] = new Loseta(0.0, -448.0, 4);
	cuadrilla[0][8] = new Loseta(0.0, -512.0, 4);
	cuadrilla[0][9] = new Loseta(0.0, -576.0, 4);
	cuadrilla[0][10] = new Loseta(0.0, -640.0, 4);
	cuadrilla[0][11] = new Loseta(0.0, -704.0, 4);
	cuadrilla[0][12] = new Loseta(0.0, -768.0, 4);
	cuadrilla[0][13] = new Loseta(0.0, -832.0, 4);
	cuadrilla[0][14] = new Loseta(0.0, -896.0, 4);

	cuadrilla[1][0] = new Loseta(-64.0, 0.0, 4);
	cuadrilla[1][1] = new Loseta(-64.0, -64.0, 1);
	cuadrilla[1][2] = new Loseta(-64.0, -128.0, 1);
	cuadrilla[1][3] = new Loseta(-64.0, -192.0, 1);
	cuadrilla[1][4] = new Loseta(-64.0, -256.0, 2);
	cuadrilla[1][5] = new Loseta(-64.0, -320.0, 1);
	cuadrilla[1][6] = new Loseta(-64.0, -384.0, 1);
	cuadrilla[1][7] = new Loseta(-64.0, -448.0, 0);
	cuadrilla[1][8] = new Loseta(-64.0, -512.0, 0);
	cuadrilla[1][9] = new Loseta(-64.0, -576.0, 0);
	cuadrilla[1][10] = new Loseta(-64.0, -640.0, 0);
	cuadrilla[1][11] = new Loseta(-64.0, -704.0, 0);
	cuadrilla[1][12] = new Loseta(-64.0, -768.0, 0);
	cuadrilla[1][13] = new Loseta(-64.0, -832.0, 2);
	cuadrilla[1][14] = new Loseta(-64.0, -896.0, 4);

	cuadrilla[2][0] = new Loseta(-128.0, 0.0, 4);
	cuadrilla[2][1] = new Loseta(-128.0, -64.0, 1);
	cuadrilla[2][2] = new Loseta(-128.0, -128.0, 0);
	cuadrilla[2][3] = new Loseta(-128.0, -192.0, 0);
	cuadrilla[2][4] = new Loseta(-128.0, -256.0, 0);
	cuadrilla[2][5] = new Loseta(-128.0, -320.0, 0);
	cuadrilla[2][6] = new Loseta(-128.0, -384.0, 2);
	cuadrilla[2][7] = new Loseta(-128.0, -448.0, 0);
	cuadrilla[2][8] = new Loseta(-128.0, -512.0, 1);
	cuadrilla[2][9] = new Loseta(-128.0, -576.0, 1);
	cuadrilla[2][10] = new Loseta(-128.0, -640.0, 1);
	cuadrilla[2][11] = new Loseta(-128.0, -704.0, 1);
	cuadrilla[2][12] = new Loseta(-128.0, -768.0, 0);
	cuadrilla[2][13] = new Loseta(-128.0, -832.0, 1);
	cuadrilla[2][14] = new Loseta(-128.0, -896.0, 4);

	cuadrilla[3][0] = new Loseta(-192.0, 0.0, 4);
	cuadrilla[3][1] = new Loseta(-192.0, -64.0, 1);
	cuadrilla[3][2] = new Loseta(-192.0, -128.0, 1);
	cuadrilla[3][3] = new Loseta(-192.0, -192.0, 0);
	cuadrilla[3][4] = new Loseta(-192.0, -256.0, 1);
	cuadrilla[3][5] = new Loseta(-192.0, -320.0, 0);
	cuadrilla[3][6] = new Loseta(-192.0, -384.0, 1);
	cuadrilla[3][7] = new Loseta(-192.0, -448.0, 0);
	cuadrilla[3][8] = new Loseta(-192.0, -512.0, 0);
	cuadrilla[3][9] = new Loseta(-192.0, -576.0, 0);
	cuadrilla[3][10] = new Loseta(-192.0, -640.0, 0);
	cuadrilla[3][11] = new Loseta(-192.0, -704.0, 2);
	cuadrilla[3][12] = new Loseta(-192.0, -768.0, 0);
	cuadrilla[3][13] = new Loseta(-192.0, -832.0, 1);
	cuadrilla[3][14] = new Loseta(-192.0, -896.0, 4);

	cuadrilla[4][0] = new Loseta(-256.0, 0.0, 4);
	cuadrilla[4][1] = new Loseta(-256.0, -64.0, 0);
	cuadrilla[4][2] = new Loseta(-256.0, -128.0, 0);
	cuadrilla[4][3] = new Loseta(-256.0, -192.0, 0);
	cuadrilla[4][4] = new Loseta(-256.0, -256.0, 0);
	cuadrilla[4][5] = new Loseta(-256.0, -320.0, 0);
	cuadrilla[4][6] = new Loseta(-256.0, -384.0, 2);
	cuadrilla[4][7] = new Loseta(-256.0, -448.0, 1);
	cuadrilla[4][8] = new Loseta(-256.0, -512.0, 1);
	cuadrilla[4][9] = new Loseta(-256.0, -576.0, 1);
	cuadrilla[4][10] = new Loseta(-256.0, -640.0, 0);
	cuadrilla[4][11] = new Loseta(-256.0, -704.0, 1);
	cuadrilla[4][12] = new Loseta(-256.0, -768.0, 0);
	cuadrilla[4][13] = new Loseta(-256.0, -832.0, 0);
	cuadrilla[4][14] = new Loseta(-256.0, -896.0, 4);

	cuadrilla[5][0] = new Loseta(-320.0, 0.0, 4);
	cuadrilla[5][1] = new Loseta(-320.0, -64.0, 1);
	cuadrilla[5][2] = new Loseta(-320.0, -128.0, 0);
	cuadrilla[5][3] = new Loseta(-320.0, -192.0, 2);
	cuadrilla[5][4] = new Loseta(-320.0, -256.0, 1);
	cuadrilla[5][5] = new Loseta(-320.0, -320.0, 0);
	cuadrilla[5][6] = new Loseta(-320.0, -384.0, 0);
	cuadrilla[5][7] = new Loseta(-320.0, -448.0, 0);
	cuadrilla[5][8] = new Loseta(-320.0, -512.0, 0);
	cuadrilla[5][9] = new Loseta(-320.0, -576.0, 0);
	cuadrilla[5][10] = new Loseta(-320.0, -640.0, 0);
	cuadrilla[5][11] = new Loseta(-320.0, -704.0, 1);
	cuadrilla[5][12] = new Loseta(-320.0, -768.0, 1);
	cuadrilla[5][13] = new Loseta(-320.0, -832.0, 0);
	cuadrilla[5][14] = new Loseta(-320.0, -896.0, 4);

	cuadrilla[6][0] = new Loseta(-384.0, 0.0, 4);
	cuadrilla[6][1] = new Loseta(-384.0, -64.0, 0);
	cuadrilla[6][2] = new Loseta(-384.0, -128.0, 0);
	cuadrilla[6][3] = new Loseta(-384.0, -192.0, 0);
	cuadrilla[6][4] = new Loseta(-384.0, -256.0, 1);
	cuadrilla[6][5] = new Loseta(-384.0, -320.0, 2);
	cuadrilla[6][6] = new Loseta(-384.0, -384.0, 1);
	cuadrilla[6][7] = new Loseta(-384.0, -448.0, 0);
	cuadrilla[6][8] = new Loseta(-384.0, -512.0, 1);
	cuadrilla[6][9] = new Loseta(-384.0, -576.0, 1);
	cuadrilla[6][10] = new Loseta(-384.0, -640.0, 1);
	cuadrilla[6][11] = new Loseta(-384.0, -704.0, 1);
	cuadrilla[6][12] = new Loseta(-384.0, -768.0, 0);
	cuadrilla[6][13] = new Loseta(-384.0, -832.0, 0);
	cuadrilla[6][14] = new Loseta(-384.0, -896.0, 4);

	cuadrilla[7][0] = new Loseta(-448.0, 0.0, 4);
	cuadrilla[7][1] = new Loseta(-448.0, -64.0, 1);
	cuadrilla[7][2] = new Loseta(-448.0, -128.0, 1);
	cuadrilla[7][3] = new Loseta(-448.0, -192.0, 0);
	cuadrilla[7][4] = new Loseta(-448.0, -256.0, 1);
	cuadrilla[7][5] = new Loseta(-448.0, -320.0, 0);
	cuadrilla[7][6] = new Loseta(-448.0, -384.0, 1);
	cuadrilla[7][7] = new Loseta(-448.0, -448.0, 0);
	cuadrilla[7][8] = new Loseta(-448.0, -512.0, 1);
	cuadrilla[7][9] = new Loseta(-448.0, -576.0, 1);
	cuadrilla[7][10] = new Loseta(-448.0, -640.0, 0);
	cuadrilla[7][11] = new Loseta(-448.0, -704.0, 0);
	cuadrilla[7][12] = new Loseta(-448.0, -768.0, 0);
	cuadrilla[7][13] = new Loseta(-448.0, -832.0, 1);
	cuadrilla[7][14] = new Loseta(-448.0, -896.0, 4);

	cuadrilla[8][0] = new Loseta(-512.0, 0.0, 4);
	cuadrilla[8][1] = new Loseta(-512.0, -64.0, 0);
	cuadrilla[8][2] = new Loseta(-512.0, -128.0, 1);
	cuadrilla[8][3] = new Loseta(-512.0, -192.0, 0);
	cuadrilla[8][4] = new Loseta(-512.0, -256.0, 0);
	cuadrilla[8][5] = new Loseta(-512.0, -320.0, 0);
	cuadrilla[8][6] = new Loseta(-512.0, -384.0, 0);
	cuadrilla[8][7] = new Loseta(-512.0, -448.0, 0);
	cuadrilla[8][8] = new Loseta(-512.0, -512.0, 0);
	cuadrilla[8][9] = new Loseta(-512.0, -576.0, 1);
	cuadrilla[8][10] = new Loseta(-512.0, -640.0, 1);
	cuadrilla[8][11] = new Loseta(-512.0, -704.0, 0);
	cuadrilla[8][12] = new Loseta(-512.0, -768.0, 1);
	cuadrilla[8][13] = new Loseta(-512.0, -832.0, 2);
	cuadrilla[8][14] = new Loseta(-512.0, -896.0, 4);

	cuadrilla[9][0] = new Loseta(-576.0, 0.0, 4);
	cuadrilla[9][1] = new Loseta(-576.0, -64.0, 0);
	cuadrilla[9][2] = new Loseta(-576.0, -128.0, 1);
	cuadrilla[9][3] = new Loseta(-576.0, -192.0, 1);
	cuadrilla[9][4] = new Loseta(-576.0, -256.0, 0);
	cuadrilla[9][5] = new Loseta(-576.0, -320.0, 1);
	cuadrilla[9][6] = new Loseta(-576.0, -384.0, 2);
	cuadrilla[9][7] = new Loseta(-576.0, -448.0, 1);
	cuadrilla[9][8] = new Loseta(-576.0, -512.0, 0);
	cuadrilla[9][9] = new Loseta(-576.0, -576.0, 1);
	cuadrilla[9][10] = new Loseta(-576.0, -640.0, 0);
	cuadrilla[9][11] = new Loseta(-576.0, -704.0, 0);
	cuadrilla[9][12] = new Loseta(-576.0, -768.0, 0);
	cuadrilla[9][13] = new Loseta(-576.0, -832.0, 1);
	cuadrilla[9][14] = new Loseta(-576.0, -896.0, 4);

	cuadrilla[10][0] = new Loseta(-640.0, 0.0, 4);
	cuadrilla[10][1] = new Loseta(-640.0, -64.0, 0);
	cuadrilla[10][2] = new Loseta(-640.0, -128.0, 3);
	cuadrilla[10][3] = new Loseta(-640.0, -192.0, 0);
	cuadrilla[10][4] = new Loseta(-640.0, -256.0, 0);
	cuadrilla[10][5] = new Loseta(-640.0, -320.0, 0);
	cuadrilla[10][6] = new Loseta(-640.0, -384.0, 0);
	cuadrilla[10][7] = new Loseta(-640.0, -448.0, 1);
	cuadrilla[10][8] = new Loseta(-640.0, -512.0, 1);
	cuadrilla[10][9] = new Loseta(-640.0, -576.0, 2);
	cuadrilla[10][10] = new Loseta(-640.0, -640.0, 3);
	cuadrilla[10][11] = new Loseta(-640.0, -704.0, 1);
	cuadrilla[10][12] = new Loseta(-640.0, -768.0, 0);
	cuadrilla[10][13] = new Loseta(-640.0, -832.0, 0);
	cuadrilla[10][14] = new Loseta(-640.0, -896.0, 4);

	cuadrilla[11][0] = new Loseta(-704.0, 0.0, 4);
	cuadrilla[11][1] = new Loseta(-704.0, -64.0, 1);
	cuadrilla[11][2] = new Loseta(-704.0, -128.0, 1);
	cuadrilla[11][3] = new Loseta(-704.0, -192.0, 1);
	cuadrilla[11][4] = new Loseta(-704.0, -256.0, 0);
	cuadrilla[11][5] = new Loseta(-704.0, -320.0, 1);
	cuadrilla[11][6] = new Loseta(-704.0, -384.0, 0);
	cuadrilla[11][7] = new Loseta(-704.0, -448.0, 0);
	cuadrilla[11][8] = new Loseta(-704.0, -512.0, 0);
	cuadrilla[11][9] = new Loseta(-704.0, -576.0, 0);
	cuadrilla[11][10] = new Loseta(-704.0, -640.0, 0);
	cuadrilla[11][11] = new Loseta(-704.0, -704.0, 1);
	cuadrilla[11][12] = new Loseta(-704.0, -768.0, 2);
	cuadrilla[11][13] = new Loseta(-704.0, -832.0, 0);
	cuadrilla[11][14] = new Loseta(-704.0, -896.0, 4);

	cuadrilla[12][0] = new Loseta(-768.0, 0.0, 4);
	cuadrilla[12][1] = new Loseta(-768.0, -64.0, 0);
	cuadrilla[12][2] = new Loseta(-768.0, -128.0, 0);
	cuadrilla[12][3] = new Loseta(-768.0, -192.0, 1);
	cuadrilla[12][4] = new Loseta(-768.0, -256.0, 0);
	cuadrilla[12][5] = new Loseta(-768.0, -320.0, 1);
	cuadrilla[12][6] = new Loseta(-768.0, -384.0, 2);
	cuadrilla[12][7] = new Loseta(-768.0, -448.0, 1);
	cuadrilla[12][8] = new Loseta(-768.0, -512.0, 0);
	cuadrilla[12][9] = new Loseta(-768.0, -576.0, 1);
	cuadrilla[12][10] = new Loseta(-768.0, -640.0, 1);
	cuadrilla[12][11] = new Loseta(-768.0, -704.0, 1);
	cuadrilla[12][12] = new Loseta(-768.0, -768.0, 0);
	cuadrilla[12][13] = new Loseta(-768.0, -832.0, 0);
	cuadrilla[12][14] = new Loseta(-768.0, -896.0, 4);

	cuadrilla[13][0] = new Loseta(-832.0, 0.0, 4);
	cuadrilla[13][1] = new Loseta(-832.0, -64.0, 0);
	cuadrilla[13][2] = new Loseta(-832.0, -128.0, 1);
	cuadrilla[13][3] = new Loseta(-832.0, -192.0, 1);
	cuadrilla[13][4] = new Loseta(-832.0, -256.0, 1);
	cuadrilla[13][5] = new Loseta(-832.0, -320.0, 1);
	cuadrilla[13][6] = new Loseta(-832.0, -384.0, 0);
	cuadrilla[13][7] = new Loseta(-832.0, -448.0, 1);
	cuadrilla[13][8] = new Loseta(-832.0, -512.0, 1);
	cuadrilla[13][9] = new Loseta(-832.0, -576.0, 2);
	cuadrilla[13][10] = new Loseta(-832.0, -640.0, 0);
	cuadrilla[13][11] = new Loseta(-832.0, -704.0, 0);
	cuadrilla[13][12] = new Loseta(-832.0, -768.0, 0);
	cuadrilla[13][13] = new Loseta(-832.0, -832.0, 1);
	cuadrilla[13][14] = new Loseta(-832.0, -896.0, 4);

	cuadrilla[14][0] = new Loseta(-896.0, 0.0, 4);
	cuadrilla[14][1] = new Loseta(-896.0, -64.0, 0);
	cuadrilla[14][2] = new Loseta(-896.0, -128.0, 0);
	cuadrilla[14][3] = new Loseta(-896.0, -192.0, 0);
	cuadrilla[14][4] = new Loseta(-896.0, -256.0, 0);
	cuadrilla[14][5] = new Loseta(-896.0, -320.0, 1);
	cuadrilla[14][6] = new Loseta(-896.0, -384.0, 1);
	cuadrilla[14][7] = new Loseta(-896.0, -448.0, 1);
	cuadrilla[14][8] = new Loseta(-896.0, -512.0, 0);
	cuadrilla[14][9] = new Loseta(-896.0, -576.0, 1);
	cuadrilla[14][10] = new Loseta(-896.0, -640.0, 2);
	cuadrilla[14][11] = new Loseta(-896.0, -704.0, 1);
	cuadrilla[14][12] = new Loseta(-896.0, -768.0, 0);
	cuadrilla[14][13] = new Loseta(-896.0, -832.0, 2);
	cuadrilla[14][14] = new Loseta(-896.0, -896.0, 4);

	cuadrilla[15][0] = new Loseta(-960.0, 0.0, 4);
	cuadrilla[15][1] = new Loseta(-960.0, -64.0, 2);
	cuadrilla[15][2] = new Loseta(-960.0, -128.0, 1);
	cuadrilla[15][3] = new Loseta(-960.0, -192.0, 1);
	cuadrilla[15][4] = new Loseta(-960.0, -256.0, 0);
	cuadrilla[15][5] = new Loseta(-960.0, -320.0, 1);
	cuadrilla[15][6] = new Loseta(-960.0, -384.0, 0);
	cuadrilla[15][7] = new Loseta(-960.0, -448.0, 0);
	cuadrilla[15][8] = new Loseta(-960.0, -512.0, 0);
	cuadrilla[15][9] = new Loseta(-960.0, -576.0, 0);
	cuadrilla[15][10] = new Loseta(-960.0, -640.0, 1);
	cuadrilla[15][11] = new Loseta(-960.0, -704.0, 0);
	cuadrilla[15][12] = new Loseta(-960.0, -768.0, 0);
	cuadrilla[15][13] = new Loseta(-960.0, -832.0, 1);
	cuadrilla[15][14] = new Loseta(-960.0, -896.0, 4);

	cuadrilla[16][0] = new Loseta(-1024.0, 0.0, 4);
	cuadrilla[16][1] = new Loseta(-1024.0, -64.0, 0);
	cuadrilla[16][2] = new Loseta(-1024.0, -128.0, 0);
	cuadrilla[16][3] = new Loseta(-1024.0, -192.0, 0);
	cuadrilla[16][4] = new Loseta(-1024.0, -256.0, 0);
	cuadrilla[16][5] = new Loseta(-1024.0, -320.0, 0);
	cuadrilla[16][6] = new Loseta(-1024.0, -384.0, 0);
	cuadrilla[16][7] = new Loseta(-1024.0, -448.0, 1);
	cuadrilla[16][8] = new Loseta(-1024.0, -512.0, 1);
	cuadrilla[16][9] = new Loseta(-1024.0, -576.0, 0);
	cuadrilla[16][10] = new Loseta(-1024.0, -640.0, 0);
	cuadrilla[16][11] = new Loseta(-1024.0, -704.0, 0);
	cuadrilla[16][12] = new Loseta(-1024.0, -768.0, 1);
	cuadrilla[16][13] = new Loseta(-1024.0, -832.0, 2);
	cuadrilla[16][14] = new Loseta(-1024.0, -896.0, 4);

	cuadrilla[17][0] = new Loseta(-1088.0, 0.0, 4);
	cuadrilla[17][1] = new Loseta(-1088.0, -64.0, 4);
	cuadrilla[17][2] = new Loseta(-1088.0, -128.0, 4);
	cuadrilla[17][3] = new Loseta(-1088.0, -192.0, 4);
	cuadrilla[17][4] = new Loseta(-1088.0, -256.0, 4);
	cuadrilla[17][5] = new Loseta(-1088.0, -320.0, 4);
	cuadrilla[17][6] = new Loseta(-1088.0, -384.0, 4);
	cuadrilla[17][7] = new Loseta(-1088.0, -448.0, 4);
	cuadrilla[17][8] = new Loseta(-1088.0, -512.0, 4);
	cuadrilla[17][9] = new Loseta(-1088.0, -576.0, 4);
	cuadrilla[17][10] = new Loseta(-1088.0, -640.0, 4);
	cuadrilla[17][11] = new Loseta(-1088.0, -704.0, 4);
	cuadrilla[17][12] = new Loseta(-1088.0, -768.0, 4);
	cuadrilla[17][13] = new Loseta(-1088.0, -832.0, 4);
	cuadrilla[17][14] = new Loseta(-1088.0, -896.0, 4);

	for (int i = 0; i < 18; i++) {

		for (int k = 0; k < 15; k++) {

			cuadrilla[i][k]->retornarSprite().setOrigin(cuadrilla[i][k]->retornarColisionador().width / 2, cuadrilla[i][k]->retornarColisionador().height);

		}

	}

}

//Método encargado de inicializar todos los objetos del arreglo de celdas
void Juego::crearCeldas() {

	//Creación del arreglo de celdas
	celdas[0] = new Celda(224, 384);
	celdas[1] = new Celda(416, 128);
	celdas[2] = new Celda(480, 384);
	celdas[3] = new Celda(352, 576);
	celdas[4] = new Celda(224, 832);
	celdas[5] = new Celda(480, 704);
	celdas[6] = new Celda(608, 576);
	celdas[7] = new Celda(800, 320);
	celdas[8] = new Celda(1056, 128);
	celdas[9] = new Celda(800, 576);
	celdas[10] = new Celda(864, 704);
	celdas[11] = new Celda(928, 576);

	for (int i = 0; i < 12; i++) {

		celdas[i]->retornarSprite().setOrigin(celdas[i]->retornarColisionador().width / 2, celdas[i]->retornarColisionador().height);

	}

}

//Método encargado de crear y darle propiedades a todos los elementos de texto
void Juego::crearTexto() {

	//Creación de texto y asignación de sus propiedades
	titulo_texto.setString("Maze Warper");
	titulo_texto.setPosition(1160.0, 910.0);
	titulo_texto.setCharacterSize(25);

	puntaje_texto.setPosition(1180.0, 256.0);
	puntaje_texto.setCharacterSize(25);

	tiempo_texto.setStyle(Text::Bold);
	tiempo_texto.setPosition(1180.0, 325.0);
	tiempo_texto.setCharacterSize(35);

	fin_texto.setString("Juego Terminado!");
	fin_texto.setCharacterSize(50);
	fin_texto.setFillColor(Color::Cyan);
	fin_texto.setOutlineThickness(1.0);
	fin_texto.setPosition(400, resolucion.y / static_cast<float>(2));

}

//función que permite fijar el tiempo del cronómetro
void Juego::establecerCronometro(int tiempo) {

	cronometro = tiempo;

}

//Método encargado de controlar de forma constante el movimiento del jugador mediante el teclado (sin pasar por la lista
//de eventos). También verifica que no se esté colisionando con una loseta del mapa antes de efectuar el movimiento
void Juego::controlTeclado() {

	// Create a FloatRect for the player's next position
	FloatRect nextPosition(jugador->retornarSprite().getPosition().x + jugador->retornarVelocidad().x, jugador->retornarSprite().getPosition().y + jugador->retornarVelocidad().y, jugador->retornarColisionador().width, jugador->retornarColisionador().height);

	nextPositionShape.setSize(Vector2f(nextPosition.width, nextPosition.height));
	nextPositionShape.setPosition(nextPosition.left, nextPosition.top);
	nextPositionShape.setOrigin(nextPositionShape.getSize().x / 2, nextPositionShape.getSize().y / 2);
	nextPositionShape.setFillColor(Color::Transparent);
	nextPositionShape.setOutlineColor(Color::Red);
	nextPositionShape.setOutlineThickness(1.0f);

	//Condición para solo mover al jugador mientras está dibujado en pantalla, evita que se mueva tras terminar
	if (jugador->debeRenderizarse()) {

		for (int i = 0; i < 18; i++) {

			for (int k = 0; k < 15; k++) {

				if (cuadrilla[i][k] == 0) {

					break;

				}




				
				bool hay_colision = false;

				if (cuadrilla[i][k]->retornarColisionador().intersects(nextPosition)) {

					cout << "colision" << cuadrilla[i][k]->retornarEstado() << endl;

					hay_colision = true;

					break;

				}
				
				if (!hay_colision) {

					if (Keyboard::isKeyPressed(Keyboard::D)) {

						//Mueve hacia la derecha
						jugador->mover(jugador->retornarVelocidad().x, 0.0, tiempo_delta);

					}

					if (Keyboard::isKeyPressed(Keyboard::W)) {

						//Mueve hacia arriba
						jugador->mover(0.0, (jugador->retornarVelocidad().y * -1), tiempo_delta);

					}

					if (Keyboard::isKeyPressed(Keyboard::S)) {

						//Mueve hacia abajo
						jugador->mover(0.0, (jugador->retornarVelocidad().y), tiempo_delta);

					}

					if (Keyboard::isKeyPressed(Keyboard::A)) {

						//Mueve hacia la izquierda
						jugador->mover((jugador->retornarVelocidad().x * -1), 0.0, tiempo_delta);

					}

				}
				
				














				/*
				// Check for collisions
				if (jugador->retornarColisionador().intersects(cuadrilla[i][k]->retornarColisionador()))
				{
					// Handle collision
					cout << "Collision detected!\n";

					//Cálculo para obtener la distancia entre el punto central de ambos sprites
					sf::Vector2f center1 = jugador->retornarPosicion() + 0.5f * Vector2f(64.f, 64.f);
					sf::Vector2f center2 = cuadrilla[i][k]->retornarPosicion() + 0.5f * Vector2f(64.f, 64.f);
					sf::Vector2f distance = center1 - center2;

					//Valor absoluto usado para determinar desde qué dirección provienen las colisiones
					float absoluto_x = abs(distance.x);
					float absoluto_y = abs(distance.y);

					if (absoluto_x > absoluto_y)
					{
						if (distance.x > 0)
						{
							cout << "Collision from right side\n";
						}
						else
						{
							cout << "Collision from left side\n";
						}
					}
					else
					{
						if (distance.y > 0)
						{
							cout << "Collision from bottom side\n";
						}
						else
						{
							cout << "Collision from top side\n";
						}
					}

					// Reverse the velocities of the rectangles
					jugador->mover(jugador->retornarVelocidad().x * -1, jugador->retornarVelocidad().y * -1, tiempo_delta);

				}

				*/

				/*
				if (Keyboard::isKeyPressed(Keyboard::D)) {

					//Mueve hacia la derecha
					jugador->mover(jugador->retornarVelocidad().x, 0.0, tiempo_delta);



				}

				if (Keyboard::isKeyPressed(Keyboard::W)) {

					//Mueve hacia arriba
					jugador->mover(0.0, (jugador->retornarVelocidad().y * -1), tiempo_delta);



				}

				if (Keyboard::isKeyPressed(Keyboard::S)) {

					//Mueve hacia abajo
					jugador->mover(0.0, (jugador->retornarVelocidad().y), tiempo_delta);



				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {

					//Mueve hacia la izquierda
					jugador->mover((jugador->retornarVelocidad().x * -1), 0.0, tiempo_delta);



				}
				
				*/

                /*
				bool permitir_movimiento_derecha = true;

				if (jugador->retornarColisionador().intersects(cuadrilla[i][k]->retornarColisionador())) {

					if (jugador->retornarPosicion().x <= cuadrilla[i][k]->retornarColisionador().left) {

						cout << "Colision Derecha" << endl;

						//jugador->mover(jugador->retornarVelocidad().x * -1, 0.0f, tiempo_delta);

						permitir_movimiento_derecha = false;

					}
					else {

						permitir_movimiento_derecha = true;

					}

					if (permitir_movimiento_derecha) {

						if (Keyboard::isKeyPressed(Keyboard::D)) {

							//Mueve hacia la derecha
							jugador->mover(jugador->retornarVelocidad().x, 0.0, tiempo_delta);



						}

					}





					if (jugador->retornarPosicion().x >= cuadrilla[i][k]->retornarColisionador().left) {

						cout << "Colision Izquierda" << endl;

						if (Keyboard::isKeyPressed(Keyboard::A)) {

							//Mueve hacia la izquierda
							jugador->mover((jugador->retornarVelocidad().x * -1), 0.0, tiempo_delta);



						}

					}



					if (jugador->retornarPosicion().y <= cuadrilla[i][k]->retornarColisionador().top) {

						cout << "Colision Arriba" << endl;

						if (Keyboard::isKeyPressed(Keyboard::W)) {

							//Mueve hacia arriba
							jugador->mover(0.0, (jugador->retornarVelocidad().y * -1), tiempo_delta);



						}

					}



					if (jugador->retornarPosicion().y >= cuadrilla[i][k]->retornarColisionador().top) {

						cout << "Colision Abajo" << endl;

						if (Keyboard::isKeyPressed(Keyboard::S)) {

							//Mueve hacia abajo
							jugador->mover(0.0, (jugador->retornarVelocidad().y), tiempo_delta);



						}

					}

				}

				*/
			}

		}

	}

}

//Método encargado de administrar los eventos disparados dentro de la ventana, excluyendo las teclas de movimiento del jugador
void Juego::procesarEventos() {

	while (ventana->pollEvent(*gestor_eventos)) {

		switch (gestor_eventos->type) {

		case Event::MouseMoved:

			cursor_sprite.setPosition((Vector2f)Mouse::getPosition(*ventana));

			if (cursor_sprite.getGlobalBounds().intersects(boton_reset->retornarColisionador())) {

				//Al poner el cursor sobre el boton, este cambia su textura
				boton_reset->intercambiarTexturas(false);

			}
			else {

				boton_reset->intercambiarTexturas(true);

			}

			break;

		case Event::MouseButtonPressed:

			if (cursor_sprite.getGlobalBounds().intersects(boton_reset->retornarColisionador())) {

				cout << "[DEBUG] / [Info]: Boton presionado: Reiniciar" << endl;

				//Al hacer click sobre el boton de reinicio, se reinicia el juego.
				//También funciona con la tecla 'R'
				reiniciar();

			}

			break;

		case Event::Closed:

			cout << "[DEBUG] / [Info]: Ventana cerrada" << endl;

			ventana->close();

			break;

		case Event::KeyPressed:

			switch (gestor_eventos->key.code) {

			case Keyboard::R:

				cout << "[DEBUG] / [Teclado]: Tecla presionada: R" << endl;
				cout << "[DEBUG] / [Info]: Reiniciando..." << endl;

				//Reinicia todas las variables y estados para volver a jugar
				reiniciar();

				break;

			case Keyboard::F1:

				cout << "[DEBUG] / [Teclado]: Tecla presionada: F1" << endl;
				cout << "[DEBUG] / [Info]: Mostrando cursor..." << endl;

				ventana->setMouseCursorVisible(true);
				activarCursorPersonalizado(false);

				break;

			case Keyboard::F2:

				cout << "[DEBUG] / [Teclado]: Tecla presionada: F2" << endl;
				cout << "[DEBUG] / [Info]: Ocultando cursor..." << endl;

				ventana->setMouseCursorVisible(false);
				activarCursorPersonalizado(true);

				break;

			case Keyboard::F3:

				cout << "[DEBUG] / [Teclado]: Tecla presionada: F3" << endl;

				if (!mezclador->estaSilenciado()) {

					mezclador->silenciar(true);
					cout << "[DEBUG] / [Info]: Desactivando audio" << endl;

				}
				else {

					mezclador->silenciar(false);
					cout << "[DEBUG] / [Info]: Activando audio" << endl;

				}

			}

			break;

		}

	}

}

//Este método revisa el tiempo del cronometro, y en base al mismo altera los colores del texto
void Juego::colorearTexto() {

	if (cronometro > 20) {

		tiempo_texto.setFillColor(Color::Green);

	}
	else if (cronometro <= 20 && cronometro > 10) {

		tiempo_texto.setFillColor(Color::Yellow);
	}
	else if (cronometro < 10) {

		tiempo_texto.setFillColor(Color::Red);

	}

	if (jugador->retornarPuntaje() == puntaje_requerido) {

		puntaje_texto.setFillColor(Color::Yellow);

	}

}

//Método que manda toda la información al método de dibujado de la ventana para mostrar el contenido en pantalla
void Juego::renderizar() {

	puntaje_texto.setString("Puntos: " + to_string(jugador->retornarPuntaje()));
	tiempo_texto.setString("Tiempo - " + to_string(cronometro));

	//Se limpia la pantalla
	ventana->clear();

	//Renderizado de sprites
	for (int i = 0; i < 18; i++) {

		for (int k = 0; k < 15; k++) {

			if (cuadrilla[i][k]->debeRenderizarse()) {

				ventana->draw(cuadrilla[i][k]->retornarSprite());

			}

		}

	}

	for (int i = 0; i < 12; i++) {

		if (celdas[i]->debeRenderizarse()) {

			ventana->draw(celdas[i]->retornarSprite());

		}

	}

	if (llave->debeRenderizarse()) {

		ventana->draw(llave->retornarSprite());

	}

	ventana->draw(portal->retornarSprite());

	if (jugador->debeRenderizarse()) {

		ventana->draw(jugador->retornarSprite());

	}

	ventana->draw(boton_reset->retornarSprite());

	if (cursor_modificado) {

		ventana->draw(cursor_sprite);

	}

	//Renderizado de texto

	ventana->draw(puntaje_texto);

	ventana->draw(titulo_texto);

	ventana->draw(tiempo_texto);

	ventana->draw(nextPositionShape);

	if (juego_terminado) {

		ventana->draw(fin_texto);

	}

	//Se muestra lo cargado en pantalla
	ventana->display();

}

//Detecta la colisión del jugador con objetos del juego como llaves, celdas y el portal de salida.
void Juego::colisionObjetos() {

	//Colisión con la llave
	if (jugador->retornarColisionador().intersects(llave->retornarColisionador())) {

		if (llave->debeRenderizarse() && jugador->debeRenderizarse()) {

			cout << "[DEBUG] / [Colisiones]: Colision detectada: llave" << endl;

			jugador->añadirLlave();

			if (!mezclador->estaSilenciado()) {

				mezclador->reproducirAudio(1);

			}
			
			llave->cambiarRender(false);

		}

	}

	//Colisión con el portal
	if (jugador->retornarColisionador().intersects(portal->retornarColisionador())) {

		if (portal->retornarEstado()) {

			cout << "[DEBUG] / [Info]: Terminó el juego. Ganaste! (saliste por el portal)" << endl;

			//Apaga el portal
			portal->cambiarEstado(false);

			if (jugador->debeRenderizarse()) {

				//Retira al jugador del nivel
				jugador->cambiarRender(false);

				if (!mezclador->estaSilenciado()) {

					mezclador->reproducirAudio(4);

				}

			}

			juego_terminado = true;

		}

	}

	//Colisión con las celdas
	for (int i = 0; i < 12; i++) {

		if (jugador->retornarColisionador().intersects(celdas[i]->retornarColisionador())) {

			if (celdas[i]->debeRenderizarse() && jugador->debeRenderizarse()) {

				cout << "[DEBUG] / [Colisiones]: Colision detectada: celda" << endl;

				//Añade el puntaje al jugador y elimina la celda recolectada del arreglo.
				jugador->añadirPuntos(100);
				//Suma 1 segundo al cronometro
				cronometro++;

				if (!mezclador->estaSilenciado()) {

					mezclador->reproducirAudio(3);

				}
				
				celdas[i]->cambiarRender(false);

				cout << "[DEBUG] / [Info]: Puntaje sumado: 100" << endl;
				cout << "Puntos totales: " + to_string(jugador->retornarPuntaje()) << endl;

			}
			
		}

	}

}

//Función que permite activar o desactivar el sprite para el cursor custom, utilizado para visibilizar/invisibilizar el mismo
//mediante el evento de tecla presionada
void Juego::activarCursorPersonalizado(bool estado) {

	cursor_modificado = estado;

}

void Juego::desbloquearLosetas() {

	if (jugador->retornarConteoLlaves() == llaves_requeridas) {

		cuadrilla[10][2]->cambiarRender(false);
		cuadrilla[10][10]->cambiarRender(false);

	}

}

void Juego::activarPortal() {

	if (jugador->retornarPuntaje() == puntaje_requerido) {

		portal->cambiarEstado(true);

		if (!audio_activo) {
			
			if (!mezclador->estaSilenciado()) {

				mezclador->reproducirAudio(2);

				audio_activo = true;

			}

		}

		portal->actualizarTexturas();

	}

}

void Juego::actualizarCronometro() {

	if (!juego_terminado) {

		if (tiempo_inferior < 60) {

			tiempo_inferior++;

		}
		else {

			if (cronometro > 0) {

				tiempo_inferior = 0;
				cronometro--;

			}

		}

	}

	if (cronometro == 0) {

		if (!juego_terminado) {

			juego_terminado = true;

			cout << "[DEBUG] / [Info]: Juego Terminado: Perdiste! (Se acabo el tiempo)" << endl;

			

		}

	}

}

//Función que restablece todos los valores modificados durante la partida para volver a jugar
void Juego::reiniciar() {

	juego_terminado = false;

	//Reinicia el cronometro
	establecerCronometro(tiempo_nivel);

	//Reposiciona al jugador, lo hace reaparecer y le reinicia el puntaje
	jugador->teletransportar(160.0, 192.0);
	jugador->reiniciarVariables();
	jugador->cambiarRender(true);

	//Si la casilla bloqueada #1 ha sido desbloqueada, la vuelve a bloquear
	if (!cuadrilla[10][2]->debeRenderizarse()) {

		cuadrilla[10][2]->cambiarRender(true);

	}

	//Si la casilla bloqueada #2 ha sido desbloqueada, la vuelve a bloquear
	if (!cuadrilla[10][10]->debeRenderizarse()) {

		cuadrilla[10][10]->cambiarRender(true);

	}

	//Desactiva el portal y actualiza su textura
	portal->cambiarEstado(false);
	portal->actualizarTexturas();

	//Reactiva la llave recolectada haciendo que vuelva a renderizarse
	llave->cambiarRender(true);
	
	//Reactiva el render de las celdas. Revisa cuales requieren reactivación revisando si están o no siendo renderizadas
	for (int i = 0; i < 12; i++) {

		if (!celdas[i]->debeRenderizarse()) {

			celdas[i]->cambiarRender(true);

		}

	}

	//Reactiva el cursor en pantalla si estaba desactivado
	ventana->setMouseCursorVisible(false);
	activarCursorPersonalizado(true);


}

//Función del bucle núcleo, aca se ejecuta toda la lógica del juego
void Juego::buclePrincipal() {

	while (ventana->isOpen()) {

		//Obtiene el tiempo transcurrido
		tiempo_delta = reloj.restart().asSeconds();

		//Al terminar el juego, ciertos métodos dejan de llamarse
		if (!juego_terminado) {

			actualizarCronometro();

			colorearTexto();

			controlTeclado();

			desbloquearLosetas();

			colisionObjetos();

			activarPortal();

		}

		procesarEventos();

		renderizar();

	}

}