#ifndef JUGADORFACIL_HH
#define JUGADORFACIL_HH
#include <Color.hh>
#include <IJugador.hh>
#include <Tablero.hh>
#include <random>
#include <vector>

using namespace std;

class JugadorFacil : public IJugador {
 public:
  JugadorFacil(string nombre, Color ficha);
  int jugar(Tablero tablero) override;
};

#endif