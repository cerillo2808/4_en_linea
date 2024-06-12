#include <Color.hh>
#include <IJugador.hh>
#include <Tablero.hh>
#include <iostream>
#include <vector>
using namespace std;

// el vector tablero está hecho de otro vector hecho de colores. Es una matriz
// de colores, de tamaño inicializado por los parámetros. Además, siempre se
// inicializan las celdad en non_color
Tablero ::Tablero(int filas, int columnas)
    : tablero(filas, vector<Color>(columnas, non_color)) {}

vector<vector<Color>> Tablero ::getTablero() { return tablero; }

// constructor de copias del tablero
Tablero::Tablero(const Tablero& other) { tablero = other.tablero; }

bool Tablero ::analizarJugada(Color ficha, int fila, int columna) {
  // En el siguiente vector se guardaran las coordenadas de la ficha extrema a
  // la ficha insertada por el jugador en la posici+on cero se hallará la fila y
  // en la uno, la columna
  int extremos[2] = {fila, columna};

  // este contador funionará para registrar la cantidad de fichas que se han
  // contabilizado en una cierta dirección de análisis
  int contador = 1;

  // Los métodos de recorrido funcionan considerando la dicha que está adelante
  // de la interés, en cualquierda de las direcciones posibles

  // primero se verifican los extremos del tablero y luego se verifica si la
  // ficha del usuario tiene otra ficha del mismo color debajo de ella
  if (((fila + 1) <= (tablero.size() - 1)) &&
      (tablero[fila + 1][columna] == ficha)) {
    // en caso de poseerla, se inicia un recorrido vertical hacia abajo de la
    // ficha para buscar 4 del mismo color
    if (recorridoVertical(ficha, contador, fila + 1, columna)) {
      return true;
    }
  }

  // se verifica si la ficha del usuario posee una ficha del mismo color a su
  // izquierda o derecha
  if ((((columna - 1) >= 0) && (tablero[fila][columna - 1] == ficha)) ||
      (((columna + 1) <= (tablero[fila].size() - 1)) &&
       (tablero[fila][columna + 1] == ficha))) {
    // en caso de poseerla, busca la ficha más extrema en la izquierda
    extremoIzq(ficha, fila, columna, extremos);

    // tomando la ficha más extrema a la izquierda, recorre hacia la derecha
    // para buscar si hay 4 fichas del mismo color
    if (recorridoHorizontalDer(ficha, contador, extremos[0], extremos[1] + 1)) {
      return true;
    }
  }

  // se verifica si la ficha del usuario posee una ficha del mismo color en
  // dirección diagonal superior-izquierda o diagonal inferior-derecha
  if ((((fila + 1) <= (tablero.size() - 1)) &&
       ((columna + 1) <= (tablero[fila].size() - 1)) &&
       (tablero[fila + 1][columna + 1] == ficha)) ||
      (((fila - 1) >= 0) && ((columna - 1) >= 0) &&
       (tablero[fila - 1][columna - 1] == ficha))) {
    // en caso de poseerla se busca la ficha extrema en la diagonal
    // superior-izquierda
    extremoArribaIzq(ficha, fila, columna, extremos);
    // tomando dicha ficha, se recorre la diagonal inferior-derecha para hallar
    // 4 fichas del mismo color
    if (recorridoAbajoDer(ficha, contador, extremos[0] + 1, extremos[1] + 1)) {
      return true;
    }
  }

  // se verifica si la ficha del usuario posee una ficha del mismo color en
  // dirección diagonal inferior-izquierda o diagonal superior-derecha
  if ((((fila - 1) >= 0) && ((columna + 1) <= (tablero[fila].size() - 1)) &&
       (tablero[fila - 1][columna + 1] == ficha)) ||
      (((fila + 1) <= (tablero.size() - 1)) && ((columna - 1) >= 0) &&
       (tablero[fila + 1][columna - 1] == ficha))) {
    // en caso de poseerla se busca la ficha extrema en la diagonal
    // inferior-izquierda
    extremoAbajoIzq(ficha, fila, columna, extremos);
    // tomando dicha ficha, se recorre la diagonal superior-derecha
    if (recorridoArribaDer(ficha, contador, extremos[0] - 1, extremos[1] + 1)) {
      return true;
    }
  }

  return false;
}

void Tablero ::extremoArribaIzq(Color ficha, int fila, int columna,
                                int coordenadas[]) {
  // se verifica que la ficha posea una ficha del mismo color en la diagonal
  // superior-izquierda
  if (((fila - 1) >= 0) && ((columna - 1) >= 0) &&
      (tablero[fila - 1][columna - 1] == ficha)) {
    // como tal ficha es más extrema, entonces sus coordenadas pasan a ser las
    // nuevas del vector de extremos
    coordenadas[0] = --fila;
    coordenadas[1] = --columna;

    // se vuelve a llamar el mismo método para continuar con la búsqueda
    extremoArribaIzq(ficha, coordenadas[0], coordenadas[1], coordenadas);
  }
}

