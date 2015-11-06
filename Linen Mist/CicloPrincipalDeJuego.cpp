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
		//Introducción del nuevo comando
        comando.clear();
        cout << "> ";
        getline(cin, comando);

		//Separación de palabras del comando
		separarPalabras(comando);

    }
}

void CicloDeJuego::separarPalabras (string comando) {

}