# 4_en_linea
Proyecto Programado 2 del curso de Programación 2, en la UCR.

## Miembros del Equipo
- Luis Eduardo Valverde Soza - C18128
- Melany Alfaro Barrantes - C30208
- Liqing Yosery Zheng Lu - C38680

## Instrucciones para Ejecutar el Programa
Para compilar, use los comandos: 
    `cmake -S . -B build -G Ninja` y `cmake --build build`

Para ejectuar las pruebas, ingrese a la carpeta `build/tests`, y ejecute el comando `ctest`.

## Consideraciones Técnicas
- El tablero es un vector de vectores de enum Color. Este tablero cuenta a partir del 0 (ej. en un tablero 2x2, existe fila 0 y 1, y de igual manera las columnas).

- Fila 0 es la fila más superior, mientras que columna 0 la columna más izquierda. 

- El jugador 1 siempre será color azul y el jugador 2 color rojo.

- Se juega hasta que se llegue a un ganador o se llene el tablero y resulte en empate.

- El programa no detecta empates si el tablero aún no está lleno.

## Funcionalidad

### Tablero
- tiene dos constructores, uno para crear el tablero de juego, y otro para copias.

- tiene varios métodos internos que llevan a un método de verificar si hay ganador. 

- tiene un método para verificar si el tablero está lleno (si hay empate).

- método para insertarle fichas al tablero.

### Jugadores

#### Humano
Juega a partir de la interfaz. Es una interacción con el usuario.

#### Fácil
Selecciona la columna en donde meterá la ficha de manera pseudo-random.

#### Difícil
Selecciona la columna con minimax.

### Interfaz Gráfica