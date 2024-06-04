#ifndef ESTADOJUEGO_HH
#define ESTADOJUEGO_HH

#include <IJugador.hh>
#include <Tablero.hh>
#include <memory>
#include <string>

using namespace std;

class EstadoJuego {
 public:
  // Constructor
  EstadoJuego(int filas, int columnas, int tipoJugador1, int tipoJugador2);

  // Según radio box_ 0 = humano, 1 = facil, 2 = dificil
  // Devuelve un puntero a la instancia del jugador generado.
  unique_ptr<IJugador> instanciarJugador(int tipoJugador, Color Ficha,
                                         string numeroJugador);

  // método que regresa el número del enum que ocupe la celda.
  int estadoCelda(int fila, int columna);

  bool insertarFicha(int columna);

  // usar verificarGanador de tablero para en caso de que haya ganador indicar
  // si fue el jugador uno o dos
  int verificarGanador();

  bool empate();

  void cambiarTurno();

  int getGanador();

  // atributo
  unique_ptr<IJugador> jugadorActual;
  unique_ptr<IJugador> jugadorUno;
  unique_ptr<IJugador> jugadorDos;
  int filas;
  int columnas;
  Tablero tablero;
};

#endif