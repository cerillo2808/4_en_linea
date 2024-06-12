#include <gtest/gtest.h>
#include <Color.hh>
#include <JugadorFacil.hh>
#include <Tablero.hh>
#include <random>
#include <vector>

TEST(JugadorFacil, ConstructorJugador) {
  JugadorFacil ia("IA", amarillo);
  EXPECT_EQ(ia.getColor(), amarillo);
}

TEST(JugadorFacil, obtenerNombre) {
  JugadorFacil ia("IA", amarillo);
  EXPECT_EQ(ia.getNombre(), "IA");
}

TEST(JugadorFacil, obtenerGanes) {
  JugadorFacil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
}

TEST(JugadorFacil, modificarGane) {
  JugadorFacil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 1);
}

TEST(JugadorFacil, modificarGaneVariasVeces) {
  JugadorFacil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 4);
}

TEST(JugadorFacil, jugarEnTablero2x2) {
  Tablero tablero (2,2);
  JugadorFacil ia("IA", amarillo);
  int columna = ia.jugar(tablero);
  EXPECT_TRUE((columna >= 0) && (columna<= 1));
}

TEST(JugadorFacil, jugarEnTablero4x4) {
  Tablero tablero (4,4);
  JugadorFacil ia("IA", amarillo);
  int columna = ia.jugar(tablero);
  EXPECT_TRUE((columna >= 0) && (columna<= 3));
}

TEST(JugadorFacil, jugarEnTablero10x10) {
  Tablero tablero (10,10);
  JugadorFacil ia("IA", amarillo);
  int columna = ia.jugar(tablero);
  EXPECT_TRUE((columna >= 0) && (columna<= 9));
}

