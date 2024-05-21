#include <JugadorFacil.hh>
#include <IJugador.hh>
#include <iostream>
#include <random>

using namespace std;

JugadorFacil:: JugadorFacil (string nombre, Color ficha):
    IJugador (nombre,ficha)
{}


void JugadorFacil:: jugar  (){

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(1, 5);
    //TODO: conectar la cantidad de columnas al random;
    int numeroRandom = dist(engine);

    cout<<"IA fácil"<<endl;
}