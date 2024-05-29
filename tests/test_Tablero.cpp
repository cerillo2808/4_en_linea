#include <gtest/gtest.h>

#include <Tablero.hh>

TEST(TableroTest, ConstructorTablero) {
  Tablero tablero(2, 2);
  EXPECT_EQ(tablero.getTablero().size(), 2);
  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 0);
}

TEST(TableroTest, AnalisisGaneVertical) {
  Tablero tablero(4, 4);
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[3][0], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 3, 0));
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[2][0], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 2, 0));
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 1, 0));
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[0][0], 2);
  EXPECT_TRUE(tablero.analizarJugada(rojo, 0, 0));
}

TEST(TableroTest, AnalisisGaneHorizontal) {
  Tablero tablero(4, 4);
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[3][0], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 3, 0));
  tablero.insertarFicha(rojo, 1);
  EXPECT_EQ(tablero.getTablero()[3][1], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 3, 1));
  tablero.insertarFicha(rojo, 2);
  EXPECT_EQ(tablero.getTablero()[3][2], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 3, 2));
  tablero.insertarFicha(rojo, 3);
  EXPECT_EQ(tablero.getTablero()[3][3], 2);
  EXPECT_TRUE(tablero.analizarJugada(rojo, 3, 3));
}

TEST(TableroTest, AnalisisGaneDiagonal) {
  Tablero tablero(4, 4);
  tablero.insertarFicha(rojo, 0);
  EXPECT_EQ(tablero.getTablero()[3][0], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 3, 0));
  tablero.insertarFicha(azul, 1);
  tablero.insertarFicha(rojo, 1);
  EXPECT_EQ(tablero.getTablero()[3][1], 1);
  EXPECT_EQ(tablero.getTablero()[2][1], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 2, 1));
  tablero.insertarFicha(azul, 2);
  tablero.insertarFicha(azul, 2);
  tablero.insertarFicha(rojo, 2);
  EXPECT_EQ(tablero.getTablero()[3][2], 1);
  EXPECT_EQ(tablero.getTablero()[2][2], 1);
  EXPECT_EQ(tablero.getTablero()[1][2], 2);
  EXPECT_FALSE(tablero.analizarJugada(rojo, 1, 2));
  tablero.insertarFicha(azul, 3);
  tablero.insertarFicha(azul, 3);
  tablero.insertarFicha(azul, 3);
  tablero.insertarFicha(rojo, 3);
  EXPECT_EQ(tablero.getTablero()[3][3], 1);
  EXPECT_EQ(tablero.getTablero()[2][3], 1);
  EXPECT_EQ(tablero.getTablero()[1][3], 1);
  EXPECT_EQ(tablero.getTablero()[0][3], 2);
  EXPECT_TRUE(tablero.analizarJugada(rojo, 0, 3));
}

TEST(TableroTest, InsertarFichaVacio) {
  Tablero tablero(2, 2);
  EXPECT_EQ(tablero.getTablero().size(), 2);

  tablero.insertarFicha(rojo, 1);
  EXPECT_EQ(tablero.getTablero().size(), 2);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);
}

TEST(TableroTest, InsertarFichaNoVacio) {
  Tablero tablero(2, 2);
  EXPECT_EQ(tablero.getTablero().size(), 2);

  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(azul, 1);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 1);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);
}

TEST(TableroTest, InsertarFichaLleno) {
  Tablero tablero(2, 2);
  EXPECT_EQ(tablero.getTablero().size(), 2);

  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(azul, 1);
  tablero.insertarFicha(rojo, 1);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 1);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);
}

TEST(TableroTest, copiaConConstructor) {
  Tablero tablero(2, 2);

  tablero.insertarFicha(rojo, 1);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);

  Tablero copia = tablero;
  // la copia se iguala al tablero

  EXPECT_EQ(copia.getTablero()[0][0], 0);
  EXPECT_EQ(copia.getTablero()[0][1], 0);
  EXPECT_EQ(copia.getTablero()[1][0], 0);
  EXPECT_EQ(copia.getTablero()[1][1], 2);
  // nótese que copia se ve igual al tablero original
}

TEST(TableroTest, copiaEditada) {
  Tablero tablero(2, 2);

  tablero.insertarFicha(rojo, 1);

  Tablero copia = tablero;

  copia.insertarFicha(rojo, 1);

  EXPECT_EQ(copia.getTablero()[0][0], 0);
  EXPECT_EQ(copia.getTablero()[0][1], 2);
  EXPECT_EQ(copia.getTablero()[1][0], 0);
  EXPECT_EQ(copia.getTablero()[1][1], 2);
  // nótese que la copia tiene la ficha del original mas la que se le insertó

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);
  // aunque se le haya insertado otra ficha a la copia, la original no cambió
}