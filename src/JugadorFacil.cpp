#include <IJugador.hh>
#include <JugadorFacil.hh>
#include <iostream>

using namespace std;

JugadorFacil::JugadorFacil(string nombre, Color ficha)
    : IJugador(nombre, ficha) {}

Color JugadorFacil ::getFicha() { return ficha; }

void JugadorFacil::jugar() { cout << "IA fácil" << endl; }