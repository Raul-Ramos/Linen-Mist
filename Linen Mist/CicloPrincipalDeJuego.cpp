// CicloPrincipalDeJuego.cpp: contiene el ciclo principal de juego
//
#include "stdafx.h"

#include "iostream"
#include "string"
#include "sstream"
#include "vector"

#include "CicloPrincipalDeJuego.h"

using namespace std;

void CicloDeJuego::iniciar()
{
	//Comando de entrada
	string comando;
	//Vector conteniendo el comando separado por espacios
	vector<string> instrucciones;
   
	//Ciclo de juego
    while(1 == 1)
	{
		//Introducción del nuevo comando
        comando.clear();
        cout << "> ";
        getline(cin, comando);

		//Separación de palabras del comando
		instrucciones.clear();
		separarPalabras(comando, instrucciones);
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
        elementos.push_back(palabra);
    }

    return elementos;
}