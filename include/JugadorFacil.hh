#ifndef JUGADORFACIL_HH
#define JUGADORFACIL_HH
#include <IJugador.hh>
#include <iostream>

using namespace std;


class JugadorFacil: public IJugador{

    public:
        JugadorFacil (string nombre, Color ficha);
        void jugar() override;

};

#endif