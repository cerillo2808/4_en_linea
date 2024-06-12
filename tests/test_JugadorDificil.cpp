#include <gtest/gtest.h>

#include <Color.hh>
#include <JugadorDificil.hh>
#include <Tablero.hh>
#include <algorithm>
#include <chrono>
#include <climits>

TEST(JugadorDificil, ConstructorJugador) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getColor(), amarillo);
}

TEST(JugadorDificil, obtenerNombre) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getNombre(), "IA");
}

TEST(JugadorDificil, obtenerGanes) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
}

TEST(JugadorDificil, modificarGane) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 1);
}

TEST(JugadorDificil, modificarGaneVariasVeces) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.getGanes(), 0);
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  ia.setGanes();
  EXPECT_EQ(ia.getGanes(), 4);
}

TEST(JugadorDificil, mismoColorDeIA) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, amarillo), 2);
}

TEST(JugadorDificil, espacioVacio) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, non_color), 1);
}

TEST(JugadorDificil, colorOponente) {
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.valorJugada(amarillo, rojo), INT_MIN);
}

TEST(JugadorDificil, Vacio) {
  Tablero tablero(4, 4);
  JugadorDificil ia("IA", amarillo);
  EXPECT_EQ(ia.puntajeTablero(tablero), 0);
}

TEST(JugadorDificil, JugadaIA1) {
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

  EXPECT_EQ(ia.puntajeTablero(tablero), 46);
}

TEST(JugadorDificil, JugadaIA2) {
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

  EXPECT_EQ(ia.puntajeTablero(tablero), 46);
}

TEST(JugadorDificil, JugadaOponente) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);
  tablero.insertarFicha(rojo, 0);

  EXPECT_EQ(ia.puntajeTablero(tablero), -46);
}

TEST(JugadorDificil, dosFilasVerticales) {
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

  EXPECT_EQ(ia.puntajeTablero(tablero), 0);
}

TEST(JugadorDificil, dosFilasHorizontales) {
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

  EXPECT_EQ(ia.puntajeTablero(tablero), 0);
}

TEST(JugadorDificil, dosFichasDistribuidas) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  tablero.insertarFicha(rojo, 2);

  tablero.insertarFicha(amarillo, 0);

  EXPECT_EQ(ia.puntajeTablero(tablero), 5);
}

TEST(JugadorDificil, IAIniciaLaPartida) {
  Tablero tablero(4, 4);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  auto tiempoInicio = std ::chrono ::time_point_cast<std ::chrono ::seconds>(
      std ::chrono ::system_clock::now());
  EXPECT_EQ(ia.minimax(tiempoInicio, 3600.0, tablero, 1, INT_MIN, INT_MAX,
                       amarillo)[0],
            0);
}

TEST(JugadorDificil, IAEscogeMejorMovimiento) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  auto tiempoInicio = std ::chrono ::time_point_cast<std ::chrono ::seconds>(
      std ::chrono ::system_clock::now());
  EXPECT_EQ(ia.minimax(tiempoInicio, 3600.0, tablero, 2, INT_MIN, INT_MAX,
                       amarillo)[0],
            3);
}

TEST(JugadorDificil, IAMovimientoGanador) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  auto tiempoInicio = std ::chrono ::time_point_cast<std ::chrono ::seconds>(
      std ::chrono ::system_clock::now());
  EXPECT_EQ(ia.minimax(tiempoInicio, 3600.0, tablero, 2, INT_MIN, INT_MAX,
                       amarillo)[0],
            0);
}

TEST(JugadorDificil, OponenteMovimientoGanador) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  auto tiempoInicio = std ::chrono ::time_point_cast<std ::chrono ::seconds>(
      std ::chrono ::system_clock::now());
  EXPECT_EQ(ia.minimax(tiempoInicio, 3600.0, tablero, 2, INT_MIN, INT_MAX,
                       amarillo)[0],
            1);
}

TEST(JugadorDificil, Empate) {
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

  auto tiempoInicio = std ::chrono ::time_point_cast<std ::chrono ::seconds>(
      std ::chrono ::system_clock::now());
  EXPECT_EQ(ia.minimax(tiempoInicio, 3600.0, tablero, 2, INT_MIN, INT_MAX,
                       amarillo)[0],
            0);
}

TEST(JugadorDificil, JugarIA1) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.jugar(tablero), 3);
}

TEST(JugadorDificil, JugarIA2) {
  Tablero tablero(4, 4);

  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(amarillo, 0);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);
  tablero.insertarFicha(rojo, 1);

  JugadorDificil ia("IA", amarillo);
  ia.setColorOponente(rojo);

  EXPECT_EQ(ia.jugar(tablero), 1);
}