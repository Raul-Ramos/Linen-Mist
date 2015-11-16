#ifndef __ObjetoCerrable__
#define __ObjetoCerrable__

using namespace std;

enum TipoCerrable
{
	COMUN,
	LLAVE,
	CLAVE
};

//Objeto cerrable. Objeto que tiene la propiedad de ser
//abierto y cerrado mediante a comandos. Cerrarlo no permite
//acceder a su contenido.
//Tambien puede estar bloqueado (cerrado con llave);
class ObjetoCerrable : public Objeto
{
public:
	ObjetoCerrable(const char* nombre, const char* descripcion, Entidad* padre, const TipoCerrable tipoCerrable, const bool cerrado, const bool bloqueado);

	void get_cerrado() const;
	void set_cerrado(const bool cerrado);
	void get_bloqueado() const;
	void set_bloqueado(const bool bloqueado);	

private :
	TipoCerrable tipoCerrable;
	bool cerrado;
	bool bloqueado;
};

#endif //__Objeto__