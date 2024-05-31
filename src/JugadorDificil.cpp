#include <IJugador.hh>
#include <JugadorDificil.hh>
#include <Tablero.hh>
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

JugadorDificil::JugadorDificil(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}

Color JugadorDificil ::getFicha() { return ficha; }

void JugadorDificil ::setColorOponente(Color fichaOponente) {
  oponente = fichaOponente;
}

vector<int> JugadorDificil ::minimax(Tablero tablero, int profundidad, int alfa,
                                     int beta, Color jugador) {
  int column;
  vector<int> columnasDisponibles = tablero.getColumnasDisponibles();
  if (profundidad == 0) {
    // TODO: Implementar la función heurística
  }
  if (jugador == ficha) {
    int puntajeCaso = INT_MIN;
    for (int i = 0; i < columnasDisponibles.size(); i++) {
      Tablero copiaTablero = tablero;
      int columna = columnasDisponibles[i];
      int fila = copiaTablero.insertarFicha(ficha, columna);
      bool verificarGaneIA = copiaTablero.analizarJugada(ficha, fila, columna);
      if (verificarGaneIA) {
        return {columna, 10000000};
      } else {
        int nuevoPuntaje =
            minimax(copiaTablero, profundidad - 1, alfa, beta, oponente)[1];
        if (nuevoPuntaje > puntajeCaso) {
          puntajeCaso = nuevoPuntaje;
          column = columna;
        }
        alfa = max(alfa, puntajeCaso);
        if (alfa >= beta) {
          break;
        }
      }
    }
    return {column, puntajeCaso};

  } else {
    int puntajeCaso = INT_MAX;
    for (int i = 0; i < columnasDisponibles.size(); i++) {
      Tablero copiaTablero = tablero;
      int columna = columnasDisponibles[i];
      int fila = copiaTablero.insertarFicha(oponente, columna);
      bool verificarGaneJugador =
          copiaTablero.analizarJugada(oponente, fila, columna);
      if (verificarGaneJugador) {
        return {columna, -10000000};
      } else {
        int nuevoPuntaje =
            minimax(copiaTablero, profundidad - 1, alfa, beta, ficha)[1];
        if (nuevoPuntaje < puntajeCaso) {
          puntajeCaso = nuevoPuntaje;
          column = columna;
        }
        beta = min(beta, puntajeCaso);
        if (alfa >= beta) {
          break;
        }
      }
    }
    return {column, puntajeCaso};
  }
}

void JugadorDificil::jugar() {}