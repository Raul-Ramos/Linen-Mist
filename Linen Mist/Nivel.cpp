// Nivel. Clase que contiene todas las entidades del juego
// y administra las interacciones entre ellas y el avance
// de la trama

#include "stdafx.h"
#include <iostream>
#include <algorithm>

#include "Nivel.h"
#include "Habitacion.h"
#include "Objeto.h"
#include "Puerta.h"
#include "NPC.h"

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
	frontal->AsignarEnlace(OESTE,niebla, false);

	jardin->AsignarEnlace(OESTE,frontal,false);
	jardin->AsignarEnlace(ESTE,trasera,false);
	jardin->AsignarEnlace(ARRIBA,casaDelArbol,true);
	jardin->AsignarEnlace(SUR,niebla,false);
	
	barbacoa->AsignarEnlace(OESTE,frontal,false);
	barbacoa->AsignarEnlace(ESTE,trasera,false);
	barbacoa->AsignarEnlace(NORTE,niebla, false);

	trasera->AsignarEnlace(NORTE, barbacoa, false);
	trasera->AsignarEnlace(SUR,jardin,false);
	trasera->AsignarEnlace(OESTE,garage,true);
	trasera->AsignarEnlace(ESTE,niebla, false);
	
	garage->AsignarEnlace(NORTE, cocina, true);
	cocina->AsignarEnlace(OESTE, recibidor, true);
	recibidor->AsignarEnlace(NORTE, despensa, true);
	recibidor->AsignarEnlace(ARRIBA, rellano, true);
	rellano->AsignarEnlace(OESTE, estudio, true);

	niebla->AsignarEnlace(ESTE,frontal,false);
	niebla->AsignarEnlace(NORTE,frontal,false);
	niebla->AsignarEnlace(SUR,frontal,false);
	niebla->AsignarEnlace(OESTE,frontal,false);

	//Contenedores
	Objeto* joyero = new Objeto("box", "descr", casaDelArbol, CONTENEDOR);
	entidades.emplace_back(joyero);
	Objeto* cajaHerramientas = new Objeto("toolbox", "descr", garage, CONTENEDOR);
	entidades.emplace_back(cajaHerramientas);
	EntidadCerrable* cajaFuerte = new EntidadCerrable("desk safe", "descr", estudio, CLAVE);
	entidades.emplace_back(cajaFuerte);

	//Objetos.
	entidades.emplace_back(new Objeto("poison", "descr", jardin, VENENO));
	entidades.emplace_back(new Objeto("meat", "descr", barbacoa, CARNE));
	entidades.emplace_back(new Objeto("hairpin", "descr", joyero, LLAVE));
	entidades.emplace_back(new Objeto("coin", "descr", joyero));
	entidades.emplace_back(new Objeto("photo", "descr", joyero));
	entidades.emplace_back(new Objeto("wirecutter", "descr", cajaHerramientas, TENAZAS));
	entidades.emplace_back(new Objeto("knife","descr", cocina, CUCHILLO));
	entidades.emplace_back(new Objeto("telephone","descr", recibidor, TELEFONO));
	entidades.emplace_back(new Objeto("portrait","descr", recibidor));
	entidades.emplace_back(new Objeto("money","descr", cajaFuerte, DINERO));

	//NPC
	NPC* perro = new NPC("dog", "descr", trasera, "mensjdd");
	vector<OrientacionSalida>* guardian = perro->get_guardia();
	guardian->push_back(OESTE);
	entidades.emplace_back(perro);

	//Puertas.
	entidades.emplace_back(new Puerta("front door", "descr", frontal));
	entidades.emplace_back(new Puerta("back door", "descr", trasera, garage, CANDADO));
	entidades.emplace_back(new Puerta("blue door", "descr", rellano));
	entidades.emplace_back(new Puerta("red door", "descr", rellano));

	//Puntero que indica dónde está el personaje
	visitando = niebla;

	//Añade las habitaciones a la lista
	entidades.emplace_back(frontal);
	entidades.emplace_back(jardin);
	entidades.emplace_back(barbacoa);
	entidades.emplace_back(trasera);
	entidades.emplace_back(casaDelArbol);
	entidades.emplace_back(garage);
	entidades.emplace_back(cocina);
	entidades.emplace_back(recibidor);
	entidades.emplace_back(despensa);
	entidades.emplace_back(rellano);
	entidades.emplace_back(estudio);
	entidades.emplace_back(niebla);

}

