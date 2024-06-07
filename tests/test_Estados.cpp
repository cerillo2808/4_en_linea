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

TEST(EstadoTest, getGanador1) {
  EstadoJuego juego = EstadoJuego(4, 4, 0, 0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);

  EXPECT_EQ(juego.estadoCelda(0, 0), 1);
  EXPECT_EQ(juego.estadoCelda(1, 0), 1);
  EXPECT_EQ(juego.estadoCelda(2, 0), 1);
  EXPECT_EQ(juego.estadoCelda(3, 0), 1);

  int ganador = juego.verificarGanador();
  EXPECT_EQ(ganador, 1);
}

TEST(EstadoTest, getGanador2) {
  EstadoJuego juego = EstadoJuego(4, 4, 0, 0);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);

  EXPECT_EQ(juego.estadoCelda(0, 0), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 2);
  EXPECT_EQ(juego.estadoCelda(2, 0), 2);
  EXPECT_EQ(juego.estadoCelda(3, 0), 2);

  int ganador = juego.verificarGanador();
  EXPECT_EQ(ganador, 2);
}

TEST(EstadoTest, getFilaDefault) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  EXPECT_EQ(juego.ultimaColumnaInsertada, -1);
}

TEST(EstadoTest, getFila) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  EXPECT_EQ(juego.ultimaColumnaInsertada, -1);
  juego.insertarFicha(0);
  EXPECT_EQ(juego.ultimaColumnaInsertada, 0);
}

TEST(EstadoTest, getFilaMasTurnos) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  EXPECT_EQ(juego.ultimaColumnaInsertada, -1);
  juego.insertarFicha(0);
  EXPECT_EQ(juego.ultimaColumnaInsertada, 0);
  juego.insertarFicha(2);
  EXPECT_EQ(juego.ultimaColumnaInsertada, 2);
}

TEST(EstadoTest, getGanes) {
  EstadoJuego juego = EstadoJuego(4, 4, 0, 0);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);

  EXPECT_EQ(juego.estadoCelda(0, 0), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 2);
  EXPECT_EQ(juego.estadoCelda(2, 0), 2);
  EXPECT_EQ(juego.estadoCelda(3, 0), 2);

  int ganador = juego.verificarGanador();
  EXPECT_EQ(ganador, 2);
  int ganes1 = juego.getGanes("1");
  int ganes2 = juego.getGanes("2");

  EXPECT_EQ(ganes1, 0);
  EXPECT_EQ(ganes2, 1);
}

TEST(EstadoTest, getMásGanes) {
  EstadoJuego juego = EstadoJuego(4, 4, 0, 0);
  juego.cambiarTurno();
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);

  EXPECT_EQ(juego.estadoCelda(0, 0), 2);
  EXPECT_EQ(juego.estadoCelda(1, 0), 2);
  EXPECT_EQ(juego.estadoCelda(2, 0), 2);
  EXPECT_EQ(juego.estadoCelda(3, 0), 2);

  int ganador = juego.verificarGanador();
  EXPECT_EQ(ganador, 2);
  int ganes1 = juego.getGanes("1");
  int ganes2 = juego.getGanes("2");

  EXPECT_EQ(ganes1, 0);
  EXPECT_EQ(ganes2, 1);

  juego.clearTablero();

  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);
  juego.insertarFicha(0);

  int ganador_1 = juego.verificarGanador();
  EXPECT_EQ(ganador_1, 2);
  int ganes1_1 = juego.getGanes("1");
  int ganes2_1 = juego.getGanes("2");

  EXPECT_EQ(ganes1_1, 0);
  EXPECT_EQ(ganes2_1, 2);
}

TEST(EstadoTest, getJugador) {
  EstadoJuego juego = EstadoJuego(2, 2, 1, 0);
  int jugador1 = juego.getTipoJugador();
  EXPECT_EQ(jugador1, 1);
}

TEST(EstadoTest, getJugadorConTurno) {
  EstadoJuego juego = EstadoJuego(2, 2, 1, 0);
  int jugador1 = juego.getTipoJugador();
  EXPECT_EQ(jugador1, 1);
  juego.cambiarTurno();
  int jugador2 = juego.getTipoJugador();
  EXPECT_EQ(jugador2, 0);
}

TEST(EstadoTest, getJugadorHumano1) {
  EstadoJuego juego = EstadoJuego(2, 2, 0, 0);
  bool jugador1 = juego.esHumano();
  EXPECT_TRUE(jugador1);
}

TEST(EstadoTest, getJugadorNoHumano1) {
  EstadoJuego juego = EstadoJuego(2, 2, 1, 0);
  bool jugador1 = juego.esHumano();
  EXPECT_FALSE(jugador1);
}

TEST(EstadoTest, getJugadorHumano2) {
  EstadoJuego juego = EstadoJuego(2, 2, 1, 0);
  juego.cambiarTurno();
  bool jugador2 = juego.esHumano();
  EXPECT_TRUE(jugador2);
}

TEST(EstadoTest, getJugadorNoHumano2) {
  EstadoJuego juego = EstadoJuego(2, 2, 1, 2);
  juego.cambiarTurno();
  bool jugador2 = juego.esHumano();
  EXPECT_FALSE(jugador2);
}