#ifndef TABLERO_HH
#define TABLERO_HH
#include <Color.hh>
#include <string>
#include <vector>

using namespace std;

class Tablero {
 public:
  // Constructor
  Tablero(int filas, int columnas);

  vector<vector<Color>> getTablero();

  // constructor de copias
  Tablero(const Tablero& other);

  // método para verificar si alguno de los jugadores ya completo una línea de 4
  // fichas
  bool analizarJugada(Color ficha, int fila, int columna);

  // método que busca la ficha más extrema en diagonal superior-izquierda con
  // respecto a una ficha de interes
  void extremoArribaIzq(Color ficha, int fila, int columna, int coordenadas[]);

  // método que busca la ficha más extrema en diagonal inferior-izquierda con
  // respecto a una ficha de interes
  void extremoAbajoIzq(Color ficha, int fila, int columna, int coordenadas[]);

  // método que busca la ficha más extrema en dirección horizontal-izquierda con
  // respecto a una ficha de interes
  void extremoIzq(Color ficha, int fila, int columna, int coordenadas[]);

  // método que busca si hay 4 fichas verticalmente
  bool recorridoVertical(Color ficha, int contador, int fila, int columna);

  // método que busca si hay 4 fichas en dirección horizontal hacia la derecha
  bool recorridoHorizontalDer(Color ficha, int contador, int fila, int columna);

  // método que busca si hay 4 fichas en dirección diagonal inferior-derecha
  bool recorridoAbajoDer(Color ficha, int contador, int fila, int columna);

  // método que busca si hay 4 fichas en dirección diagonal superior-derecha
  bool recorridoArribaDer(Color ficha, int contador, int fila, int columna);

  // método que inserta la ficha, devuelve -1 si la columna ya estaba llena,
  // sino devuelve el número de fila donde se inserto la ficha
  int insertarFicha(Color Ficha, int columna);

  // método que devuelve la cantidad de filas
  int getFilas();

  // método que devuelve la cantidad de columnas
  int getColumnas();

  // método para verificar si hubo un empate en la partida
  bool empate();

  // método para que el tablero indique las columnas disponibles que posee
  vector<int> getColumnasDisponibles();

  // método para modificar una casilla
  void setCasilla(Color ficha, int fila, int columna);

 private:
  vector<vector<Color>> tablero;
  vector<int> columnasDisponibles;
};
#endif