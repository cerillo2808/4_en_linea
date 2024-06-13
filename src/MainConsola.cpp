#include <EstadoJuego.hh>
#include <JugadorDificil.hh>
#include <JugadorFacil.hh>
#include <JugadorHumano.hh>
#include <Tablero.hh>
#include <iostream>

using namespace std;

void imprimirTablero(EstadoJuego juego, int filas, int columnas) {
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      cout << "|" << juego.estadoCelda(i, j) << "|";
      // imprime dentro de los '|' el numero de Color. non_color es 0, entonces
      // empieza todo en 0.
    }
    cout << "\n";
  }
}

bool insertarFicha(EstadoJuego &juego, int columna) {
  int exito = juego.insertarFicha(columna);
  // insertarFicha devuelve -1 cuando no se logró insertar la ficha

  if (exito == -1) {
    return false;
  }

  return true;
}

bool validarEntradaContinuar(char entrada) {
  if (entrada == 'Y' || entrada == 'y') {
    return true;
  }

  if (entrada == 'N' || entrada == 'n') {
    return true;
  }

  return false;
}

int main() {
  cout << "Bienvenidos a 4 en línea" << endl;

  // inicialización de valores
  int tipoJugador1 = 0;
  int tipoJugador2 = 0;
  int filas = 0;
  int columnas = 0;

  cout << "Ingrese el primer jugador: \n[1] Humano \n[2] IA Fácil \n[3] IA "
          "Dificil"
       << endl;
  cin >> tipoJugador1;
  cout << "Ingrese el segundo jugador: \n[1] Humano \n[2] IA Fácil \n[3] IA "
          "Dificil"
       << endl;
  cin >> tipoJugador2;
  cout << "Ingrese cantidad de filas: " << endl;
  cin >> filas;
  cout << "Ingrese cantidad de columnas: " << endl;
  cin >> columnas;

  // se elimina 1, para que entre a estadoJuego correctamente
  tipoJugador1--;
  tipoJugador2--;

  EstadoJuego juego = EstadoJuego(filas, columnas, tipoJugador1, tipoJugador2);
  imprimirTablero(juego, filas, columnas);

  do {
    do {
      if (juego.getTipoJugador() == 0) {
        int columnaInsertar = -1;
        cout << "Ingrese la columna en la que desea insertar su ficha: "
             << endl;
        cin >> columnaInsertar;
        columnaInsertar--;
        // en lógica, la primera columna empieza en 0, pero en el juego, empieza
        // en 1, por eso hay que eliminar 1.

        while (!insertarFicha(juego, columnaInsertar)) {
          cout << "Columna inválida. Ingrese otra columna: " << endl;
          cin >> columnaInsertar;
          columnaInsertar--;
        }
      } else {
        if (juego.getTipoJugador() == 1) {
          cout << "Turno de IA Fácil" << endl;
        } else {
          cout << "Turno de IA Difícil" << endl;
        }
        int columna_IA = juego.jugar();
        juego.insertarFicha(columna_IA);
      }

      imprimirTablero(juego, filas, columnas);

      if (juego.empate()) {
        cout << "Hubo un empate" << endl;
        break;
      }

      if (juego.verificarGanador()) {
        cout << "Gana el jugador " << juego.jugadorActual->getColor()
             << ". ¡Felicidades! " << endl;
        break;
      }

      juego.cambiarTurno();
    } while (true);

    cout << "\nContadores:" << endl;
    cout << "Jugador 1: " << juego.jugadorUno->getGanes() << endl;
    cout << "Jugador 2: " << juego.jugadorDos->getGanes() << endl;

    char querer;

    cout << "¿Quiere jugar otra partida?\n[Y] Sí\n[N] No" << endl;
    cin >> querer;

    while (!validarEntradaContinuar(querer)) {
      cout << "Entrada Inválida" << endl;
      cin >> querer;
    }

    if (querer == 'Y' || querer == 'y') {
      juego.clearTablero();
    }

    if (querer == 'N' || querer == 'n') {
      break;
    }

  } while (true);

  return 0;
}