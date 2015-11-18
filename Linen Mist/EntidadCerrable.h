#ifndef __EntidadCerrable__
#define __EntidadCerrable__

#include "Entidad.h"

using namespace std;

// Tipo de cerrable
enum TipoCerrable
{
	COMUN = 0,					// Se puede abrir y cerrar libremente
	CANDADO,					// Se puede abrir con una llave o con una ganzúa
	CLAVE,						// Contiene un panel con una contraseña
	PERMACLOSED					// Está permanentemente cerrado
};

//Entidad cerrable. Entidad que tiene la propiedad de ser
//abierto y cerrado mediante comandos. Cerrarlo no permite
//acceder a su contenido.
//Tambien puede estar bloqueado (cerrado con llave);
class EntidadCerrable : public Entidad
{
public:
	EntidadCerrable(const char* nombre, const char* descripcion, Entidad* padre, const TipoCerrable tipoCerrable = COMUN, const bool cerrado = true, const bool bloqueado = true);

	bool get_cerrado() const;
	void set_cerrado(const bool cerrado);
	bool get_bloqueado() const;
	void set_bloqueado(const bool bloqueado);	
	TipoCerrable get_tipoCerrable() const;

private :
	TipoCerrable tipoCerrable;
	bool cerrado;
	bool bloqueado;
};

#endif //__EntidadCerrable__