#include <IJugador.hh>
#include <JugadorHumano.hh>
#include <Tablero.hh>
#include <Color.hh>

using namespace std;

JugadorHumano::JugadorHumano(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}


int JugadorHumano ::jugar(Tablero tablero) { return 0; }