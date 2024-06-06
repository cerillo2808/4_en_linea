#include <gtest/gtest.h>

#include <EstadoJuego.hh>
#include <Tablero.hh>

TEST(EstadoTest, estadoCeldaDefault) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 0);
}

TEST(EstadoTest, amarillo) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  Tablero tableroPrueba(2,2);
  tableroPrueba.insertarFicha(amarillo, 1);  
  juego.tablero = tableroPrueba;
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

TEST(EstadoTest, rojo) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  Tablero tableroPrueba(2,2);
  tableroPrueba.insertarFicha(rojo, 1);  
  juego.tablero = tableroPrueba;
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 2);
}

/*TEST(EstadoTest, insertarFicha) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

TEST(EstadoTest, insertarMásFichas) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 1);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

TEST(EstadoTest, insertarMásFichasLleno) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 1);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  bool exito = juego.insertarFicha(1);
  EXPECT_FALSE(exito);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 1);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}*/

TEST(EstadoTest, cambiarTurno) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);  
  EXPECT_EQ(juego.jugadorActual, juego.jugadorUno);
  juego.cambiarTurno();
  EXPECT_EQ(juego.jugadorActual, juego.jugadorDos);
}

TEST(EstadoTest, cambiarTurnoDosVeces) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);  
  EXPECT_EQ(juego.jugadorActual, juego.jugadorUno);
  juego.cambiarTurno();
  EXPECT_EQ(juego.jugadorActual, juego.jugadorDos);
  juego.cambiarTurno();
  EXPECT_EQ(juego.jugadorActual, juego.jugadorUno);
  juego.cambiarTurno();
  EXPECT_EQ(juego.jugadorActual, juego.jugadorDos);
}

TEST(EstadoTest, colorFicha) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  Color ficha = juego.asignarFicha();
  EXPECT_EQ(ficha,amarillo);
  juego.cambiarTurno();
  Color ficha2 = juego.asignarFicha();
  EXPECT_EQ(ficha2, rojo);
  // TODO: Esta prueba no pasa
}

/*TEST(EstadoTest, insertarFichasOtroTurno) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  EXPECT_EQ(juego.jugadorActual, juego.jugadorDos);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  // TODO: Esta prueba no pasa
}*/
