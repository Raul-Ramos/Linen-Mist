#include "stdafx.h"
#include "NPC.h"

//NPC. Entidad que representa un personaje no controlado
//por el jugador.
//Puede custodiar varias salidas de una habitación, evitando que se usen.
//Tiene un mensaje personalizado para cuando muere
NPC::NPC(const char * nombre, const char * descripcion, Entidad * padre, char * mensajeMuerte, const TipoNPC tipoNPC):
	Entidad(nombre, descripcion, padre), mensajeMuerte(mensajeMuerte), tipoNPC(tipoNPC)
{
	guardia = new vector<OrientacionSalida>();
	tipo = TIPONPC;
	this->vida = 100;
}

//Gets/Sets
int NPC::get_vida() const{return vida;}
void NPC::set_vida(const int vida) { this->vida = vida; }
vector<OrientacionSalida>* NPC::get_guardia() { return guardia; }
void NPC::set_guardia(vector<OrientacionSalida>* guardia) { this->guardia = guardia; }
char * NPC::get_mensajeMuerte(){ return mensajeMuerte; }
TipoNPC NPC::get_tipoNPC() { return tipoNPC; }