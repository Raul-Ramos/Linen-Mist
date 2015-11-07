#include "string"
#include "vector"

using namespace std;

class CicloDeJuego {
    int width, height; //TODO: BORRAR
  public:
	void iniciar();
  private:
	vector<string> separarPalabras(const string &, vector<string> &);
};