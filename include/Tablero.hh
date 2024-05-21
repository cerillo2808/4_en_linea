#ifndef TABLERO_HH
#define TABLERO_HH
#include <iostream>
# include <IJugador.hh>

using namespace std;

class Tablero {
    public:
    
    //Constructor
    Tablero (int filas, int columnas) {}
    
    Color ** getTablero () {}

    bool analizarFichaJugadir (Color ficha) {}

    void insertarFicha (Color Ficha) {} 

    private: 

    Color ** tablero;
};
#endif