#include "stdafx.h"
#include "Habitacion.h"

//Habitacion. Entidad no contenida por otra que conecta a otras 
//seis habitaciones mediante referencias (los puntos cardinales,
//encima y debajo).

//La variable fase es un indicador narrativo. Empieza en 0.
//Al visitarse por primera vez la sala (valor 0), esta se describe con detalle y
//se pasa a 1. Al visitarla en fase 1, la descripción se reduce singificativamente.
//Valores superiores a 1 se utilizan para representar diferentes eventos narrativos
//posteriores según se necesite.
Habitacion::Habitacion(const char* nombre, const char* descripcion) :
Entidad(nombre, descripcion)
{
	tipo = HABITACION;
	fase = 0; //TODO: Declaracion en header?

	salidas[NORTE] = NULL;
	salidas[SUR] = NULL;
	salidas[ESTE] = NULL;
	salidas[OESTE] = NULL;
	salidas[ARRIBA] = NULL;
	salidas[ABAJO] = NULL;
}

//Gets/Sets
vector<Habitacion*> Habitacion::get_salidas() const {return salidas;}
void Habitacion::set_salidas(const vector<Habitacion*> salidas) {this->salidas = salidas;}
int Habitacion::get_fase() const {return fase;}
void Habitacion::set_fase(const int fase) {this->fase = fase;}