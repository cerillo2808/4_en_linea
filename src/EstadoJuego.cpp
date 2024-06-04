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

  unique_ptr<IJugador> jugadorUno = instanciarJugador(tipoJugador1, amarillo);
  unique_ptr<IJugador> jugadorDos = instanciarJugador(tipoJugador2, rojo);

  // Inciamos con el primer jugador, se va a ir cambiando
  jugadorActual = move(jugadorUno);
}

std::unique_ptr<IJugador> EstadoJuego::instanciarJugador(int tipoJugador1,
                                                         Color ficha) {
  if (tipoJugador1 == 0) {
    string nombre = "humano";
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorHumano(nombre, ficha));
    return jugador;

  } else if (tipoJugador1 == 1) {
    string nombre = "facil";
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorFacil(nombre, ficha));
    return jugador;

  } else {
    string nombre = "dificil";
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorDificil(nombre, ficha));
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
    unique_ptr<IJugador> temporal = move(jugadorActual);
    jugadorActual = move(jugadorDos);
    jugadorUno = move(temporal);
  } else {
    unique_ptr<IJugador> temporal = move(jugadorActual);
    jugadorActual = move(jugadorUno);
    jugadorUno = move(temporal);
  }
}
