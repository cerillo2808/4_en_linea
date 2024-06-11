#ifndef JUGADORDIFICIL_HH
#define JUGADORDIFICIL_HH
#include <IJugador.hh>
#include <Tablero.hh>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

class JugadorDificil : public IJugador {
 public:
  JugadorDificil(string nombre, Color ficha);
  void jugar() override;

  vector<int> minimax(std::chrono::time_point<std::chrono::system_clock> tiempoInicio, double timepoLimite, Tablero tablero, int profundidad, int alfa, int beta,
                      Color jugador);


  void setColorOponente(Color ficha);

  int puntajeTablero(Tablero tablero);

  int valorJugada(Color fichaJugador, Color fichaTablero);

 private:
  Color oponente;
};

#endif