#include <gtest/gtest.h>

#include <EstadoJuego.hh>
#include <Tablero.hh>

TEST(EstadoTest, Constructor) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
}