void Nivel::operacion(const vector<string> operacion) {

	//Se asegura de que se ha escrito algo
	if ( operacion.size() < 1) {
		cout << "Excuse me?";
	} else {
		//Opera según el nombre de palabras
		switch (operacion.size()) {
			case 4:
				//Funcion PUT X IN Y
				if (operacion.at(0).compare("put") == 0
					&& operacion.at(2).compare("in") == 0){
					this->drop(operacion.at(1), operacion.at(3));
				} //Funcion GIVE X TO Y
				else if (operacion.at(0).compare("give") == 0
					&& operacion.at(2).compare("to") == 0) {
					this->give(operacion.at(1), operacion.at(3));
				} //Funcion CUT X WITH Y
				else if (operacion.at(0).compare("cut") == 0
					&& operacion.at(2).compare("with") == 0) {
					this->cut(operacion.at(1), operacion.at(3));
				} // Comando no entendido
				else {cout << "You can't do that.";}
				break;

			case 3:
				//Función OPEN XX
				if (operacion.at(0).compare("open") == 0){
					this->open(operacion.at(1) + " " + operacion.at(2));
				} //Función CLOSE XX
				else if (operacion.at(0).compare("close") == 0){
					this->close(operacion.at(1) + " " + operacion.at(2));
				} //Función UNLOCK/PICKLOCK XX
				else if (operacion.at(0).compare("unlock") == 0 ||
					operacion.at(0).compare("picklock") == 0) {
					this->unlock(operacion.at(1) + " " + operacion.at(2));
				} //Función TALK TO XX
				else if (operacion.at(0).compare("talk") == 0 &&
					operacion.at(1).compare("to") == 0) {
					this->talk(operacion.at(2));
				}// Comando no entendido
				else {cout << "You can't do that.";}
				break;

			case 2:
				//Funcion GO X
				if (operacion.at(0).compare("go") == 0){
					this->go(operacion.at(1));
				} //Funcion TAKE X
				else if (operacion.at(0).compare("take") == 0){
					this->take(operacion.at(1));
				} //Funcion DROP X
				else if (operacion.at(0).compare("drop") == 0) {
					this->drop(operacion.at(1));
				} //Funcion Examine X
				else if (operacion.at(0).compare("examine") == 0) {
					//Si es "room" examina la habitación
					if (operacion.at(1).compare("room") == 0){
						this->examine(visitando->get_nombre());
					}else {
						this->examine(operacion.at(1));
					}
				} //Funcion Look (igual que examine)
				else if (operacion.at(0).compare("look") == 0) {
					if (operacion.at(1).compare("around") == 0) {
						this->examine(visitando->get_nombre());
					}
					else {
						this->examine(operacion.at(1));
					}
				} //Funcion POISON X
				else if (operacion.at(0).compare("poison") == 0) {
					this->poison(operacion.at(1));
				} //Funcion STAB X
				else if (operacion.at(0).compare("stab") == 0) {
					this->stab(operacion.at(1));
				} // Comando no entendido
				else {cout << "You can't do that.";}
				break;

			case 1:
				if (operacion.at(0).compare("LOOK") == 0){
					cout << "I see";
				}
				else {cout << "You can't do that";}
				break;

			default:
				cout << "Only commands up to four words are accepted.";
				break;
		}
	}
}

//Busca una entidad en la lista de entidades, la devuelve si le encuentra
//y si no devuelve null
Entidad * Nivel::buscarEntidad(const string entidadDeseada)
{
	//Busca una entidad cuyo nombre coincida con el deseado
	for (int i = 0; i < entidades.size(); i++){

		//Si el objeto es el que estamos buscando...
		if (entidades.at(i).get()->get_nombre().compare(entidadDeseada) == 0) {

			return entidades.at(i).get();
		}
	}

	return NULL;
}

