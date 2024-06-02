#ifndef ESTADOJUEGO_HH
#define ESTADOJUEGO_HH

#include <IJugador.hh>

class EstadoJuego{
    public:
    //Constructor
    EstadoJuego(int filas, int columnas, int tipoJugador1, int tipoJugador2);


    //métodos:
    //De acuerdo a los indices que obtenemos de los radio box si
    //0=jugadorHumano, 1=Fácil , 2= dificil, por ello considero útil método para
    //que dependiendo del entero se instancie un tipo de jugador
    void instanciarJugadores(int tipoJugador1, int tipoJugador2);
    bool insertarFicha(int columna);
    //usar verificarGanador de tablero para en caso de que haya ganador indicar si fue el jugador uno o dos
    int verificarGanador();
    bool empate();

    void cambiarTurno();

    //método que regrese 1 si es una casilla donde está el jugador 1
    //2 si es el 2 y 0 si está vacía 
    int estadoCelda (int fila, int columna);


    //atributos 

    IJugador* jugadorActual;
    IJugador* jugadorUno;
    IJugador* jugadorDos;
    int filas;
    int columnas;
    



};

#endif