#ifndef __Entidad__
#define __Entidad__

#include <string>

using namespace std;

//Enum sobre los distintos tipos de entidad
enum TipoDeEntidad
{
	UNDEFINED,
	ITEM,
	HABITACION
};

//Entidad. Existencia material dentro del juego, con un nombre
// y una descripcion y capaz de ser examinada.
class Entidad
{
public:
	Entidad(const char* nombre, const char* descripcion, Entidad* padre);
	//virtual ~Entidad();

	string get_nombre() const;
	void set_nombre(const string nombre);	
	string get_descripcion() const;
	void set_descripcion(const string descripcion);
	TipoDeEntidad get_tipoEntidad() const;
	Entidad* get_padre() const;
	void set_padre(Entidad* padre);

protected :
	TipoDeEntidad tipo;
	string nombre;
	string descripcion;
	Entidad* padre;
};

#endif //__Entidad__