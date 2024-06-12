#include <IJugador.hh>
#include <JugadorFacil.hh>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

JugadorFacil::JugadorFacil(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}


int JugadorFacil::jugar(Tablero tablero) { 
    //se declara el inicializador de numeros aleatorios
    mt19937 rng (random_device{}());
    //se crea una distribución uniforme en el rango que va desde la posicion cero al número de columnas disponibles
    uniform_int_distribution<int> distribution (0,tablero.getColumnasDisponibles().size() - 1);
    //se retorna la columna disponible según la posición aleatoria obtenida mediante la distribución
    return tablero.getColumnasDisponibles()[distribution(rng)];
    }