#include "stdafx.h"
#include "EntidadCerrable.h"

//Entidad cerrable. Entidad que tiene la propiedad de ser
//abierto y cerrado mediante comandos. Cerrarlo no permite
//acceder a su contenido.
//Tambien puede estar bloqueado (cerrado con llave);
EntidadCerrable::EntidadCerrable(const char * nombre, const char * descripcion, Entidad * padre, const TipoCerrable tipoCerrable, const bool cerrado, const bool bloqueado) :
	Entidad(nombre, descripcion, padre), tipoCerrable(tipoCerrable), cerrado(cerrado), bloqueado(bloqueado)
{
	tipo = CERRABLE;
}

//Gets/Sets
bool EntidadCerrable::get_cerrado() const { return cerrado; }
void EntidadCerrable::set_cerrado(const bool cerrado) { this->cerrado = cerrado; }
bool EntidadCerrable::get_bloqueado() const { return bloqueado;  }
void EntidadCerrable::set_bloqueado(const bool bloqueado) { this->bloqueado = bloqueado; }
TipoCerrable EntidadCerrable::get_tipoCerrable() const { return tipoCerrable; }