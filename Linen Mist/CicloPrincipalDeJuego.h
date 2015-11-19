#ifndef __CicloPrincipalDeJuego__
#define __CicloPrincipalDeJuego__

#include "string"
#include "vector"
#include "iostream"
#include "sstream"
#include <algorithm>

using namespace std;

class CicloDeJuego {
  public:
	void iniciar();
  private:
	vector<string> separarPalabras(const string &, vector<string> &);
};

#endif //__CicloPrincipalDeJuego__