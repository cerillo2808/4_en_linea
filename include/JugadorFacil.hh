#ifndef JUGADORFACIL_HH
#define JUGADORFACIL_HH
#include <IJugador.hh>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class JugadorFacil : public IJugador {
 public:
  JugadorFacil(string nombre, Color ficha);
  int jugar(Tablero tablero) override;
};

#endif