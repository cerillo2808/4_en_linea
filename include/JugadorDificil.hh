#ifndef JUGADORDIFICIL_HH
#define JUGADORDIFICIL_HH
#include <IJugador.hh>
#include <Tablero.hh>
#include <iostream>
#include <vector>

using namespace std;

class JugadorDificil : public IJugador {
 public:
  JugadorDificil(string nombre, Color ficha);
  void jugar() override;

  vector<int> minimax(Tablero tablero, int profundidad, int alfa, int beta,
                      Color jugador);

  Color getFicha();

  void setColorOponente(Color ficha);

 private:
  Color oponente;
};

#endif