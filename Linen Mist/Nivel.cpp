// Nivel. Clase que contiene todas las entidades del juego
// y administra las interacciones entre ellas y el avance
// de la trama

#include "stdafx.h"

#include "Nivel.h"
#include "Habitacion.h"
#include "Objeto.h"
#include "Puerta.h"
#include "NPC.h"

using namespace std;

Nivel::Nivel(){

	gameOver = false;
	tiempo = NULL;

	//Inicializacion del habitaciones
	char* texto = { "[You walk and walk in the linen mist. It seems endless. A menacing, limitless nightmare whose will you're following. After walking what feels like hours, the mist seems to be fading. Seems like it's midnight. Walking in that direction, you see a shadowy structure in front of you].\n\nYou're in front of a big suburb's house. White walls and red roof, it feels like the typical house you've always seen in fiction. You feel the impulse to get inside." };
	Habitacion* frontal = new Habitacion("porch",texto);
	texto = { "The south side of the house is a garden. Little plots contain a large variety of flora; tomatoes, artichokes, marigolds, saffron...Seems like someone was gardening not long ago, as some equipment is left under a shed.\nThe biggest tree has a tire in the ground, with two ropes - with their extremes broken - firmly tied to it. Upon further inspection you see there's a well hidden treehouse, with some stairs to climb them." };
	Habitacion* jardin = new Habitacion("garden", texto);
	texto = { "This place has a lot of benches and a grill. Seems like had a barbecue party no long ago. From outside the fence, the omnipresent mist awaits."};
	Habitacion* barbacoa = new Habitacion("barbecue place", texto);
	texto = { "The backyard. There's a backdoor, but there's a stupid dog guarding it. Upon seein you, he barked loudly. He must have awaken the entire neighborhood..." };
	Habitacion* trasera = new Habitacion("backyard", texto);
	texto = { "The treehouse interior structure is solid, but its decoration is chaotic. The dispersed pencils, the drawings in the floor...Seems like some childs had a meeting not long ago." };
	Habitacion* casaDelArbol = new Habitacion ("treehouse interior", texto);
	texto = { "You're inside. It's great not to have the mist presence upon you. The garage isn't used as a garage. Rather, it's a amateur carpenter workshop. I'm sure the workbench where the toolbox is was the one used for building that treehouse." };
	Habitacion* garage = new Habitacion("garage",texto);
	texto = { "The kitchen. Nothing particulary great about it. The fridge has a lot of child paintings, but everything seems a bit disused. Seems like they go to restaurants a lot.\nThere's a calendar hanging in the wall. 1987...So that's the year we're on." };
	Habitacion* cocina = new Habitacion("kitchen", texto);
	texto = { "The entrance hall. There's a pantry just north, and there's stairs to the second floor. In a corner you can see a small altar to a woman, photo included." };
	Habitacion* recibidor = new Habitacion("entrance hall", texto);
	texto = { "As you enter the pantry, your heart freezes. It's a child...No, it's Annah. She's whimping. You look at her eyes. She knows what you did. She knows your face. A cold feeling crosses your body. You...you can't leave it like this. But...\n\nThere's nowhere no go. There's no scape.\n\nYou have to do it." };
	Habitacion* despensa = new Habitacion("pantry ", texto);
	texto = { "The landing. There's a blue door and a red door. To the west, another room." };
	Habitacion* rellano = new Habitacion("landing", texto);
	texto = { "The study. Seems like someone has spend a lot of time in here lately. Maybe it's a workingplace? There are a lot of sketches everywhere. Whatever result the artist wants, he isn't getting it." };
	Habitacion* estudio = new Habitacion("study", texto);
	texto = { "The linen mist. The omnipresent presence." };
	Habitacion* niebla = new Habitacion("linen mist", texto, TipoHabitacion::NIEBLA);

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

	entidades.emplace_back(new NPC("girl", "descr", despensa, "You did it", FINALE));

	//Puertas.
	entidades.emplace_back(new Puerta("front door", "descr", frontal));
	entidades.emplace_back(new Puerta("back door", "descr", trasera, garage, CANDADO));
	entidades.emplace_back(new Puerta("pantry door", "descr", recibidor, despensa, CANDADO));
	entidades.emplace_back(new Puerta("pantry exit", "descr", despensa, recibidor));
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

	//NARRATIVA - Si en el finale han pasado mas de 15 segundos
	if (tiempo != NULL && difftime(time(NULL), tiempo) > 15) {
		die();
		return;
	}

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
				} //Funcion Look / Examine (igual que examine)
				else if (operacion.at(0).compare("look") == 0 ||
					operacion.at(0).compare("examine") == 0 ) {
					this->examine(operacion.at(1) + " " + operacion.at(2));
				} // Comando no entendido
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

