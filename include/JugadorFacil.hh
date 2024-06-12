#ifndef JUGADORFACIL_HH
#define JUGADORFACIL_HH
#include <Color.hh>
#include <IJugador.hh>
#include <random>
#include <vector>
#include <Tablero.hh>

using namespace std;

class JugadorFacil : public IJugador {
 public:
  JugadorFacil(string nombre, Color ficha);
  int jugar(Tablero tablero) override;
};

#endif