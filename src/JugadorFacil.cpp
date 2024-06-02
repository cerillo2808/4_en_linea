#include <JugadorFacil.hh>
#include <IJugador.hh>
#include <iostream>

using namespace std;

JugadorFacil:: JugadorFacil (string nombre, Color ficha):
    IJugador (nombre,ficha)
{}


void JugadorFacil:: jugar(){
    cout<<"IA fácil"<<endl;
}