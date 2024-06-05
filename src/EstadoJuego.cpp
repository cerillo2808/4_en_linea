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

  shared_ptr<IJugador> jugadorUno =
      instanciarJugador(tipoJugador1, amarillo, "1");
  shared_ptr<IJugador> jugadorDos = instanciarJugador(tipoJugador2, rojo, "2");

  // Inciamos con el primer jugador, se va a ir cambiando
  jugadorActual = move(jugadorUno);
}

std::shared_ptr<IJugador> EstadoJuego::instanciarJugador(int tipoJugador,
                                                         Color ficha,
                                                         string numeroJugador) {
  if (tipoJugador == 0) {
    string nombre = numeroJugador;
    shared_ptr<IJugador> jugador =
        shared_ptr<IJugador>(new JugadorHumano(nombre, ficha));
    return jugador;

  } else if (tipoJugador == 1) {
    string nombre = numeroJugador;
    shared_ptr<IJugador> jugador =
        shared_ptr<IJugador>(new JugadorFacil(nombre, ficha));
    return jugador;

  } else {
    string nombre = numeroJugador;
    shared_ptr<IJugador> jugador =
        shared_ptr<IJugador>(new JugadorDificil(nombre, ficha));
    return jugador;
  }
}

int EstadoJuego::estadoCelda(int fila, int columna) {
  return tablero.getTablero()[fila][columna];
}

bool EstadoJuego::insertarFicha(int columna) {
  Color ficha;

  if (jugadorActual == jugadorUno) {
    ficha = amarillo;
  } else if (jugadorActual == jugadorDos) {
    ficha = rojo;
  }

  return tablero.insertarFicha(ficha, columna);
}

int EstadoJuego::verificarGanador() {
  Color ficha;

  if (jugadorActual == jugadorUno) {
    ficha = amarillo;
  } else if (jugadorActual == jugadorDos) {
    ficha = rojo;
  }

  if (tablero.analizarJugada(ficha, 1, 1)) {
    // TODO: Conseguir las coordenadas en donde se insertó la ficha.
    if (ficha == amarillo) {
      return 1;
    } else if (ficha == rojo) {
      return 2;
    }
  }

  return 0;
}

bool EstadoJuego::empate() { return tablero.empate(); }

void EstadoJuego::cambiarTurno() {
  if (jugadorActual == jugadorUno) {
    shared_ptr<IJugador> temporal = move(jugadorActual);
    jugadorActual = move(jugadorDos);
    jugadorUno = move(temporal);
  } else {
    shared_ptr<IJugador> temporal = move(jugadorActual);
    jugadorActual = move(jugadorUno);
    jugadorUno = move(temporal);
  }
}
