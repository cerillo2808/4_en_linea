#ifndef JUGADORHUMANO_HH
#define JUGADORHUMANO_HH
#include <IJugador.hh>
#include <iostream>

using namespace std;

class JugadorHumano : public IJugador {
 public:
  JugadorHumano(string nombre, Color ficha);
  void jugar() override;
  Color getFicha();
};

#endif