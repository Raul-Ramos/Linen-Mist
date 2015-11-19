#ifndef __NPC__
#define __NPC__

#include "Entidad.h"
#include "Habitacion.h"

using namespace std;

// Tipo de NPC
enum TipoNPC
{
	CORRIENTE,
	FINALE
};

//NPC. Entidad que representa un personaje no controlado
//por el jugador.
//Puede custodiar varias salidas de una habitación, evitando que se usen.
//Tiene un mensaje personalizado para cuando muere
class NPC : public Entidad
{
public:
	NPC(const char* nombre, const char* descripcion, Entidad* padre, char* mensajeMuerte, const const TipoNPC tipoNPC = CORRIENTE);

	int get_vida() const;
	void set_vida(const int vida);
	vector<OrientacionSalida>* get_guardia();
	void set_guardia(vector<OrientacionSalida>* GUARDIA);
	char* get_mensajeMuerte();
	TipoNPC get_tipoNPC();


private:
	int vida;
	vector<OrientacionSalida>* guardia;
	char* mensajeMuerte;
	TipoNPC tipoNPC;
};

#endif //__NPC__