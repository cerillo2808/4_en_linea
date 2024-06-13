#ifndef JUGADORDIFICIL_HH
#define JUGADORDIFICIL_HH
#include <Color.hh>
#include <IJugador.hh>
#include <Tablero.hh>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class JugadorDificil : public IJugador {
 public:
  JugadorDificil(string nombre, Color ficha);
  int jugar(Tablero tablero) override;

  vector<int> minimax(
      std::chrono::time_point<std::chrono::system_clock> tiempoInicio,
      std::chrono::nanoseconds timepoLimite, Tablero tablero, int profundidad, int alfa, int beta,
      Color jugador);

  void setColorOponente(Color ficha);

  int puntajeTablero(Tablero tablero);

  int valorJugada(Color fichaJugador, Color fichaTablero);

 private:
  Color oponente;
};

#endif
