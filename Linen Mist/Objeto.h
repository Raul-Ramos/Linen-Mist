#ifndef __Objeto__
#define __Objeto__

#include <string>
#include "Entidad.h"

using namespace std;

enum TipoObjeto
{
	GENERICO,
	CARNE,
	VENENO,
	CARNE_ENVENENADA,
	LLAVE,
	CUCHILLO,
	TENAZAS,
	TELEFONO,
	TELEFONO_ROTO,
	DINERO,
	CONTENEDOR
};

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
//Un padre null indica que está en el inventario
class Objeto : public Entidad
{
public:
	Objeto(const char* nombre, const char* descripcion, Entidad* padre, const TipoObjeto tipoObjeto = GENERICO);

	TipoObjeto get_tipoObjeto() const;
	void set_tipoObjeto(const TipoObjeto tipoObjeto);

private :
	TipoObjeto tipoObjeto;

};

#endif //__Objeto__