//Funcion para tomar un objeto de la habitación actual
void Nivel::take(const string objetoDeseado){

	//Se busca el objeto deseado
	Entidad* puntero = buscarEntidad(objetoDeseado);

	//Si se ha encontrado el objeto
	if (puntero != NULL) {

		//Si es un objeto
		if (puntero->get_tipoEntidad() == ITEM) {

			//Objeto se registra en una nueva variable
			//La variable de puntero ahora se utilizará para buscar
			//el último contenedor no contenido
			Entidad* objeto = static_cast<Objeto*>(puntero);
			puntero = buscarUltimoPadre(puntero);

			//Si esta entidad es la habitacion actual, el objeto se puede tomar
			if (puntero == visitando) {

				//El padre del objeto indica a "NULL" (lo que quiere decir
				//que está en el inventario) y se avisa al usuario;
				objeto->set_padre(NULL);
				cout << "You took " << objeto->get_nombre() << ".";

			}
			else { //Si el objeto existe pero no es accesible, disimulamos
				cout << "You can't take that.";
			}
		}
		else { //Si no es un objeto
			cout << "You can't take that.";
		}
	} //Si no se ha encontrado el objeto
	else {
		cout << "You can't do that.";
	}
}

//Funcion para dejar un objeto en una habitacion u objeto capaz de contener
//otros objetos
void Nivel::drop(const string objetoDeseado, const string contenedorDeseado) {

	//Se busca el objeto deseado
	Entidad* contenido = buscarEntidad(objetoDeseado);

	//SALE - Si no se ha encontrado el objeto o no está
	//en el inventorio
	if (contenido == NULL ||
		contenido->get_padre() != NULL) {
		cout << "You don't have any object with that name.";
		return;
	}

	//Si contenedor está en null significa que se quiere dejar en la
	//habitación actual
	if (contenedorDeseado == "") {

		contenido->set_padre(visitando);
		cout << "You dropped " << contenido->get_nombre() << " to the ground.";

	} //Si el contenedor no es null, significa que se quiere dejar
	  //dentro de otro contenedor
	else {
		//Buscamos el contenedor deseado
		Entidad* contenedor = buscarEntidad(contenedorDeseado);

		//SALE - Si no se ha encontrado el contenedor
		if (contenedor == NULL) {
			cout << "You don't have any object with that name.";
			return;
		}

		//Busca la última entidad no contenida
		Entidad* puntero = buscarUltimoPadre(contenedor);

		//SALE -  Si el contenedor NO está en la habitacion o en el inventario
		//(No es accesible) o no es un item
		if (!(puntero == visitando || puntero == contenido) ||
			contenedor->get_tipoEntidad() != ITEM) {
			cout << "You can't do that.";
			return;
		}

		//Se hace cast para acceder a propiedades de Objetos
		Objeto* contenedorObj = static_cast<Objeto*>(contenedor);

		//Si es un objeto de tipo contenedor
		if (contenedorObj->get_tipoObjeto() == CONTENEDOR) {

			//Asignamos el contenedor como padre del objeto contenido
			//y avisamos al usuario
			contenido->set_padre(contenedor);
			cout << "You put " << contenido->get_nombre() << " inside " << contenedor->get_nombre() << ".";

		} //SALE - Si no es un objeto de tipo contenedor
		else {
			cout << "You can't put objects in " << contenedorObj->get_nombre() << ".";
		}
	}
}

