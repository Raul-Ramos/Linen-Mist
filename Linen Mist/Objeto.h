#ifndef __Objeto__
#define __Objeto__

#include <string>
#include "Entidad.h"

using namespace std;

enum tipoObjeto
{
	NORMAL,
	CARNE,
	VENENO,
	LLAVE,
	CUCHILLO,
	TENAZAS,
	TELEFONO,
	DINERO
};

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
//Un padre null indica que está en el inventario
class Objeto : public Entidad
{
public:
	Objeto(const char* nombre, const char* descripcion, Entidad* padre);

	Entidad* get_padre() const;
	void set_padre(Entidad* padre);	

protected :
	Entidad* padre;
};

#endif //__Objeto__