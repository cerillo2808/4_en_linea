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
  shared_ptr<IJugador> instanciarJugador(int tipoJugador, Color Ficha,
                                         string numeroJugador);

  // método que regresa el número del enum que ocupe la celda.
  int estadoCelda(int fila, int columna);

  // método que inserta la ficha en el tablero y devuelve la columna en la que
  // se logró insertar.
  int insertarFicha(int columna);

  // usar verificarGanador de tablero para en caso de que haya ganador indicar
  // si fue el jugador uno o dos
  // TODO: Faltan coordenadas para Tablero::AnalizarJugada
  int verificarGanador();

  // devuelve verdadero si el tablero está lleno, devuelve falso si aún hay
  // campo en el tablero.
  bool empate();

  // hace que jugadorActual cambie al otro jugador
  void cambiarTurno();

  // hace que los colores del tablero sea non_color
  void clearTablero();

  // devuelve 0 si jugadorActual es humano, 1 si jugadorActual es facil, 2 si
  // jugadorActual es dificil.
  // TODO: implementarlo.
  int getTipoJugador();

  // atributos
  shared_ptr<IJugador> jugadorActual;
  shared_ptr<IJugador> jugadorUno;
  shared_ptr<IJugador> jugadorDos;
  int filas;
  int columnas;
  Tablero tablero;
  int ultimaColumnaInsertada;
  int ultimaFilaInsertada;
};

#endif