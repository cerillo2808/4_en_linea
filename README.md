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
   ###  VistaJuego
    Esta la clase responsable de manejar la ventana principal del juego.Esta clase deriva de wxFrame y proporciona la interfaz gráfica para jugar , incluyendo el tablero, la información del turno actual, y los botones de control. 
   #  Métodos Principales
    - # ControladorTurnos: El método controladorTurnos en la clase VistaJuego es responsable de gestionar los turnos de los jugadores. Utiliza el método esHumano() del estado actual del juego (estadoActual) para determinar si el jugador actual es un humano.Si el jugador es humano, no se realiza ninguna acción adicional en este método, ya que el evento onClick manejará la interacción del jugador.
    Si el jugador es una IA, se lanza el método llamarJugarIAs() en un hilo separado utilizando std::async con la política de lanzamiento std::launch::async. Esto permite que la IA realice su jugada sin bloquear la interfaz de usuario.

    - # onClick: Este método maneja los eventos de clic del ratón en la ventana del juego, permitiendo a los jugadores humanos interactuar con el tablero. 

    - # llamarJugarIAs: Este método maneja la lógica del jugador de IA, ejecutándose en un hilo separado del principal para no bloquear la interfaz gráfica de usuario (GUI).El método comienza obteniendo la columna en la que la IA desea colocar su ficha. Esto se logra llamando al método jugar() del jugador actual (estadoActual->jugadorActual->jugar()). Este jugador puede ser de tipo IAFacil o IADificil, ambos heredan de IJugador e implementan el método jugar() de manera diferente. Una vez que se ha obtenido la columna en la que la IA desea jugar, se utiliza wxTheApp->CallAfter() para asegurarse de que la actualización de la interfaz gráfica (insertarFichaGUI(columna)) se realice en el hilo principal. 

    - # insertarFichaGUI:Este método maneja la lógica de insertar una ficha en el tablero del juego.Se llama al método estadoActual->insertarFicha(columna) para intentar insertar una ficha en la columna especificada. El método devuelve la fila en la que se inserta la ficha. Si la fila es -1, significa que la inserción no fue exitosa debido a que la columna está llena.Si la fila es distinta de -1, se considera una inserción válida.Se llama al método actualizarEstado() para reflejar cualquier cambio en el estado del juego debido a la inserción de la ficha. Finalmente se llama al método Refresh() para redibujar la ventana y mostrar los cambios en la interfaz.
    
    - # actualizarEstado:El método se encarga de verificar si hay un ganador o un empate en el juego actual y realiza las acciones correspondientes en la interfaz gráfica.Si el método estadoActual->verificarGanador() devuelve verdadero, se crea un nuevo diálogo (DialogoGanador) con el nombre del jugador actual(estadoActual->jugadorActual->getNombre()) y se muestra al usuario mediante ganador->ShowModal(). Este diálogo informa al jugador que ha ganado la partida.
    Si no hay un ganador y el método estadoActual->empate() devuelve verdadero, se crea un nuevo diálogo (DialogoEmpate) con el nombre del jugador actual y se muestra al usuario mediante empate->ShowModal(). Este diálogo informa al jugador que la partida ha terminado en empate.Después de verificar el resultado del juego, se llama al método estadoActual->cambiarTurno() para cambiar al siguiente turno.
    Se llama al método controladorTurnos() para actualizar la interfaz gráfica y permitir al siguiente jugador realizar su jugada.

    - # onPaint: El método VistaJuego::onPaint(wxPaintEvent& event) se encarga de dibujar el estado actual del tablero en la ventana del juego. Utiliza un objeto wxBufferedPaintDC para realizar el dibujo en un búfer fuera de la pantalla antes de copiarlo en la pantalla, lo que ayuda a reducir el parpadeo. Primero establece el color de fondo como azul y luego itera sobre todas las celdas del tablero, dibujando un círculo en cada una. El color del círculo depende del estado de la celda en el tablero (amarillo para el jugador 1, rojo para el jugador 2 y blanco para celdas vacías), y se calcula el tamaño y la posición de cada círculo para que esté centrado en la celda correspondiente.

    - # onClose:El método se encarga de manejar el evento de cierre de la ventana del juego. Primero, verifica si la ventana de configuración de nuevo juego (confNuevoJuego) está abierta y, en caso afirmativo, la cierra. Luego, deshabilita los eventos de pintura y clic del tablero (espacioTablero) para evitar que se procesen después del cierre de la ventana. Finalmente, desvincula el evento de cierre de ventana (wxEVT_CLOSE_WINDOW) de la instancia de VistaJuego actual y llama a event.Skip() para permitir que el evento continúe su propagación.

    - # onBotonSalir: El método maneja el evento de clic en el botón "Salir". Simplemente llama al método Close(true) para cerrar la ventana de juego con confirmación.


    

  ## # Errores conocidos en la Interfaz Gráfica

A nivel interno, los diferentes tipos de jugador se le asigna un número.

- Jugador 0 = Jugador Humano
- Jugador 1 = Jugador IA Fácil
- Jugador 2 = Jugador IA Difícil