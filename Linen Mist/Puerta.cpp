#include "stdafx.h"
#include "Puerta.h"

//Puerta. Entidad cerrable que conecta dos habitaciones.
//Si el destino es NULL, la puerta permanece permanentemente
//cerrada.
Puerta::Puerta(const char * nombre, const char * descripcion, Entidad * padre,
	Habitacion * destino, const TipoCerrable tipoCerrable, const bool cerrado, const bool bloqueado) :
	EntidadCerrable(nombre, descripcion, padre, tipoCerrable, cerrado, bloqueado), destino(destino)
{
	tipo = PUERTA;
}

//Gets/Sets
Habitacion* Puerta::get_destino() const { return destino; }