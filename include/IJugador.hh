#ifndef IJUGADOR_HH
#define IJUGADOR_HH
#include <iostream>

using namespace std;

enum Color {
  amarillo = 1,
  // amarillo será jugador 1
  rojo = 2,
  // rojo será jugador 2
  non_color = 0
  // el non_color es 0 porque es el default

};

class IJugador {
 public:
  // Constructor
  IJugador(string nombre, Color ficha) : nombre(nombre), ficha(ficha) {}

  // método para obtener el color de ficha del jugador
  Color getColor () {return ficha;}

  // método abstracto:
  virtual void jugar() = 0;

 protected:
  string nombre;
  Color ficha;
};

#endif