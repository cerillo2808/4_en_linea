#include <gtest/gtest.h>

#include <JugadorDificil.hh>
#include <Tablero.hh>
#include <algorithm>
#include <climits>

TEST(JugadorDificlInstancia, ConstructorJugador) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getColor(), amarillo);
}

TEST(funcionesGeneralesIJugador1, obtenerNombre) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getNombre(), "IA");
}

TEST(funcionesGeneralesIJugador2, obtenerGanes) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
}

TEST(funcionesGeneralesIJugador3, modificarGane) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 1);
}

TEST(funcionesGeneralesIJugador4, modificarGaneVariasVeces) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 4);
}

TEST(ValorJugadaIA, mismoColorDeIA) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, amarillo), 2);
}

TEST(ValorJugadaVacia, espacioVacio) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, non_color), 1);
}

TEST(ValorJugadaOponente, colorOponente) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, rojo), INT_MIN);
}

TEST(PuntajeTableroVacio, Vacio) {
  Tablero tablero(4, 4);
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.puntajeCaso(tablero), 0);
}

TEST(PuntajeJugadas, JugadaIA1) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  // esta jugada permitirá verificar el uso del recorrido y puntaje vertical
  // superior e inferior, horizontal derecha
  //  y diagonal superior e inferior ambas hacia la derecha
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);

  EXPECT_EQ(ia.puntajeCaso(tablero), 46);
}

TEST(PuntajeJugadas, JugadaIA2) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  // esta jugada permitirá verificar el uso del recorrido y puntaje vertical
  // superior e inferior, horizontal izquierda y diagonal superior e inferior
  // ambas hacia la izquierda
  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(amarillo, 3);

  EXPECT_EQ(ia.puntajeCaso(tablero), 46);
}

TEST(PuntajeJugadasVerticalesOponente, JugadaOponente) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);

  EXPECT_EQ(ia.puntajeCaso(tablero), -46);
}

TEST(RestaPuntaje1, dosFilasVerticales) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);

  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(amarillo, 1);

  EXPECT_EQ(ia.puntajeCaso(tablero), 0);
}

TEST(RestaPuntaje2, dosFilasHorizontales) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 2);
  tablero.insertarFicha(rojo, 3);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(amarillo, 2);
  tablero.insertarFicha(amarillo, 3);

  EXPECT_EQ(ia.puntajeCaso(tablero), 0);
}

TEST(RestaPuntaje3, dosFichasDistribuidas) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 2);

  tablero.insertarFicha(amarillo, 0);

  EXPECT_EQ(ia.puntajeCaso(tablero), 5);
}

TEST(Minimax1, IAIniciaLaPartida) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.minimax(tablero, 1, INT_MIN, INT_MAX, amarillo)[0], 0);
}

TEST(Minimax2, IAEscogeMejorMovimiento) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.minimax(tablero, 2, INT_MIN, INT_MAX, amarillo)[0], 3);
}

TEST(Minimax3, IAMovimientoGanador) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.minimax(tablero, 2, INT_MIN, INT_MAX, amarillo)[0], 0);
}

TEST(Minimax4, OponenteMovimientoGanador) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.minimax(tablero, 2, INT_MIN, INT_MAX, amarillo)[0], 1);
}

TEST(Minimax5, Empate) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(rojo, 2);
  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(amarillo, 2);
  tablero.insertarFicha(rojo, 3);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(rojo, 2);
  tablero.insertarFicha(amarillo, 1);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(amarillo, 3);
  tablero.insertarFicha(rojo, 2);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.minimax(tablero, 2, INT_MIN, INT_MAX, amarillo)[0], 0);
}