//Funcion para ir de una habitacion a otra
void Nivel::go(const string destinoDeseado){

	//Comprueba qué dirección se ha escrito
	OrientacionSalida destino = NINGUNA;

	if (destinoDeseado.compare("north") == 0){ destino = NORTE;
	} else if (destinoDeseado.compare("south") == 0){ destino = SUR;
	} else if (destinoDeseado.compare("east") == 0){ destino = ESTE;
	} else if (destinoDeseado.compare("west") == 0){ destino = OESTE;
	} else if (destinoDeseado.compare("upstairs") == 0){ destino = ARRIBA;
	} else if (destinoDeseado.compare("downstairs") == 0){ destino = ABAJO;
	}

	//Si se ha escrito una direccion valida
	if(destino != NINGUNA){

		Habitacion* visitar = visitando->get_salidas().at(destino);

		//Se buscan puertas que puedan estar cerradas e impidan el paso
		Entidad* puntero;

		//Se recorren todas las entidades
		for (int i = 0; i < entidades.size(); i++)
		{
			puntero = entidades.at(i).get();

			//Si está en esta habitación
			if (puntero->get_padre() == visitando) {

				//Si también es una puerta
				if (puntero->get_tipoEntidad() == PUERTA) {

					//Si además va hacia el destino deseado
					Puerta* puerta = static_cast<Puerta*>(puntero);
					if (puerta->get_destino() == visitar) {

						//Si la puerta está bloqueada, se cancela
						if (puerta->get_bloqueado() == true) {
							cout << "You can't go there, the " << puerta->get_nombre() << " is locked.";
							return;
						} //Si la puerta está cerrada, se cancela
						else if (puerta->get_cerrado() == true) {
							cout << "You can't go there, the " << puerta->get_nombre() << " is closed.";
							return;
						}
					}
				}

				//Si es un NPC y está vivo
				if (puntero->get_tipoEntidad() == TIPONPC &&
					static_cast<NPC*>(puntero)->get_vida() > 0) {

					//Si bloquea la salida deseada, se cancela
					vector<OrientacionSalida>* guardia = static_cast<NPC*>(puntero)->get_guardia();
					for (int i = 0; i < guardia->size(); i++)
					{
						if (guardia->at(0) == destino) {
							cout << "The " << puntero->get_nombre() << " is blocking your way in that direction.";
							return;
						}
					}

				}
			}
		}

		//Se revisa si existe algún lugar al que ir realmente en esa dirección
		//(Se hace posteriormente a la busqueda de puertas para mostrar el mensaje
		//de puerta cerrada en caso de que exista)
		if (visitar != NULL){

			//Si no ha sido visitado nunca antes (fase 0), se
			//da la descripción larga y se pasa a fase 1.
			if( visitar->get_fase() == 0 ){
				visitar->set_fase(1);
				cout << visitar->get_descripcion();
			} else { //Si no, simplemente se dice que se ha regresado.
				cout << "You return to the " << visitar->get_nombre() << ".";
			}

			//Si la habitacion destino es de niebla, todos sus vecinos
			//se cambian a la habitacion de origen
			if(visitar->get_tipoHabitacion() == NIEBLA){
				visitar->AsignarEnlace(NORTE,visitando,false);
				visitar->AsignarEnlace(SUR,visitando,false);
				visitar->AsignarEnlace(ESTE,visitando,false);
				visitar->AsignarEnlace(OESTE,visitando,false);
			}

			//Se cambia la habitacion que estamos visitando actualmente.
			visitando = visitar;

		} else { // Direccion no valida
			cout << "You can't go " << destinoDeseado << " from here.";
		}
	} else { // Direccion inexistente
		cout << "You can only go North, South, West, East, Upstairs and Downstairs.";
	}
}

void Nivel::examine(const string objetoDeseado)
{
	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//Si se ha encontrado el objeto
	if (entidad != NULL) {

		//Busca la última entidad no contenida
		Entidad* puntero = buscarUltimoPadre(entidad);

		//Si el objeto está en la habitacion o en el inventario
		if (puntero == visitando || puntero == entidad) {

			//Devuelve la descripción
			cout << entidad->get_descripcion();

			//Si es una habitación o un objeto de tipo
			//contenedor, imprime su contenido
			if (entidad->get_tipoEntidad() == HABITACION || 
				(entidad->get_tipoEntidad() == ITEM &&
				static_cast<Objeto*>(entidad)->get_tipoObjeto() == CONTENEDOR)) {

				nombrarObjetosContenidos(entidad);
			}

		} //Si el objeto no está en la habitación o en el inventario
		else { cout << "You can't do that.";}
	} //Si no se ha encontrado
	else { cout << "You can't do that.";}
}

