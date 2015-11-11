#ifndef __Objeto__
#define __Objeto__

#include <string>
#include "Entidad.h"

using namespace std;

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
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