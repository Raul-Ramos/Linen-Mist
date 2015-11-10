#ifndef __Objeto__
#define __Objeto__

using namespace std;

//Objeto. Una entidad contenida por otra que es capaz de ser
//recogida, almacenada, dejada...
class Objeto : public Entidad
{
public:
	Objeto(const char* nombre, const char* descripcion, const Entidad* padre);

	void get_padre() const;
	void set_padre(const Entidad* padre);	

protected :
	Entidad* padre;
};

#endif //__Objeto__