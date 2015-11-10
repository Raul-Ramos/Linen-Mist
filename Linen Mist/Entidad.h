#ifndef __Entidad__
#define __Entidad__

using namespace std;

//Enum sobre los distintos tipos de entidad
enum TipoDeEntidad
{
	UNDEFINDED,
	ITEM,
	HABITACION
};

//Entidad. Existencia material dentro del juego, con un nombre
// y una descripcion y que se puede examinar.
class Entidad
{
public:
	Entidad(const char* nombre, const char* descripcion);
	virtual ~Entidad();

	virtual void get_nombre() const;
	virtual void set_nombre(const char* nombre);	
	virtual void get_descripcion() const;
	virtual void set_descripcion(const char* descripcion);

protected :
	TipoDeEntidad tipo;
	string nombre;
	string description;
};

#endif //__Entidad__