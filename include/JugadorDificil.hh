#ifndef JUGADORDIFICIL_HH
#define JUGADORDIFICIL_HH
#include <IJugador.hh>
#include <iostream>

using namespace std;

class JugadorDificil: public IJugador{

    public:
        JugadorDificil (string nombre, Color ficha);
        void jugar() override;

};

#endif