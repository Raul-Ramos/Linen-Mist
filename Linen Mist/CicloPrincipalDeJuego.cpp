// CicloPrincipalDeJuego.cpp: contiene el ciclo principal de juego
//
#include "stdafx.h"

#include "iostream"
#include "string"

#include "CicloPrincipalDeJuego.h"

using namespace std;

void CicloDeJuego::iniciar()
{
	//Comando de entrada
	string comando;
   
	//Ciclo de juego
    while(1 == 1)
	{
		//Introducci�n del nuevo comando
        comando.clear();
        cout << "> ";
        getline(cin, comando);

		//Separaci�n de palabras del comando
		separarPalabras(comando);

    }
}

void CicloDeJuego::separarPalabras (string comando) {

}