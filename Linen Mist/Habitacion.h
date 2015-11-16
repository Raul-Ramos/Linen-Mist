#ifndef __Habitacion__
#define __Habitacion__

#include <string>
#include <vector>
#include "Entidad.h"

using namespace std;

//Tipo de habitación.
//Las habitaciones de niebla cambian cuando se entra en ellas
//para que todas las salidas sean la habitación por donde se ha entrado
enum TipoHabitacion
{
	NORMAL,
	NIEBLA
};

enum OrientacionSalida
{
	NINGUNA = -1,
	NORTE,
	SUR,
	ESTE,
	OESTE,
	ARRIBA,
	ABAJO
};

//Habitacion. Entidad no contenida por otra que conecta a otras 
//seis habitaciones mediante referencias (los puntos cardinales,
//encima y debajo).

//La variable fase es un indicador narrativo. Empieza en 0.
//Al visitarse por primera vez la sala (valor 0), esta se describe con detalle y
//se pasa a 1. Al visitarla en fase 1, la descripción se reduce singificativamente.
//Valores superiores a 1 se utilizan para representar diferentes eventos narrativos
//posteriores según se necesite.
class Habitacion : public Entidad
{
public:
	//Habitacion(const char* nombre, const char* descripcion);
	Habitacion(const char* nombre, const char* descripcion, const TipoHabitacion tipoHab = NORMAL, Entidad* padre = NULL);
	
	//Asigna una habitacion como vecino
	void AsignarEnlace(const OrientacionSalida direccion, Habitacion* vecino, const bool bidireccional);

	vector<Habitacion*> get_salidas() const;
	int get_fase() const;
	void set_fase(const int fase);
	TipoHabitacion get_tipoHabitacion() const;

private :
	TipoHabitacion tipoHabitacion;
	vector<Habitacion*> salidas;
	int fase;
};

#endif //__Habitacion__