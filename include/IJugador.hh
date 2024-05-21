#ifndef IJUGADOR_HH
#define IJUGADOR_HH
#include <iostream>

using namespace std;

enum Color{

};

class IJugador{
    public:
        //Constructor 
        IJugador (string nombre, Color ficha):
            nombre(nombre), ficha(ficha) 
            {}

        //método abstracto:
         virtual void jugar() = 0;


    protected:
        string nombre;
        Color ficha;

};

#endif