//Abre entidades cerrables
void Nivel::open(const string objetoDeseado)
{
	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//SALE - Si la entidad no es un cerrable o puerta
	if (entidad->get_tipoEntidad() != CERRABLE &&
		entidad->get_tipoEntidad() != PUERTA) {
		cout << "You can't do that.";
		return;
	}

	//Cast a cerrable para acceder a sus propiedades
	EntidadCerrable* cerrable = static_cast<EntidadCerrable*>(entidad);

	//Si ya está abierto
	if (cerrable->get_cerrado() == false) {
		cout << cerrable->get_nombre() << " is already open.";
	} //Si está bloqueado
	else if(cerrable->get_bloqueado() == true) {
		cout << cerrable->get_nombre() << " seems firmly locked.";
	} //Si no hay problemas
	else {
		cerrable->set_cerrado(false);
		cout << cerrable->get_nombre() << " is now open.";
	}

}

//TODO: VER INVENTORIO
//TODO: NO PUEDES HACER GO SI LA PUERTA ESTÁ CERRADA

//Cierra entidades cerrables
void Nivel::close(const string objetoDeseado)
{
	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//SALE - Si la entidad no es un cerrable
	if (entidad->get_tipoEntidad() != CERRABLE &&
		entidad->get_tipoEntidad() != PUERTA) {
		cout << "You can't do that.";
		return;
	}

	//Cast a cerrable para acceder a sus propiedades
	EntidadCerrable* cerrable = static_cast<EntidadCerrable*>(entidad);

	//Si ya está cerrado
	if (cerrable->get_cerrado() == true) {
		cout << "The " << cerrable->get_nombre() << " is already closed.";
	} //Si no hay problemas
	else {
		cerrable->set_cerrado(true);
		cout << "The " << cerrable->get_nombre() << " is now closed.";
	}
}

//Desbloquea entidades bloqueadas
void Nivel::unlock(const string objetoDeseado)
{
	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//SALE - Si el objeto no existe, no está en la habitación actual
	//o si la entidad no es un cerrable o puerta
	if (entidad == NULL
		|| buscarUltimoPadre(entidad) != visitando
		|| (entidad->get_tipoEntidad() != CERRABLE &&
			entidad->get_tipoEntidad() != PUERTA)) {
		cout << "You can't do that.";
	}

	//Cast a cerrable para acceder a sus propiedades
	EntidadCerrable* cerrable = static_cast<EntidadCerrable*>(entidad);

	//SALE - Si es un objeto permanentemente cerrado
	if (cerrable->get_tipoCerrable() == PERMACLOSED) {
		cout << "You can't figure out how to open this.";
		return;
	}

	//SALE - Si ya está desbloqueado
	if (cerrable->get_bloqueado() == false) {
		cout << cerrable->get_nombre() << " is already unlocked.";
		return;
	}

	//Si está cerrada por candado
	if (cerrable->get_tipoCerrable() == CANDADO) {

		//Busca una llave en el inventorio
		Objeto* llave = NULL;
		Entidad* puntero;
		int indice;

		for (indice = 0; indice < entidades.size(); indice++)
		{
			//Si está en el inventorio, es un item y es una llave,
			//busqueda resuelta
			puntero = entidades.at(indice).get();
			if (puntero->get_padre() == NULL &&
				puntero->get_tipoEntidad() == ITEM &&
				static_cast<Objeto*>(puntero)->get_tipoObjeto() == LLAVE) {
				llave = static_cast<Objeto*>(puntero);
				break;
			}
		}

		//SALE - Si no se ha encontrado
		if (llave == NULL) {
			cout << "You can't figure out how to open this.";
			return;
		}

		//Si nada más falla, se desbloquea
		cout << "The " << cerrable->get_nombre() << " has been unlocked. However, you broke the " << llave->get_nombre() << " in the process.";
		cerrable->set_bloqueado(false);
		entidades.erase(entidades.begin() + indice);

	}
}

