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

TEST(EstadoTest, insertarFicha) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

TEST(EstadoTest, insertarFichaDespuesDeSwap) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);  
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.jugadorActual = juego.jugadorDos;
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}
