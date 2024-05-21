#include <Tablero.hh>
#include <IJugador.hh>

Tablero :: Tablero (int filas, int columnas) {
    tablero = new Color* [filas];

    for (int i; i < filas; i++) {
        tablero [i] = new Color [columnas];
    } 
}

Color ** Tablero :: getTablero () {
    return tablero;
}

// metodos de analizarFicha e insertarFicha están en proceso de desarrollo  
