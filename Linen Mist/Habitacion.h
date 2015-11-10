#ifndef __Habitacion__
#define __Habitacion__

using namespace std;

enum OrientacionSalida
{
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
	Habitacion(const char* nombre, const char* descripcion);

	void get_salidas() const;
	void set_salidas(const vector<Habitacion>* salidas);
	void get_fase() const;
	void set_fase(const int fase);

private :
	vector<Habitacion> salidas;
	int fase;
};

#endif //__Habitacion__