#ifndef __Nivel__
#define __Nivel__

#include <vector>
#include <string>
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

private :
	//Lista de entidades
	vector<Entidad> entidades;
	//Puntero que indica que habitación se está visitando
	Habitacion* visitando;

	void go(const string destinoDeseado);
};

#endif //__Nivel__