void Tablero ::extremoAbajoIzq(Color ficha, int fila, int columna,
                               int coordenadas[]) {
  // se verifica que la ficha posea una ficha del mismo color en la diagonal
  // inferior-izquierda
  if (((fila + 1) <= (tablero.size() - 1)) && ((columna - 1) >= 0) &&
      (tablero[fila + 1][columna - 1] == ficha)) {
    coordenadas[0] = ++fila;
    coordenadas[1] = --columna;
    extremoAbajoIzq(ficha, coordenadas[0], coordenadas[1], coordenadas);
  }
}

void Tablero ::extremoIzq(Color ficha, int fila, int columna,
                          int coordenadas[]) {
  // se verifica que la ficha posea una ficha del mismo color a la izquierda
  if (((columna - 1) >= 0) && (tablero[fila][columna - 1] == ficha)) {
    coordenadas[1] = --columna;
    extremoIzq(ficha, coordenadas[0], coordenadas[1], coordenadas);
  }
}

bool Tablero ::recorridoVertical(Color ficha, int contador, int fila,
                                 int columna) {
  // como la ficha que se recibe es la siguiente a la de interés, se aumenta el
  // contador en un primer momento
  contador++;

  // si aún no se han hallado las cuatro fichas se vuelve a llamar el método
  if (contador < 4) {
    // se verifica que existe una ficha del mismo color bajo la ficha de interés
    if (((fila + 1) <= (tablero.size() - 1)) &&
        (tablero[fila + 1][columna] == ficha)) {
      return recorridoVertical(ficha, contador, fila + 1, columna);
    }
    // en caso de que se corte la secuencia de color o se toque el extremo de
    // fila del tablero, se retorna falso
    else {
      return false;
    }
  }

  return true;
}

bool Tablero ::recorridoHorizontalDer(Color ficha, int contador, int fila,
                                      int columna) {
  contador++;
  cout << contador << endl;
  if (contador < 4) {
    // se verifica que existe una ficha del mismo color a la derecha de la fila
    // de interes
    if (((columna + 1) <= (tablero[fila].size() - 1)) &&
        (tablero[fila][columna + 1] == ficha)) {
      return recorridoHorizontalDer(ficha, contador, fila, columna + 1);
    }

    else {
      return false;
    }
  }

  // en caso de hallar las 4 fichas, se retorna verdadero, lo cual implica que
  // hubo un ganador
  return true;
}

bool Tablero ::recorridoAbajoDer(Color ficha, int contador, int fila,
                                 int columna) {
  contador++;

  if (contador < 4) {
    // se verifica que existe una ficha del mismo color en al diagonal
    // inferior-derecha
    if (((fila + 1) <= (tablero.size() - 1)) &&
        ((columna + 1) <= (tablero[fila].size() - 1)) &&
        (tablero[fila + 1][columna + 1] == ficha)) {
      return recorridoAbajoDer(ficha, contador, fila + 1, columna + 1);
    }

    else {
      return false;
    }
  }

  return true;
}

bool Tablero ::recorridoArribaDer(Color ficha, int contador, int fila,
                                  int columna) {
  contador++;

  if (contador < 4) {
    // se verifica que existe una ficha del mismo color en la diagonal
    // superio-derecha
    if (((fila - 1) >= 0) && ((columna + 1) <= (tablero[fila].size() - 1)) &&
        (tablero[fila - 1][columna + 1] == ficha)) {
      return recorridoArribaDer(ficha, contador, fila - 1, columna + 1);
    }

    else {
      return false;
    }
  }

  return true;
}

int Tablero::getFilas() { return tablero.size(); }

int Tablero::getColumnas() {
  if (!tablero.empty()) {
    return tablero[0].size();
  }
  return 0;
}

int Tablero::insertarFicha(Color ficha, int columna) {
  if (tablero[0][columna] == non_color) {
    // verifica que la columna a la que se quiere insertar la ficha no esté
    // llena.

    for (int i = (getFilas() - 1); i >= 0; i--) {
      // recorre la columna de abajo para arriba

      if (tablero[i][columna] == non_color) {
        // la fila de la columna en la que se encuentre vacío es non_color
        tablero[i][columna] = ficha;
        // se procede a asignarle el color a ese campo vacío
        return i;
        // se para el for aquí para que no asigne más fichas.
      }
    }
  }
  return -1;
  // se retorna falso, para que la GUI sepa que no se logró insertar la ficha
  // en esa columna y deje que el usuario haga otro click.
}

bool Tablero::empate() {
  for (int i = 0; i < tablero.size(); i++) {
    if (tablero[0][i] == 0) {
      return false;
    }
  }
  return true;
}

vector<int> Tablero ::getColumnasDisponibles() {
  // el tablero va modificandose con cada movimiento, por lo que para obtener
  // valores actualizados lo ideal es re-obtenerlos, para ello se borran los
  // elementos y se vuelven a solicitar los disponibles
  if (!columnasDisponibles.empty()) {
    columnasDisponibles.clear();
  }

  for (int i = 0; i < tablero[0].size(); i++) {
    // se sabe que mientras la fila 0 de una columna esté vacía (sea non_color)
    // es porque al menos existe una columna disponible
    if (tablero[0][i] == non_color) {
      // por ello se inserta de inmediato el valor i
      columnasDisponibles.push_back(i);
    }
  }

  return columnasDisponibles;
}

void Tablero::setCasilla(Color ficha, int fila, int columna) {
  tablero[fila][columna] = ficha;
}
