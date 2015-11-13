// Nivel. Clase que contiene todas las entidades del juego
// y administra las interacciones entre ellas y el avance
// de la trama

#include "stdafx.h"
#include <iostream>
#include <algorithm>

#include "Nivel.h"
#include "Habitacion.h"

using namespace std;

Nivel::Nivel(){

	//Inicializacion del habitaciones
	Habitacion* frontal = new Habitacion("porch", "porch description");
	Habitacion* jardin = new Habitacion("garden", "garden description");
	Habitacion* barbacoa = new Habitacion("barbecue place", "barbecue place description");
	Habitacion* trasera = new Habitacion("backyard", "backyard description");
	Habitacion* casaDelArbol = new Habitacion ("treehouse interior", "treehouse interior description");
	Habitacion* garage = new Habitacion("garage","garage description");
	Habitacion* cocina = new Habitacion("kitchen", "kitchen description");
	Habitacion* recibidor = new Habitacion("entrance hall", "entrance hall description");
	Habitacion* despensa = new Habitacion("pantry ", "pantry  description");
	Habitacion* rellano = new Habitacion("landing", "landing description");
	Habitacion* estudio = new Habitacion("study", "study description");
	Habitacion* niebla = new Habitacion("linen mist", "linen mist description", TipoHabitacion::NIEBLA);

	//Conexiones entre habitaciones
	frontal->AsignarEnlace(NORTE,barbacoa, false);
	frontal->AsignarEnlace(SUR,jardin, false);
	frontal->AsignarEnlace(OESTE,niebla, true);

	jardin->AsignarEnlace(OESTE,frontal,false);
	jardin->AsignarEnlace(ESTE,trasera,false);
	jardin->AsignarEnlace(ARRIBA,casaDelArbol,true);
	
	barbacoa->AsignarEnlace(OESTE,frontal,false);
	barbacoa->AsignarEnlace(ESTE,trasera,false);

	trasera->AsignarEnlace(NORTE, barbacoa, false);
	trasera->AsignarEnlace(SUR,jardin,false);
	trasera->AsignarEnlace(OESTE,garage,true);
	
	garage->AsignarEnlace(NORTE, cocina, true);
	cocina->AsignarEnlace(OESTE, recibidor, true);
	recibidor->AsignarEnlace(NORTE, despensa, true);
	recibidor->AsignarEnlace(ARRIBA, rellano, true);
	rellano->AsignarEnlace(OESTE, estudio, true);

	//Objetos.


	//Puntero que indica dónde está el personaje
	visitando = frontal;

}

void Nivel::operacion(const vector<string> operacion) {

	//Se asegura de que se ha escrito algo
	if ( operacion.size() < 1) {
		cout << "Excuse me?";
	} else {
		//Opera según el nombre de palabras
		switch (operacion.size()) {
			case 4:
				/*
				if (operacion.at(0).compare("LOOK") == 0){
					cout << "I see";
				}
				else {cout << "I can't do that.";}
				break;
				*/

			case 3:
				/*
				if (operacion.at(0).compare("LOOK") == 0){
					cout << "I see";
				}
				else {cout << "I can't do that.";}
				break;
				*/

			case 2:
				//Funcion GO
				if (operacion.at(0).compare("GO") == 0){
					this->go(operacion.at(1));
				} // Comando no entendido
				else {cout << "I can't do that.";}
				break;

			case 1:
				/*
				if (operacion.at(0).compare("LOOK") == 0){
					cout << "I see";
				}
				else {cout << "I can't do that";}
				break;
				*/

			default:
				cout << "Only commands up to four words are accepted.";
				break;
		}
	}
}

//Funcion para ir de una habitacion a otra
void Nivel::go(const string destinoDeseado){

	//Comprueba qué dirección se ha escrito
	OrientacionSalida destino = NINGUNA;

	if (destinoDeseado.compare("NORTH") == 0){ destino = NORTE;
	} else if (destinoDeseado.compare("SOUTH") == 0){ destino = SUR;
	} else if (destinoDeseado.compare("EAST") == 0){ destino = ESTE;
	} else if (destinoDeseado.compare("WEST") == 0){ destino = OESTE;
	} else if (destinoDeseado.compare("UPSTAIRS") == 0){ destino = ARRIBA;
	} else if (destinoDeseado.compare("DOWNSTAIRS") == 0){ destino = ABAJO;
	}

	//Si se ha escrito una direccion valida
	if(destino != NINGUNA){

		//Si se puede ir donde se quiere
		Habitacion* visitar = visitando->get_salidas().at(destino);
		if (visitar != NULL){

			//Si no ha sido visitado nunca antes (fase 0), se
			//da la descripción larga y se pasa a fase 1.
			if( visitar->get_fase() == 0 ){
				visitar->set_fase(1);
				cout << visitar->get_descripcion();
			} else { //Si no, simplemente se dice que se ha regresado.
				cout << "You return to the " << visitar->get_nombre() << ".";
			}
			//Se cambia la habitacion que estamos visitando actualmente.
			visitando = visitar;

		} else { // Direccion no valida
			cout << "I can't go " << destinoDeseado << " from here.";
		}
	} else { // Direccion inexistente
		cout << "I can only go North, South, West, East, Upstairs and Downstairs.";
	}
}