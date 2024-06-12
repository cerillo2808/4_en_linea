#ifndef IJUGADOR_HH
#define IJUGADOR_HH
#include <iostream>
#include <Tablero.hh>
#include <Color.hh>

using namespace std;

/*enum Color {
  amarillo = 1,
  // amarillo será jugador 1
  rojo = 2,
  // rojo será jugador 2
  non_color = 0
  // el non_color es 0 porque es el default

};*/

class IJugador {
 public:
  // Constructor
  IJugador(string nombre, Color ficha)
      : nombre(nombre), ficha(ficha), ganes(0) {}

  //destructor virtual de la clase IJugador
  virtual ~IJugador() {}

  // método para obtener el color de ficha del jugador
  Color getColor() { return ficha; }

  // método abstracto:
  virtual int jugar(Tablero tablero);

  // método para setear los ganes
  void setGanes() { ganes++; }

  // método para obtener los ganes
  int getGanes() { return ganes; }

  // método para obtener el nombre
  string getNombre() { return nombre; }

 protected:
  string nombre;
  Color ficha;
  int ganes;
};

#endif