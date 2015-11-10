#ifndef __CicloPrincipalDeJuego__
#define __CicloPrincipalDeJuego__

#include "string"
#include "vector"

using namespace std;

class CicloDeJuego {
  public:
	void iniciar();
  private:
	vector<string> separarPalabras(const string &, vector<string> &);
};

#endif //__CicloPrincipalDeJuego__