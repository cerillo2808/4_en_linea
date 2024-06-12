#ifndef IJUGADOR_HH
#define IJUGADOR_HH
#include <Tablero.hh>
#include <Color.hh>
#include <string>

using namespace std;

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
  virtual int jugar(Tablero tablero) = 0;

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