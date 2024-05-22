#include <Tablero.hh>
#include <IJugador.hh>
#include <vector>

Tablero :: Tablero (int filas, int columnas) {
    
    std::vector<std::vector<Color>> tablero (filas, std::vector<Color>(columnas));
    //el vector tablero está hecho de otro vector hecho de colores. Es una matriz de colores, de tamaño inicializado por los parámetros.
    
}

std::vector<std::vector<Color>> Tablero :: getTablero () {
    return tablero;
}

// metodos de analizarFicha e insertarFicha están en proceso de desarrollo  
