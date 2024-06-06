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
  shared_ptr<IJugador> jugadorActual =
      instanciarJugador(0, non_color, "placeholder");

  jugadorActual = jugadorUno;
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

Color EstadoJuego::asignarFicha() {
  Color ficha = non_color;

  if (jugadorActual == jugadorUno) {
    ficha = amarillo;
  } else if (jugadorActual == jugadorDos) {
    ficha = rojo;
  }

  return ficha;
  // TODO: Eliminar este método porque es inútil
}

int EstadoJuego::insertarFicha(int columna) {
  if (jugadorActual->getColor() == jugadorUno->getColor()) {
    return tablero.insertarFicha(amarillo, columna);
  } else if (jugadorActual->getColor() == jugadorDos->getColor()) {
    return tablero.insertarFicha(rojo, columna);
  }

  return false;
}

int EstadoJuego::verificarGanador() {
  Color ficha;

  if (jugadorActual->getColor() == jugadorUno->getColor()) {
    ficha = amarillo;
  } else if (jugadorActual->getColor() == jugadorDos->getColor()) {
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
  if (jugadorActual->getColor() == jugadorUno->getColor()) {
    jugadorActual = jugadorDos;
  } else {
    jugadorActual = jugadorUno;
  }
}