//Get/Set
bool Nivel::isGameOver() const { return gameOver;}

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
			Objeto* objeto = static_cast<Objeto*>(puntero);
			puntero = buscarUltimoPadre(puntero);

			//Si esta entidad es la habitacion actual, el objeto se puede tomar
			if (puntero == visitando) {

				//El padre del objeto indica a "NULL" (lo que quiere decir
				//que está en el inventario) y se avisa al usuario;
				objeto->set_padre(NULL);
				cout << "You took " << objeto->get_nombre() << ".";

				//NARRATIVA: Si el objeto cogido es dinero, en el hall
				//se pasa a fase 2
				if (objeto->get_tipoObjeto() == DINERO) {
					Habitacion * hall = static_cast<Habitacion*>(buscarEntidad("entrance hall"));
					if (hall->get_fase() == 1) {
						hall->set_fase(2);
					}
				}

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
						if (guardia->at(i) == destino) {
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

			//NARRATIVA: Si la habitacion destino tiene fase 2
			//empieza el prefinale.
			if (visitar->get_fase() == 2) {
				prefinale();
			}

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

			//Si es una habitación, un objeto de tipo
			//contenedor o un objeto cerrable abierto, imprime su contenido
			if ((entidad->get_tipoEntidad() == HABITACION) ||
				(entidad->get_tipoEntidad() == ITEM && static_cast<Objeto*>(entidad)->get_tipoObjeto() == CONTENEDOR) ||
				(entidad->get_tipoEntidad() == CERRABLE && static_cast<EntidadCerrable*>(entidad)->get_cerrado() == false)) {

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
	else if (cerrable->get_tipoCerrable() == CLAVE) {

		string comando;
		cout << "Enter code: ";
		getline(cin, comando);

		if (comando.compare("1950") == 0) {
			cout << "\n\nCorrect code. Unlocked.";
			cerrable->set_bloqueado(false);
		}
		else {
			cout << "\n\nInvalid code. ";
		}

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

		cout << NPCDeseado << " happily eats the meatball. ";

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
void Nivel::stab(const string victima)
{
	//Se busca el cuchillo
	Entidad* puntero;
	Objeto* cuchillo = NULL;
	int indice;

	for (int indice = 0; indice < entidades.size(); indice++)
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
	Entidad* Ovictima = buscarEntidad(victima);

	//Si no se ha encontrado
	if (Ovictima == NULL) {
		cout << "You can't do that.";
		return;
	}

	//Busca la última entidad no contenida
	puntero = buscarUltimoPadre(Ovictima);

	//Si el objeto no está en la habitacion actual
	if (puntero != visitando) {
		cout << "You can't do that.";
		return;
	}

	//Mata a la entidad
	kill(Ovictima);

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

			//NARRATIVA - Acaba el quicktime event
			tiempo = NULL;

			//NARRATIVA - Si se mata al "jefe final",
			//se pasa al finale
			if (victima->get_tipoNPC() == FINALE) {
				finale();
			}

		}
		else {
			cout << victima->get_nombre() << " is already dead.";
		}

		return;
	}
	else {
		cout << "You can't kill that.";
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

void Nivel::prefinale()
{
	cout << "\n\n You're not alone. You see a middle aged man ";

	//Se busca el telefono
	Entidad* telefono = buscarEntidad("telephone");

	//Si el telefono no está en la habitacion
	if (telefono->get_padre() != visitando){
		cout << "desperately trying to find the telephone, with no success.";
	} //Si el telefono está cortado
	else if (static_cast<Objeto*>(telefono)->get_tipoObjeto() == TELEFONO_ROTO){
		cout << "desperately trying to use the phone, until his blood freezes when he notices someone has cut the wire.";
	} //Si te ha pillado, game over
	else {
		cout << "hanging the phone. A second later he notices you. Holding a revolver, he says 'I have already called the police! You have nowhere to go!'.\nYou know when to surrender. Yes, you could silence him here and now, but you won't have time to scape until the police arrives. It's pointless.\nYou get on your knees, staring at the phone. If you had done something about it...\nThe loud noise of the police's siren breaks your train of thought. You close your eyes trying to make everything disappear...\n\nBut you can't scape. Not until you do it.\n\n";
		gameOver = true;
		return;
	}

	char* muerte = {"You run towards the man like you have never run before. You can move his arm fast enough with a precise elbow hit, and he shoots to the ceiling. Out of the weapon range, you slice his throat open.\n\nYou don't feel much of a thing. It happens. You're sure you thought the house would be empty when you planned the robbery. Sometimes, things just go wrong, and you have to do something about them.\nYou only regret this has become so easy to do. You don't want to feel the same anguish, the same distress of the first time. It was the worst sensation in your life. But you should feel something...Don't you?\n\n You watch as he falls to his knees. Every word trying to get out of his mouth scapes in is neck as bubbles in a crimson lake. But he isn't looking at you. He is looking at the pantry door, which you would swear just gasped."};
	//Se crea el hombre, un NPC que no te deja ir a ninguna parte. Muere apuñalandolo
	NPC* hombre = new NPC("man","A middle aged man.",visitando,muerte);
	vector<OrientacionSalida>* guardian = hombre->get_guardia();
	guardian->push_back(OESTE);
	guardian->push_back(ESTE);
	guardian->push_back(NORTE);
	guardian->push_back(SUR);
	guardian->push_back(ARRIBA);
	guardian->push_back(ABAJO);
	entidades.emplace_back(hombre);

	//Se suelta una llave
	entidades.emplace_back(new Objeto("key", "A key to the pantry.", visitando, LLAVE));

	//Se pone en situación
	cout << " Your last step has alerted him, and he turns around. You can feel how fear takes over every muscle of his body, distorting his face in a terror grimace, making his legs tremble in disbelief.\n\n As he draws the revolver out of his pocket, a small key falls to the ground. He hysterically looks to the key, then to the pantry, then back to the key. You see an opportunity in this panic reaction, but as you make a single step, he points the gun at your.\n\nYou have been in this situation before. The dread eyes, the shaking gun...This rookie hasn't shoot before, but something is off. The finger is situated steadily in the trigger, without hesitation. He will shoot, you're sure of it. Is he protecting something?\n\nYou don't have time to think. It has come to you or him. It's not the first time you do this.\n\nIt's time to him to go.";

	//Empieza un quicktime event
	cin.ignore();
	cout << "\n\nWhen the counter reachs 5, you will have 15 seconds to do something. Think fast.";
	for (int i = 5; i > 0; i--)
	{
		cout << "\n\n" << i;
		_sleep(1000);
	}
	cout << "\n\nGO!";
	this->tiempo = time(NULL);
}

//Si pierdes el quicktime event
void Nivel::die()
{
	cout << "\n\nYou were fast. But not fast enough.\n\nYou're not sure of what gets to you before. Maybe the burning, excruciating pain in your chest. Maybe the sound of the gunpowder smell. No, it certainly was the explosion sound as the bullet left the revolver.\n\nStaring at the ceiling, resting in a pool of your own blood, you decide it doesn't matter. You hear a sound. Seems like the trembling hand of the man let the gun go. Who knows what kind of tears is he shedding. Terror at you still living presence? Horror at what he has done? Relief at killing the dangerous criminal?\n\nYou don't care. You just stare at the ceiling, incapable of doing anything more. And as you stare and everything starts to get dark, you smile. Why? Why do you feel like dying was the best you could do? Why do you feel like you have finally avoided a monster that has been hunting you for ages?\n\nSmiling gets to laughing as you imagine your face; a big smile in your lips but a confused expression everywhere else. What a stupid face you must be making!\nAnd there goes; a single relief tear, a sole explorer wanting to meet the red your clothes are soaking in.\n\nBut as your vision blurs, it resembles the mist. That linen mist. And your body panics again. You feel the sudden need to run, run away from this place. But you body doesn't answer. You feel the neeed to scream, but your mouth won't open. As the fog in your eyes becomes black you give up to insanity.\n\nYou know you will never rest. Not until you do it.\n\n";
	gameOver = true;
}

void Nivel::finale()
{
	cout << "\n\nYou just did it again.\n\nThe blood drops from the pointy end, falling all the way to the once white daisies in her dress. It feels unreal. \n\n> ";

	string comando;
	getline(cin, comando);

	cout << "\nYou want to do something, anything. \n\n> ";

	getline(cin, comando);

	cout << "\nBut your muscles won't answer. \n\n> ";
	getline(cin, comando);

	cout << "\nI hope it was worthy. \n\n> ";
	getline(cin, comando);

	cout << "\nIt's not just sadness that has stolen you body. You're not your own anymore. You don't feel anything, but you feel everything. Emotions are flooding your mind now that you've renounced to your humanity. You're nothing but a broken soul in a rusted body. \n\n> ";
	getline(cin, comando);

	cout << "\nAnd soon, it will come again. \n\n> ";
	getline(cin, comando);

	cout << "\nThe linen mist will come, and it will make you do it again. It will erase your memory and it will make you feel broken again, \n\n> ";

	for (int i = 0; i < 3; i++)
	{
		getline(cin, comando);
		cout << "\nand again,  \n\n> ";
	}
	getline(cin, comando);

	cout << "\nand again.\n\nIt's you punishement. It's your torture for what you once did. It will follow you forever. \n\n> ";
	getline(cin, comando);

	cout << "Here it comes.\n\nThe linen mist, sliding under the door. Always hunting. Always there.\n\nTry to speak. \n\n> ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	getline(cin, comando);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "Nothing. You can't even hear your own thinking. The linen mist gets in your lungs, burning like hellfire. You feel like you're choking, but trying to breathe just makes it worse and worse. \n\n> ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	getline(cin, comando);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "You fall to the ground, in an agony no man could endure. Your innards are rotting alive, your brain is being stabbed by thousands of knives. Insanity. Despair. \n\n> ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	getline(cin, comando);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	cout << "You're one with the mist. You don't feel relieved. It will end soon, but it will begin soon. The hell that will torment you forever.\n\n\n\nEven if you do it.\n\n";
	gameOver = true;
}

