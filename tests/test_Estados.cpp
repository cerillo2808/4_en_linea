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
  Tablero tableroPrueba(2, 2);
  tableroPrueba.insertarFicha(amarillo, 1);
  juego.tablero = tableroPrueba;
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

TEST(EstadoTest, rojo) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  Tablero tableroPrueba(2, 2);
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
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 1);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
}

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

TEST(EstadoTest, insertarFichasOtroTurno) {
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
}

TEST(EstadoTest, empateSi) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 1);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 2);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 1);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  bool empate = juego.empate();
  EXPECT_TRUE(empate);
}

TEST(EstadoTest, empateNo) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 1);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  bool empate = juego.empate();
  EXPECT_FALSE(empate);
}

TEST(EstadoTest, clearTablero) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(1);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 1);
  EXPECT_EQ(juego.estadoCelda(1, 1), 1);
  juego.clearTablero();
  EXPECT_EQ(juego.estadoCelda(0, 0), 0);
  EXPECT_EQ(juego.estadoCelda(0, 1), 0);
  EXPECT_EQ(juego.estadoCelda(1, 0), 0);
  EXPECT_EQ(juego.estadoCelda(1, 1), 0);
}