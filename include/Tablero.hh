#ifndef TABLERO_HH
#define TABLERO_HH
#include <IJugador.hh>
#include <iostream>
#include <vector>

using namespace std;

class Tablero {
 public:
  // Constructor
  Tablero(int filas, int columnas);

  std::vector<std::vector<Color>> getTablero();

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

  void insertarFicha(Color Ficha);

 private:
  std::vector<std::vector<Color>> tablero;
};
#endif