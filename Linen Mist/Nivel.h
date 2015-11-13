#ifndef __Nivel__
#define __Nivel__

#include <vector>
#include <string>
#include "Entidad.h"

using namespace std;

//Nivel. Clase que contiene todas las entidades del juego
//y administra las interacciones entre ellas y el avance
//de la trama
class Nivel
{
public:
	Nivel();

	void operacion(const vector<string> operacion) const; //Todo: ¿Pasar como puntero?

private :
	vector<Entidad> entidades;
};

#endif //__Nivel__