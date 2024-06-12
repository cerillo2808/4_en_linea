#include <Color.hh>
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

#include <stdexcept>

using namespace std;

EstadoJuego::EstadoJuego(int filas, int columnas, int tipoJugador1,
                         int tipoJugador2)
    : filas(filas),
      columnas(columnas),
      tablero(filas, columnas),
      tipoJugador1(tipoJugador1),
      tipoJugador2(tipoJugador2) {
    
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
  
  if (fila < 0 || fila >= tablero.getFilas()) {
    throw std::out_of_range("Fila fuera de rango: Fila pedida: " + std::to_string(fila) + ", Total de filas según programa: " + std::to_string(tablero.getFilas()));
}

if (columna < 0 || columna >= tablero.getColumnas()) {
    throw std::out_of_range("Columna fuera de rango: Columna pedida: " + std::to_string(columna) + ", Total de columnas según programa: " + std::to_string(tablero.getColumnas()));
}

  return tablero.getTablero()[fila][columna];
}

int EstadoJuego::insertarFicha(int columna) {
  if (jugadorActual == jugadorUno) {
    int FilaInsertada = tablero.insertarFicha(amarillo, columna);
    ultimaFilaInsertada = FilaInsertada;
    ultimaColumnaInsertada = columna;
    return FilaInsertada;
  } else if (jugadorActual == jugadorDos) {
    int FilaInsertada = tablero.insertarFicha(rojo, columna);
    ultimaFilaInsertada = FilaInsertada;
    ultimaColumnaInsertada = columna;
    return FilaInsertada;
  }

  return -1;
}

int EstadoJuego::verificarGanador() {
  if (tablero.analizarJugada(jugadorActual->getColor(), ultimaFilaInsertada,
                             ultimaColumnaInsertada)) {
    jugadorActual->setGanes();
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

int EstadoJuego::getTipoJugador() {
  if (jugadorActual == jugadorUno) {
    return tipoJugador1;
  } else if (jugadorActual == jugadorDos) {
    return tipoJugador2;
  }

  return -1;
}

int EstadoJuego::getGanes(string nombre) {
  if (nombre == "1") {
    return jugadorUno->getGanes();
  } else if (nombre == "2") {
    return jugadorDos->getGanes();
  }

  return -1;
}

bool EstadoJuego::esHumano() {
  if (jugadorActual == jugadorUno) {
    if (tipoJugador1 == 0) {
      return true;
    }
  } else if (jugadorActual == jugadorDos) {
    if (tipoJugador2 == 0) {
      return true;
    }
  }

  return false;
}