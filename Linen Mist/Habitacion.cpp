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
Habitacion::Habitacion(const char* nombre, const char* descripcion, const TipoHabitacion tipoHab) :
Entidad(nombre, descripcion), tipoHabitacion(tipoHab)
{
	tipo = HABITACION;
	fase = 0; //TODO: Declaracion en header?

	//Inicializa las salidas
	for( int i = 0; i < 6; ++i )
	{
		salidas.push_back(NULL);
	}
}

//Asigna una habitacion como vecino. La dirección indica la dirección del vecino, el vecino es un puntero a este
//y si bidireccional está activado, la habitación vecina se enlaza a la actual en la dirección contraria
void Habitacion::AsignarEnlace(const OrientacionSalida direccion, Habitacion* vecino, const bool bidireccional){

	salidas.at(direccion) = vecino;

	
	if(bidireccional){
		OrientacionSalida direccionPropia;

		
		switch( direccion ) {
			case NORTE: direccionPropia = SUR; break;
			case SUR: direccionPropia = NORTE; break;
			case OESTE: direccionPropia = ESTE; break;
			case ESTE: direccionPropia = OESTE; break;
			case ABAJO: direccionPropia = ARRIBA; break;
			default: direccionPropia = ABAJO; break;
		}

		vecino->AsignarEnlace(direccionPropia, this, false);
	}
	
}

//Gets/Sets
vector<Habitacion*> Habitacion::get_salidas() const {return salidas;}
int Habitacion::get_fase() const {return fase;}
void Habitacion::set_fase(const int fase) {this->fase = fase;}
TipoHabitacion Habitacion::get_tipoHabitacion() const {return tipoHabitacion;}