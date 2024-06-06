#include <EstadoJuego.hh>
#include <IJugador.hh>
#include <JugadorDificil.hh>
#include <JugadorFacil.hh>
#include <JugadorHumano.hh>
#include <Tablero.hh>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

EstadoJuego::EstadoJuego(int filas, int columnas, int tipoJugador1,
                         int tipoJugador2)
    : filas(filas), columnas(columnas), tablero(filas, columnas) {
  Tablero tablero = Tablero(filas, columnas);

  jugadorUno = instanciarJugador(tipoJugador1, amarillo, "1");
  jugadorDos = instanciarJugador(tipoJugador2, rojo, "2");

  // Inciamos con el primer jugador, se va a ir cambiando
  jugadorActual = jugadorUno;

  // empiezan como -1, porque no se ha insertado nada aún
  ultimaColumnaInsertada = -1;
  ultimaFilaInsertada = -1;
}

std::shared_ptr<IJugador> EstadoJuego::instanciarJugador(int tipoJugador,
                                                         Color ficha,
                                                         string numeroJugador) {
  if (tipoJugador == 0) {
    return std::make_shared<JugadorHumano>(numeroJugador, ficha);
  } else if (tipoJugador == 1) {
    return std::make_shared<JugadorFacil>(numeroJugador, ficha);
  } else {
    return std::make_shared<JugadorDificil>(numeroJugador, ficha);
  }
}

int EstadoJuego::estadoCelda(int fila, int columna) {
  return tablero.getTablero()[fila][columna];
}

int EstadoJuego::insertarFicha(int columna) {
  if (jugadorActual == jugadorUno) {
    int FilaInsertada = tablero.insertarFicha(amarillo, columna);
    ultimaFilaInsertada = FilaInsertada;
    ultimaColumnaInsertada = columna;
    return columna;
  } else if (jugadorActual == jugadorDos) {
    int FilaInsertada = tablero.insertarFicha(rojo, columna);
    ultimaFilaInsertada = FilaInsertada;
    ultimaColumnaInsertada = columna;
    return columna;
  }

  return -1;
}

int EstadoJuego::verificarGanador() {
  if (tablero.analizarJugada(jugadorActual->getColor(), ultimaFilaInsertada,
                             ultimaColumnaInsertada)) {
    return jugadorActual->getColor();
  }

  return 0;
}

bool EstadoJuego::empate() { return tablero.empate(); }

void EstadoJuego::cambiarTurno() {
  if (jugadorActual == jugadorUno) {
    jugadorActual = jugadorDos;
  } else {
    jugadorActual = jugadorUno;
  }
}

void EstadoJuego::clearTablero() {
  for (int i = 0; i < tablero.getFilas(); i++) {
    for (int j = 0; j < tablero.getColumnas(); j++) {
      tablero.setCasilla(non_color, i, j);
    }
  }
}
