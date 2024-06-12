#include <Color.hh>
#include <IJugador.hh>
#include <JugadorHumano.hh>
#include <Tablero.hh>

using namespace std;

JugadorHumano::JugadorHumano(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}

int JugadorHumano ::jugar(Tablero tablero) { return 0; }