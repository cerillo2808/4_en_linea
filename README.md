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

- El jugador 1 siempre será color amarillo y el jugador 2 color rojo.

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

La interfaz gráfica está compuesta por varias clases. Estás son:App,MainFrame,ConfNuevoJuego,DialogoEmpate, DialogoGanador, y Vista Juego.

A continución un desglose de cada clase

### App
     Crea una ventana principal a partir de una instancia de mainFrame.Está clase contiene wxIMPLEMENT_APP(App) el cual es el punto de entrada de la interfaz, al crear una instancia de App, inicializar, configurar el entorno e iniciar el bucle de eventos para la interfaz. 
### MainFrame
    Está es la clase que es instanciada desde App.Está es la ventana principal de la interfaz, es la primera en mostrase, y cada que se cierren sus ventanas hijas, se regresa a está ventana. La ventana principal contiene un mensaje de bienvenida y dos botones: "NUEVO JUEGO" y "SALIR". Al hacer clic en el botón "NUEVO JUEGO", se abre una ventana de configuración para un nuevo juego.
### ConfNuevoJuego
    Está es la ventana que se crea cuando el usuario desde MainFrame hace clic en "NUEVO JUEGO". La ventana permite al usuario seleccionar las configuraciones del juego, como el tipo de jugador, el tamaño del tablero y iniciar el juego.

    ## Funcionalidades principales de ConfNuevoJuego
    
    - La ventana permite al usuario seleccionar el tipo de jugador para el Jugador 1 y el  Jugador 2 entre tres opciones: Humano, IA Fácil o IA Difícil.Estas selecciones se realizan mediante dos radio boxes, donde el usuario puede elegir una opción para cada jugador.
    - El usuario puede seleccionar las dimensiones del tablero, especificando el número de casillas horizontales y verticales.Se utilizan controles de giro (spin controls) para permitir al usuario ajustar estas dimensiones dentro de un rango predefinido. El mínimo que se puede seleccionar son 4, y máximo 10. Si no se selecciona nada se muestran los mínimos. 
    - La ventana incluye un botón "INICIAR" que permite al usuario iniciar el juego con las configuraciones seleccionada.Al presionar "INICIAR" usamos un make_unique<EstadoJuego>(...) para crear una instancia de la clase EstadoJuego, que representa el estado inicial del juego. Esta instancia se crea utilizando las configuraciones seleccionadas por el usuario, como el número de filas y columnas del tablero, así como el tipo de jugador para el Jugador 1 y el Jugador 2. Además, se crea una instancia de la clase VistaJuego, que representa la ventana del juego.Se pasa un puntero a la ventana principal (this), un título para la ventana ("4 en linea") y se mueve la instancia del estado del juego a la ventana.
    - La ventana también incluye un botón de regresar que permite al usuario volver a la ventana principal, es decir a la proporcionada por MainFrame.


  ## # Errores conocidos en la Interfaz Gráfica

A nivel interno, los diferentes tipos de jugador se le asigna un número.

- Jugador 0 = Jugador Humano
- Jugador 1 = Jugador IA Fácil
- Jugador 2 = Jugador IA Difícil