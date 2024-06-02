#include <EstadoJuego.hh>
#include <IJugador.hh>
#include <Tablero.hh>
#include <iostream>
#include <vector>

EstadoJuego::EstadoJuego(int filas, int columnas, int tipoJugador1, int tipoJugador2): filas(filas), columnas(columnas){
    Tablero tablero= Tablero(filas, columnas);
    instanciarJugadores(tipoJugador1,tipoJugador2);
    //Inciamos con el primer jugador, se va a ir cambiando
    jugadorActual=jugadorUno;

}


 void EstadoJuego::instanciarJugadores(int tipoJugador1, int tipoJugador2){

 }

 int EstadoJuego::estadoCelda (int fila, int columna){
    return 1;
 }

bool EstadoJuego::insertarFicha(int columna){
    //dependiendo del tipo del jugador tiene que usar un método de inserción de ficha distinto
    //De acuerdo a los indices que obtenemos de los radio box si
    //0=jugadorHumano, 1=Fácil , 2= dificil
    //Se le pasa el tipo como parametro a IJugador
    return false;
}

int EstadoJuego::verificarGanador(){

    return 1;
}


bool EstadoJuego::empate(){

    return false;
}

void EstadoJuego::cambiarTurno(){
    if(jugadorActual==jugadorUno){
        jugadorActual=jugadorDos;
    }else{
        jugadorActual=jugadorUno;
    }
}
