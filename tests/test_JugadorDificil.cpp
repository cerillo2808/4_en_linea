#include <gtest/gtest.h>
#include <JugadorDificil.hh>
#include <Tablero.hh>
#include <algorithm>
#include <climits>

TEST (JugadorDificlInstancia,ConstructorJugador) {
    JugadorDificil ia ("IA",azul);
    EXPECT_EQ(ia.getColor(), azul);
}

TEST (ValorJugadaIA,mismoColorDeIA) {
    JugadorDificil ia ("IA",azul);
    EXPECT_EQ(ia.valorJugada(azul,azul),2);
}

TEST (ValorJugadaVacia,espacioVacio) {
    JugadorDificil ia ("IA",azul);
    EXPECT_EQ(ia.valorJugada(azul,non_color),1);
}

TEST (ValorJugadaOponente,colorOponente) {
    JugadorDificil ia ("IA",azul);
    EXPECT_EQ(ia.valorJugada(azul,rojo),INT_MIN);
}

TEST (PuntajeTableroVacio,Vacio) {
    Tablero tablero (4,4);
    JugadorDificil ia ("IA",azul);
    EXPECT_EQ(ia.puntajeCaso(tablero),0);
}

TEST (PuntajeJugadas,JugadaIA1) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    //esta jugada permitirá verificar el uso del recorrido y puntaje vertical superior e inferior, horizontal derecha
    // y diagonal superior e inferior ambas hacia la derecha
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);

    EXPECT_EQ(ia.puntajeCaso(tablero),46);
}

TEST (PuntajeJugadas,JugadaIA2) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    //esta jugada permitirá verificar el uso del recorrido y puntaje vertical superior e inferior, horizontal izquierda
    //y diagonal superior e inferior ambas hacia la izquierda
    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(azul,3);

    EXPECT_EQ(ia.puntajeCaso(tablero),46);
}

TEST (PuntajeJugadasVerticalesOponente,JugadaOponente) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);

    EXPECT_EQ(ia.puntajeCaso(tablero),-46);
}

TEST (RestaPuntaje1,dosFilasVerticales) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,0);

    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(azul,1);

    EXPECT_EQ(ia.puntajeCaso(tablero),0);
}

TEST (RestaPuntaje2,dosFilasHorizontales) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(rojo,1);
    tablero.insertarFicha(rojo,2);
    tablero.insertarFicha(rojo,3);

    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(azul,2);
    tablero.insertarFicha(azul,3);

    EXPECT_EQ(ia.puntajeCaso(tablero),0);
}

TEST (RestaPuntaje3,dosFichasDistribuidas) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);

    tablero.insertarFicha(rojo,2);

    tablero.insertarFicha(azul,0);

    EXPECT_EQ(ia.puntajeCaso(tablero),5);
}

TEST (Minimax1,IAIniciaLaPartida) {
    Tablero tablero (4,4);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);  
 
    EXPECT_EQ(ia.minimax(tablero,1,INT_MIN,INT_MAX,azul)[0],0);
}

TEST (Minimax2,IAEscogeMejorMovimiento) {
    Tablero tablero (4,4);

    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(rojo,1);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);  
 
    EXPECT_EQ(ia.minimax(tablero,2,INT_MIN,INT_MAX,azul)[0],3);
}

TEST (Minimax3,IAMovimientoGanador) {
    Tablero tablero (4,4);

    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha (rojo,1);
    tablero.insertarFicha (rojo,1);
    tablero.insertarFicha (rojo,1);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);  
 
    EXPECT_EQ(ia.minimax(tablero,2,INT_MIN,INT_MAX,azul)[0],0);
}

TEST (Minimax4,OponenteMovimientoGanador) {
    Tablero tablero (4,4);

    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha (rojo,1);
    tablero.insertarFicha (rojo,1);
    tablero.insertarFicha (rojo,1);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);  
 
    EXPECT_EQ(ia.minimax(tablero,2,INT_MIN,INT_MAX,azul)[0],1);
}

TEST (Minimax5,Empate) {
    Tablero tablero (4,4);

    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(rojo,2);
    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(azul,2);
    tablero.insertarFicha(rojo,3);
    tablero.insertarFicha(azul,0);
    tablero.insertarFicha(rojo,1);
    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(rojo,2);
    tablero.insertarFicha(azul,1);
    tablero.insertarFicha(rojo,0);
    tablero.insertarFicha(azul,3);
    tablero.insertarFicha(rojo,2);

    JugadorDificil ia ("IA",azul);
    ia.setColorOponente(rojo);  
 
    EXPECT_EQ(ia.minimax(tablero,2,INT_MIN,INT_MAX,azul)[0],0);
}
