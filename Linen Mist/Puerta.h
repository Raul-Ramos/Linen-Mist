#ifndef __Puerta__
#define __Puerta__

#include "EntidadCerrable.h"
#include "Habitacion.h"

using namespace std;

//Puerta. Entidad cerrable que conecta dos habitaciones (padre y destino).
class Puerta : public EntidadCerrable
{
public:
	Puerta(const char* nombre, const char* descripcion, Entidad* padre, Habitacion* destino = NULL, const TipoCerrable tipoCerrable = PERMACLOSED, const bool cerrado = true, const bool bloqueado = true);

	Habitacion* get_destino() const;

private:
	Habitacion* destino;
};

#endif //__Puerta__