#ifndef __Nivel__
#define __Nivel__

#include <vector>
#include <string>
#include <memory>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <iostream>

#include "Entidad.h"
#include "Habitacion.h"


using namespace std;

//Nivel. Clase que contiene todas las entidades del juego
//y administra las interacciones entre ellas y el avance
//de la trama
class Nivel
{
public:
	Nivel();

	void operacion(const vector<string> operacion); //Todo: ¿Pasar como puntero?
	bool isGameOver() const;

private :
	//Lista de entidades
	vector<unique_ptr<Entidad>> entidades;
	//Puntero que indica que habitación se está visitando
	Habitacion* visitando;
	//Puntero que indica cuando se ha acabado el juego
	bool gameOver;
	//NARRATIVA: Tiempo, para indicar el tiempo transcurrido en los Quicktime events
	time_t tiempo;

	Entidad* buscarEntidad(const string entidadDeseada);
	void take(const string objetoDeseado);
	void drop(const string objetoDeseado, const string contenedorDeseado = "");
	void go(const string destinoDeseado);
	void examine(const string objetoDeseado);
	void open(const string objetoDeseado);
	void close(const string objetoDeseado);
	void unlock(const string objetoDeseado);
	void poison(const string objetoDeseado);
	void give(const string objetoDeseado, const string NPCDeseado);
	void stab(const string Victima);
	void kill(Entidad * entidad);
	void cut(const string objetoDeseado, const string herramienta);
	void talk(const string NPCDeseado);

	void nombrarObjetosContenidos(const Entidad* entidad);
	Entidad* buscarUltimoPadre(Entidad* entidad);
	void prefinale();
	void die();
	void finale();
};

#endif //__Nivel__