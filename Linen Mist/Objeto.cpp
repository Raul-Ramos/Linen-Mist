#include "stdafx.h"
#include "Objeto.h"

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
Objeto::Objeto(const char* nombre, const char* descripcion, Entidad* padre, TipoObjeto tipoObjeto) :
Entidad(nombre, descripcion), padre(padre), tipoObjeto(tipoObjeto)
{
	tipo = ITEM;
}

//Gets/Sets
Entidad* Objeto::get_padre() const {return padre;}
void Objeto::set_padre(Entidad* padre) {this->padre = padre;}
TipoObjeto Objeto::get_tipoObjeto() const {return tipoObjeto;}