//Envenena entidades
void Nivel::poison(const string objetoDeseado)
{
	//Se busca el veneno
	Entidad* puntero;
	Objeto* veneno = NULL;
	int indice;

	for (indice = 0; indice < entidades.size(); indice++)
	{
		//Si está en el inventario, es un item y es veneno,
		//busqueda resuelta
		puntero = entidades.at(indice).get();
		if (puntero->get_padre() == NULL &&
			puntero->get_tipoEntidad() == ITEM &&
			static_cast<Objeto*>(puntero)->get_tipoObjeto() == VENENO) {
			veneno = static_cast<Objeto*>(puntero);
			break;
		}
	}

	//Si no se ha encontrado
	if (veneno == NULL) {
		cout << "You don't have any poison.";
		return;
	}

	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//Si no se ha encontrado
	if (entidad == NULL) {
		cout << "You can't do that";
		return;
	}

	//Busca la última entidad no contenida
	puntero = buscarUltimoPadre(entidad);

	//Si el objeto no está en el inventario o en la habitacion actual
	if (puntero != entidad &&
		puntero != visitando) {
		cout << "You can't do that.";
		return;
	}

	//Si es un NPC
	if (entidad->get_tipoEntidad() == TIPONPC){
		cout << "I can't poison " << entidad->get_nombre() << " directly.";
		return;
	}

	//Si es la carne
	if (entidad->get_tipoEntidad() == ITEM &&
		static_cast<Objeto*>(entidad)->get_tipoObjeto() == CARNE) {

		//Se envenena la carne y se elimina el veneno
		Objeto* carne = static_cast<Objeto*>(entidad);
		carne->set_tipoObjeto(CARNE_ENVENENADA);
		carne->set_descripcion("A poisoned meatball. It doesn't make much of a difference with your mother-in-law cooking.");

		cout << "You poisoned " << entidad->get_nombre() << ". You used all the poison.";
		entidades.erase(entidades.begin() + indice);

	} //Si no es la carne
	else {
		cout << "That doesn't make any sense.";
	}
}

//Da un objeto a otra entidad
void Nivel::give(const string objetoDeseado, const string NPCDeseado)
{
	//Se busca el objeto a dar
	Entidad* origen = buscarEntidad(objetoDeseado);

	//Si no se ha encontrado el objeto
	if (origen == NULL) {
		cout << "You don't have any " << objetoDeseado;
		return;
	}
	
	Entidad* puntero = buscarUltimoPadre(origen);

	//Si no está en el inventario
	if (puntero != origen) {
		cout << "You don't have any " << objetoDeseado;
		return;
	}

	//Se busca el NPC al que dar
	Entidad* destino = buscarEntidad(NPCDeseado);

	// Si no se ha encontrado el objeto
	if (destino == NULL) {
		cout << "You can't give that to " << NPCDeseado;
		return;
	}

	puntero = buscarUltimoPadre(destino);

	//Si no está en la habitación actual o no es un NPC
	if (puntero != visitando ||
		destino->get_tipoEntidad() != TIPONPC) {
		cout << "You can't give that to " << NPCDeseado;
		return;
	}

	Objeto* objeto = static_cast<Objeto*>(origen);
	NPC* npc = static_cast<NPC*>(destino);
	
	if(objeto->get_tipoObjeto() == CARNE ||
		objeto->get_tipoObjeto() == CARNE_ENVENENADA){

		cout << NPCDeseado << " happily eats the meatball.";

		//Si está envenada, mata al NPC
		if (objeto->get_tipoObjeto() == CARNE_ENVENENADA) {
			kill(npc);
		}

		//Elimina la carne
		for (int i = 0; i < entidades.size(); i++) {
			if (entidades.at(i).get() == origen) { entidades.erase(entidades.begin() + i); }
		}

	} //Si no es nada de lo anterior
	else {
		cout << NPCDeseado << " seems uninterested in " << objetoDeseado << ".";
	}

}

//Apuñala a una entidad
void Nivel::stab(const string objetoDeseado)
{
	//Se busca el cuchillo
	Entidad* puntero;
	Objeto* cuchillo = NULL;
	int indice;

	for (int i = 0; indice < entidades.size(); indice++)
	{
		//Si está en el inventario, es un item y es un cuchillo,
		//busqueda resuelta
		puntero = entidades.at(indice).get();
		if (puntero->get_padre() == NULL &&
			puntero->get_tipoEntidad() == ITEM &&
			static_cast<Objeto*>(puntero)->get_tipoObjeto() == CUCHILLO) {
			cuchillo = static_cast<Objeto*>(puntero);
			break;
		}
	}

	//Si no se ha encontrado
	if (cuchillo == NULL) {
		cout << "You don't have any knife.";
		return;
	}

	//Se busca el objeto deseado
	Entidad* entidad = buscarEntidad(objetoDeseado);

	//Busca la última entidad no contenida
	puntero = buscarUltimoPadre(entidad);

	//Si el objeto no está en la habitacion actual
	if (puntero != visitando) {
		cout << "You can't do that.";
		return;
	}

	//Mata a la entidad
	kill(puntero);

}

