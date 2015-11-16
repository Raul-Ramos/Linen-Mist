#include <iostream>

#include "stdafx.h"
#include "Entidad.h"

//Entidad. Existencia material dentro del juego, con un nombre
// y una descripcion y capaz de ser examinada.
Entidad::Entidad(const char* nombre, const char* descripcion, Entidad* padre) :
nombre(nombre), descripcion(descripcion), padre(padre)
{
	tipo = UNDEFINED;
}

//Gets/Sets
string Entidad::get_nombre() const {return nombre;}
void Entidad::set_nombre(const string nombre) {this->nombre = nombre;}
string Entidad::get_descripcion() const {return descripcion;}
void Entidad::set_descripcion(const string descripcion){this->descripcion = descripcion;}
TipoDeEntidad Entidad::get_tipoEntidad() const { return tipo; }
Entidad* Entidad::get_padre() const { return padre; }
void Entidad::set_padre(Entidad* padre) { this->padre = padre; }