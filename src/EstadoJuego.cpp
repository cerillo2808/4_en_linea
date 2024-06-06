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

  unique_ptr<IJugador> jugadorUno =
      instanciarJugador(tipoJugador1, amarillo, "1");
  unique_ptr<IJugador> jugadorDos = instanciarJugador(tipoJugador2, rojo, "2");

  // Inciamos con el primer jugador, se va a ir cambiando
  unique_ptr<IJugador> jugadorActual =
      instanciarJugador(0, non_color, "placeholder");
  jugadorActual.swap(jugadorUno);
}

std::unique_ptr<IJugador> EstadoJuego::instanciarJugador(int tipoJugador,
                                                         Color ficha,
                                                         string numeroJugador) {
  if (tipoJugador == 0) {
    string nombre = numeroJugador;
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorHumano(nombre, ficha));
    return jugador;

  } else if (tipoJugador == 1) {
    string nombre = numeroJugador;
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorFacil(nombre, ficha));
    return jugador;

  } else {
    string nombre = numeroJugador;
    unique_ptr<IJugador> jugador =
        unique_ptr<IJugador>(new JugadorDificil(nombre, ficha));
    return jugador;
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

bool EstadoJuego::insertarFicha(int columna) {
  if (jugadorActual == jugadorUno) {
    return tablero.insertarFicha(amarillo, columna);
  } else if (jugadorActual == jugadorDos) {
    return tablero.insertarFicha(rojo, columna);
  }

  return false;

  // TODO: asegurar que el == logre llegar al else-if
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
  unique_ptr<IJugador> temporal =
      unique_ptr<IJugador>(new JugadorHumano("temporal", non_color));

  if (jugadorActual == jugadorUno) {
    temporal.swap(jugadorActual);
    jugadorActual.swap(jugadorDos);
    jugadorUno.swap(temporal);
    jugadorDos.swap(temporal);
  } else {
    temporal.swap(jugadorActual);
    jugadorActual.swap(jugadorUno);
    jugadorDos.swap(temporal);
    jugadorUno.swap(temporal);
  }
}
