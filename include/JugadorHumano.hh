#ifndef JUGADORHUMANO_HH
#define JUGADORHUMANO_HH
#include <IJugador.hh>
#include <Tablero.hh>
#include <Color.hh>

using namespace std;

class JugadorHumano : public IJugador {
 public:
  JugadorHumano(string nombre, Color ficha);
  int jugar(Tablero tablero) override;
};

#endif