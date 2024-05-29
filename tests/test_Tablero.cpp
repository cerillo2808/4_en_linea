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

TEST(TableroTest, copiaTablero) {
  Tablero tablero(2, 2);

  std::vector<std::vector<Color>> tableroCopia = tablero.getTablero();

  EXPECT_EQ(tableroCopia[0][0], 0);
  EXPECT_EQ(tableroCopia[0][1], 0);
  EXPECT_EQ(tableroCopia[1][0], 0);
  EXPECT_EQ(tableroCopia[1][1], 0);
}

TEST(TableroTest, manipularCopiaTablero) {
  Tablero tablero(2, 2);

  tablero.insertarFicha(rojo, 1);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);

  std::vector<std::vector<Color>> tableroCopia = tablero.getTablero();

  EXPECT_EQ(tableroCopia[0][0], 0);
  EXPECT_EQ(tableroCopia[0][1], 0);
  EXPECT_EQ(tableroCopia[1][0], 0);
  EXPECT_EQ(tableroCopia[1][1], 2);
}

TEST(TableroTest, objetoTableroIgualadoATablero) {
  Tablero tablero(2, 2);

  int filas = tablero.getFilas();
  int columnas = tablero.getColumnas();

  Tablero copia(filas, columnas);

  copia.getTablero() = tablero.getTablero();

  copia.insertarFicha(rojo, 1);

  EXPECT_EQ(copia.getTablero()[0][0], 0);
  EXPECT_EQ(copia.getTablero()[0][1], 0);
  EXPECT_EQ(copia.getTablero()[1][0], 0);
  EXPECT_EQ(copia.getTablero()[1][1], 2);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 0);
}

TEST(TableroTest, objetoTableroIgualadoATableroConFichas) {
  Tablero tablero(2, 2);

  int filas = tablero.getFilas();
  int columnas = tablero.getColumnas();

  Tablero copia(filas, columnas);

  tablero.insertarFicha(rojo, 1);

  EXPECT_EQ(tablero.getTablero()[0][0], 0);
  EXPECT_EQ(tablero.getTablero()[0][1], 0);
  EXPECT_EQ(tablero.getTablero()[1][0], 0);
  EXPECT_EQ(tablero.getTablero()[1][1], 2);

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      copia.getTablero()[i][j] = tablero.getTablero()[i][j];
    }
  }

  EXPECT_EQ(copia.getTablero()[0][0], 0);
  EXPECT_EQ(copia.getTablero()[0][1], 0);
  EXPECT_EQ(copia.getTablero()[1][0], 0);
  EXPECT_EQ(copia.getTablero()[1][1], 0);
}
