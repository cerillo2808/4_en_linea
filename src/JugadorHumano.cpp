#include <IJugador.hh>
#include <JugadorHumano.hh>
#include <iostream>

using namespace std;

JugadorHumano::JugadorHumano(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}


void JugadorHumano::jugar() { cout << "humano" << endl; }