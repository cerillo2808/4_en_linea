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
    if (tablero.empate()) {
      return {-1, 0};
    } else {
      return {-1, puntajeCaso(tablero)};
    }
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

int JugadorDificil ::puntajeCaso(Tablero tablero) {
  int contadorJugadasGaneIA = 0;
  int contadorJugadasGaneOponente = 0;
  Color fichaInteres;
  Color fichaOponente;

  vector<vector<Color> > copiaTablero = tablero.getTablero();

  for (int i = (copiaTablero.size() - 1); i >= 0; i--) {
    for (int j = 0; i < copiaTablero[0].size(); i++) {
      if (copiaTablero[i][j] == non_color) {
        continue;
      }

      else if (copiaTablero[i][j] == ficha) {
        fichaInteres = ficha;
        fichaOponente = oponente;
      } else {
        fichaInteres = oponente;
        fichaOponente = ficha;
      }
      // jugadas superiores verticales
      if (((i - 3) >= 0) && (copiaTablero[i - 1][j] != fichaOponente)) {
        int puntaje = 2 + valorJugada(fichaInteres, copiaTablero[i - 1][j]) +
                      valorJugada(fichaInteres, copiaTablero[i - 2][j]) +
                      valorJugada(fichaInteres, copiaTablero[i - 3][j]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas inferiores verticales
      if (((i + 3) <= (copiaTablero.size() - 1)) &&
          (copiaTablero[i + 1][j] != fichaOponente)) {
        int puntaje = 2 + valorJugada(fichaInteres, copiaTablero[i + 1][j]) +
                      valorJugada(fichaInteres, copiaTablero[i + 2][j]) +
                      valorJugada(fichaInteres, copiaTablero[i + 3][j]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas horizontales izquierda
      if (((j - 3) >= 0) && (copiaTablero[i][j - 1] != fichaOponente)) {
        int puntaje = 2 + valorJugada(fichaInteres, copiaTablero[i][j - 1]) +
                      valorJugada(fichaInteres, copiaTablero[i][j - 2]) +
                      valorJugada(fichaInteres, copiaTablero[i][j - 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas horizontales derecha
      if (((j + 3) >= 0) && (copiaTablero[i][j + 1] != fichaOponente)) {
        int puntaje = 2 + valorJugada(fichaInteres, copiaTablero[i][j + 1]) +
                      valorJugada(fichaInteres, copiaTablero[i][j + 2]) +
                      valorJugada(fichaInteres, copiaTablero[i][j + 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas diagonales superiores derecha
      if (((i - 3) >= 0) && ((j + 3) <= (copiaTablero[0].size() - 1)) &&
          (copiaTablero[i - 1][j + 1] != fichaOponente)) {
        int puntaje = 2 +
                      valorJugada(fichaInteres, copiaTablero[i - 1][j + 1]) +
                      valorJugada(fichaInteres, copiaTablero[i - 2][j + 2]) +
                      valorJugada(fichaInteres, copiaTablero[i - 3][j + 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas diagonales superiores izquierda
      if (((i - 3) >= 0) && ((j - 3) >= 0) &&
          (copiaTablero[i - 1][j - 1] != fichaOponente)) {
        int puntaje = 2 +
                      valorJugada(fichaInteres, copiaTablero[i - 1][j - 1]) +
                      valorJugada(fichaInteres, copiaTablero[i - 2][j - 2]) +
                      valorJugada(fichaInteres, copiaTablero[i - 3][j - 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas diagonales inferiores derecha
      if (((i + 3) <= (copiaTablero.size() - 1)) &&
          ((j + 3) <= (copiaTablero[0].size() - 1)) &&
          (copiaTablero[i + 1][j + 1] != fichaOponente)) {
        int puntaje = 2 +
                      valorJugada(fichaInteres, copiaTablero[i + 1][j + 1]) +
                      valorJugada(fichaInteres, copiaTablero[i + 2][j + 2]) +
                      valorJugada(fichaInteres, copiaTablero[i + 3][j + 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
      // jugadas diagonales inferiores izquierda
      if (((i + 3) <= (copiaTablero.size() - 1)) && ((j - 3) >= 0) &&
          (copiaTablero[i + 1][j - 1] != fichaOponente)) {
        int puntaje = 2 +
                      valorJugada(fichaInteres, copiaTablero[i + 1][j - 1]) +
                      valorJugada(fichaInteres, copiaTablero[i + 2][j - 2]) +
                      valorJugada(fichaInteres, copiaTablero[i + 3][j - 3]);
        if (puntaje > 0 && fichaInteres == ficha) {
          contadorJugadasGaneIA += puntaje;
        } else if (puntaje > 0 && fichaInteres == oponente) {
          contadorJugadasGaneOponente += puntaje;
        }
      }
    }
  }

  return contadorJugadasGaneIA - contadorJugadasGaneOponente;
}

int JugadorDificil ::valorJugada(Color fichaJugador, Color fichaTablero) {
  if (fichaJugador == fichaTablero) {
    return 2;
  } else if (fichaTablero == non_color) {
    return 1;
  }
  return INT_MIN;
}

void JugadorDificil::jugar() {}