//Mata a una entidad
void Nivel::kill(Entidad * entidad)
{
	//Si es un NPC
	if (entidad->get_tipoEntidad() == TIPONPC) {

		NPC* victima = static_cast<NPC*>(entidad);

		//Si no está muerto
		if (victima->get_vida() > 0) {
			victima->set_vida(0);
			cout << victima->get_mensajeMuerte();
		}
		else {
			cout << victima->get_nombre() << " is already dead.";
		}

		return;
	}
}

//Corta algo
void Nivel::cut(const string objetoDeseado, const string herramienta)
{
	//Se busca el objeto a cortar
	Entidad* origen = buscarEntidad(objetoDeseado);

	//Si no se ha encontrado el objeto
	if (origen == NULL) {
		cout << "You can't do that.";
		return;
	}

	Entidad* puntero = buscarUltimoPadre(origen);

	//Si no está en el inventario o habitacion actual,
	// y no es un objeto
	if ((puntero != origen
		&& puntero != visitando)
		|| origen->get_tipoEntidad() != ITEM) {
		cout << "You can't do that.";
		return;
	}

	//Se busca la entidad con la que cortar
	Entidad* destino = buscarEntidad(herramienta);

	// Si no se ha encontrado el objeto
	if (destino == NULL) {
		cout << "You can't do that.";
		return;
	}

	puntero = buscarUltimoPadre(destino);

	//Si no está en el inventorio
	if (puntero != destino 
		|| destino->get_tipoEntidad() != ITEM) {
		cout << "You can't do that.";
		return;
	}

	Objeto* Oobjeto = static_cast<Objeto*>(origen);
	Objeto* Oherramienta = static_cast<Objeto*>(destino);

	if (Oobjeto->get_tipoObjeto() == TELEFONO
		&& Oherramienta->get_tipoObjeto() == TENAZAS) {

		Oobjeto->set_tipoObjeto(TELEFONO_ROTO);
		Oobjeto->set_descripcion(Oobjeto->get_descripcion().append(" The wire is cut, so it doesn't have line."));
		cout << "You have cut the phone wire.";


	} //Si no es nada de lo anterior
	else {
		cout << "Nothing happened.";
	}


}

//Habla con alguien
void Nivel::talk(const string NPCDeseado)
{
	cout << NPCDeseado << " doesn't seem interested in talking.";
}

//Imprime por pantalla un mensaje nombrando todas las entidades
//directamente contenidas por la entidad que se pasa como parámetro
void Nivel::nombrarObjetosContenidos(const Entidad * entidad)
{
	vector<string> contiene;

	//Devuelve el nombre de las entidades que tengan la entidad pasada
	//a la función como parametro asignadas como padre
	for (int i = 0; i < entidades.size(); i++) {
		if (entidades.at(i).get()->get_padre() == entidad) {
			contiene.push_back(entidades.at(i).get()->get_nombre());
		}
	}

	//Imprime lo encontrado
	cout << "\n\n";
	if (contiene.size() == 0) {
		cout << "There's nothing particularly useful in it.";}
	else {
		string mensaje = "Contains ";

		for (int i = 0; i < contiene.size(); i++)
		{
			if (i == contiene.size() - 1 && contiene.size() > 1) {
				mensaje.append(" and ");
			} else if (i > 0) {
				mensaje.append(", ");
			}

			mensaje.append(contiene.at(i));
		}

		cout << mensaje;
	}
}

//Se le pasa una entidad como parámetro y busca la última
//entidad que lo contiene
Entidad * Nivel::buscarUltimoPadre(Entidad * entidad)
{
	Entidad* puntero = entidad;
	while (puntero->get_padre() != NULL) {
		puntero = puntero->get_padre();
	}
	return puntero;
}
