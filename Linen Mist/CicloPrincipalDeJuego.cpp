// CicloPrincipalDeJuego.cpp: contiene el ciclo principal de juego
//
#include "stdafx.h"

#include "CicloPrincipalDeJuego.h"
#include "Nivel.h"

using namespace std;

void CicloDeJuego::iniciar()
{
	cout << "_____________________________________________________\n  Linen Mist- Raul Ramos Macias - @MetroGoldyMayer  \n_____________________________________________________" ;

	//Genera el mundo
	Nivel* nivel = new Nivel();

	//Comando de entrada
	string comando;
	//Vector conteniendo el comando separado por espacios
	vector<string> instrucciones;
   
	//Ciclo de juego
    while(1 == 1)
	{
		//Introducción del nuevo comando
        comando.clear();
        cout << "\n\n> ";
        getline(cin, comando);

		//Separación de palabras del comando
		instrucciones.clear();
		separarPalabras(comando, instrucciones);
		nivel->operacion(instrucciones);

		if (nivel->isGameOver() == true) {
			delete nivel;
			nivel = new Nivel();
		}
	}
}

//Entra un string de varias palabras y un vector string
//Devuelve el vector de strings con las palabras separadas
vector<string> CicloDeJuego::separarPalabras(const string &comando, vector<string> &elementos) {

	stringstream ss(comando);
	string palabra;

	//Se van leyendo palabras usando como separador un espacio
	//y se guardan en el vector con push_back
    while (getline(ss, palabra, ' ')) {

		//Pasa la palabra a mayusculas
		transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);

		//Almacena la palabra en el voctor Elementos
        elementos.push_back(palabra);
    }

    return elementos;
}