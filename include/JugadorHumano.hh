#ifndef JUGADORHUMANO_HH
#define JUGADORHUMANO_HH
#include <Color.hh>
#include <IJugador.hh>
#include <Tablero.hh>

using namespace std;

class JugadorHumano : public IJugador {
 public:
  JugadorHumano(string nombre, Color ficha);
  int jugar(Tablero tablero) override;
};

#endif