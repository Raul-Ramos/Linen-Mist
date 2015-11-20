#include "stdafx.h"
#include "Objeto.h"

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
Objeto::Objeto(const char* nombre, const char* descripcion, Entidad* padre, const TipoObjeto tipoObjeto) :
Entidad(nombre, descripcion, padre), tipoObjeto(tipoObjeto)
{
	tipo = ITEM;
}

//Gets/Sets
TipoObjeto Objeto::get_tipoObjeto() const {return tipoObjeto;}
void Objeto::set_tipoObjeto(const TipoObjeto tipoObjeto) { this->tipoObjeto = tipoObjeto; }
