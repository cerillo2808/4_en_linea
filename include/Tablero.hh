#ifndef TABLERO_HH
#define TABLERO_HH
#include <iostream>
#include <IJugador.hh>
#include <vector>

using namespace std;

class Tablero {
    public:
    
    //Constructor
    Tablero (int filas, int columnas);
    
    std::vector<std::vector<Color>> getTablero ();

    bool analizarFichaJugadir (Color ficha);

    void insertarFicha (Color Ficha);

    private: 

    std::vector<std::vector<Color>> tablero;
};
#endif