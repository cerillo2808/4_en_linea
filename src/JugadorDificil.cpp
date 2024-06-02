#include <JugadorDificil.hh>
#include <IJugador.hh>
#include <iostream>

using namespace std;

JugadorDificil:: JugadorDificil (string nombre, Color ficha):
    IJugador (nombre,ficha)
{}


void JugadorDificil:: jugar(){
    cout<<"IA dificil"<<endl;
}