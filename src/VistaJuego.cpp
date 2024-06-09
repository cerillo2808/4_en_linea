#include <wx/dcbuffer.h>
#include <wx/timer.h>
#include <wx/wx.h>
#include <DialogoEmpate.hh>
#include <DialogoGanador.hh>
#include <EstadoJuego.hh>
#include <VistaJuego.hh>
#include <memory>
#include <future>

VistaJuego::VistaJuego(ConfNuevoJuego* confNuevoJuego, const wxString title,
                       unique_ptr<EstadoJuego> estado)
    : wxFrame(confNuevoJuego, wxID_ANY, title, wxDefaultPosition,
              wxDefaultSize),
      confNuevoJuego(confNuevoJuego),
      estadoActual(move(estado)),
      timer(new wxTimer(this)),
      hayAnimacion(false),
      valEjeY(0) {
  // crear el espacio, panel, para el tablero
  espacioTablero = new wxPanel(this);

  espacioTablero->Bind(wxEVT_PAINT, &VistaJuego::onPaint, this);
  espacioTablero->Bind(wxEVT_LEFT_DOWN, &VistaJuego::onClick, this);
  espacioTablero->Bind(wxEVT_RIGHT_DOWN, &VistaJuego::onClick, this);
  espacioTablero->Bind(wxEVT_MIDDLE_DOWN, &VistaJuego::onClick, this);
  Bind(wxEVT_CLOSE_WINDOW, &VistaJuego::onClose, this);

  // creando fuente para el texto de los botones
  wxFont fuenteBotones(wxFontInfo(30).Bold().FaceName("Arial"));
  wxFont fuenteMarcador(wxFontInfo(15).Bold().FaceName("Arial"));

  // marcadores de las partidas ganadas
  wxGridSizer* tablaPuntaje = new wxGridSizer(2, 2, 7, 6);

  wxStaticText* etiquetaJugadorUno =
      new wxStaticText(this, wxID_ANY, "Jugador 1");
  etiquetaJugadorUno->SetFont(fuenteMarcador);
  wxStaticText* etiquetaJugadorDos =
      new wxStaticText(this, wxID_ANY, "Jugador 2");
  etiquetaJugadorDos->SetFont(fuenteMarcador);

  wxStaticText* puntajeJugadorUno = new wxStaticText(this, wxID_ANY, "0");
  puntajeJugadorUno->SetFont(fuenteMarcador);
  wxStaticText* puntajeJugadorDos = new wxStaticText(this, wxID_ANY, "0");
  puntajeJugadorDos->SetFont(fuenteMarcador);
  // ingresando todo a la tabla
  tablaPuntaje->Add(etiquetaJugadorUno, 0, wxALIGN_CENTER);
  tablaPuntaje->Add(etiquetaJugadorDos, 0, wxALIGN_CENTER);
  tablaPuntaje->Add(puntajeJugadorUno, 0, wxALIGN_CENTER);
  tablaPuntaje->Add(puntajeJugadorDos, 0, wxALIGN_CENTER);

  // Texto estático para indicar el turno de los jugadores
  turno = new wxStaticText(this, wxID_ANY, "Turno: Jugador 1");
  turno->SetFont(fuenteBotones);
  wxButton* botonSalir =
      new wxButton(this, wxID_ANY, "SALIR", wxDefaultPosition, wxSize(150, 90));
  botonSalir->SetFont(fuenteMarcador);
  botonSalir->Bind(wxEVT_BUTTON, &VistaJuego::onBotonSalir, this);

  wxBoxSizer* panelVertical = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* panelHorizontal = new wxBoxSizer(wxHORIZONTAL);

  // que el marcador quede en la esquina superior derecha

  panelHorizontal->Add(tablaPuntaje, 0, wxALIGN_RIGHT | wxALL, 10);
  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(turno, 0, wxALIGN_CENTER | wxALL, 10);
  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(botonSalir, 0, wxALIGN_LEFT | wxALL, 10);

  int margenLados = 60;
  panelVertical->Add(panelHorizontal, 0, wxEXPAND | wxTOP | wxRIGHT, 10);
  panelVertical->Add(espacioTablero, 1,
                     wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM,
                     margenLados);

  this->SetSizerAndFit(panelVertical);

  // que incialmente este maximizado
  Maximize(true);

  // Llama al controlador de turnos para comenzar el juego
  controladorTurnos();
}

// método que trabaja en un hilo distinto
void VistaJuego::llamarJugarIAs() {
  // TO-DO: corregir que jugar devuelva una columna
  int columna;
  //columna= estadoActual->jugadorActual->jugar();

  //Las actualizaciones de la GUI tiene que realizarse en el hilo principal 
  // con wxTheApp->CallAfter hacemos que insertarFichaGUI se ejecute en el hilo principal
  //ocupamos el lamba para pasar el argumento de columna 
  wxTheApp->CallAfter([this, columna]() {
        insertarFichaGUI(columna);
    });
}

/*Este es el método que va controlando los turnos
va ir mostrando en panatalla el nombre del jugadro del cual es el turno 1 o 2
dependiendo del tipo de jugador va a habilitar o no onclick*/
void VistaJuego::controladorTurnos() {
  // obtenemos nombre del jugador
  wxString nombreActual = estadoActual->jugadorActual->getNombre();
  turno->SetLabel("Turno: " + nombreActual);
  // TODO:método de si es humano para saber si habilitar o no el onclick
  if (estadoActual->esHumano()) {
    // si es true no hace nada porque onclick se encarga
  } else {
    // Inicia la ejecución de llamar IAs en un hilo distinto al de la GUI
     std::async(std::launch::async, &VistaJuego::llamarJugarIAs, this);
  }
}

void VistaJuego::actualizarEstado() {
  if (estadoActual->verificarGanador()) {
    DialogoGanador* ganador =
        new DialogoGanador(this, (estadoActual->jugadorActual->getNombre()));
    ganador->ShowModal();
  } else if (estadoActual->empate()) {
    DialogoEmpate* empate =
        new DialogoEmpate(this, (estadoActual->jugadorActual->getNombre()));
  }
  // cualquiera de los dos casos anteriores les va a dar la posibilidad de
  // salir, si desean continuar o si no sucede ninguna de las dos
  estadoActual->cambiarTurno();
  controladorTurnos();
}

// método que se llama cuando se va a insertar una ficha, inicializa la
// animación y los valores que se ocupan para ella recibe en que columna se
// quiere insertar la ficha, así como el color del jugador que la está
// insertando se establecio: 1=amarillo, 2=rojo
void VistaJuego::iniciarAnimacion(int columna, int filaObj) {
  columnaObjetivo = columna;
  filaObjetivo = filaObj;
  hayAnimacion = true;
  // el valor del eje Y tiene que iniciar en 0, se ve "cayendo"
  valEjeY = 0;
  // vamos a llamar a onTimer cada 16 milisegundos
  timer->Start(16);
}

// método para obtener la coordena Y donde se encuentra una ficha insertada
// es utilizado para en onTimer saber cuando ya se llego a la coordenada
// deseada, donde insertamos la ficha
int VistaJuego::obtenerCoordY(int filaObjetivo) {
  // primero ocupamos conocer el espacio total de tablero donde se hace el
  // dibujo
  int altura = espacioTablero->GetClientSize().GetHeight();
  // dividimos la altura total entre la  cantidad de filas, así obtenemos la
  // altura de cada celda
  int alturaCelda = altura / estadoActual->filas;
  // obtenemos la altura del borde superior de la celda a eso le sumamos la
  // mitad de la altura de la celda, sumandolos obtenemos la coordenada del
  // centro
  return filaObjetivo * alturaCelda + alturaCelda / 2;
}

// Método que actualiza la posición de la ficha en cada intervalo de tiempo
// definido por el wxtimer

void VistaJuego::onTimer(wxTimerEvent& event) {
  // revisamos que la animación siga en proceso
  if (!hayAnimacion) {
    // no hay una animación detenemos el timer
    timer->Stop();
    return;
  }
  // vamos a ir incrementando la posición de la ficha en el ejeY
  valEjeY = valEjeY + 5;
  // si el valor de la ficha en el eje Y llega al valor del eje Y de la fila
  // correspondiente o se pasa detenemos la animación y el timer
  if (valEjeY >= obtenerCoordY(filaObjetivo)) {
    hayAnimacion = false;
    timer->Stop();
    // cuando se para la animación actualizamos el estado
    actualizarEstado();
  }
  Refresh();  // forzamos un repintado
}

// método que se va a llamar cada que el tablero ocupe ser redibujado- por
// ejemplo que tenga que cambiar de tamaño
void VistaJuego::onPaint(wxPaintEvent& event) {
  // el objeto wxBufferedPaintDC permite hacer el dibujo primero en un bufer
  // fuera de la pantalla, cuando ya está se copia en la pantalla esto ayuda a
  // reducir el parpadeo
  wxBufferedPaintDC bufferDibujo(espacioTablero);

  // Establece el color de fondo a azul
  bufferDibujo.SetBackground(*wxBLUE);
  // limpia el area del dibujo:
  bufferDibujo.Clear();

  int alturaPanel, anchoPanel;

  // obtiene el tamaño del panel y lo guarda en las variables altura y ancho del
  // panel

  espacioTablero->GetClientSize(&anchoPanel, &alturaPanel);

  // para calcular el ancho y largo de las celdas dividimos el ancho por la
  // cantidad de columnas y el largo por la cantidad de filas

  int anchoCelda = anchoPanel / estadoActual->columnas;
  int alturaCelda = alturaPanel / estadoActual->filas;

  // entre el ancho y la altura tomamos el menor valor para asegurar que no se
  // nos salga el circulo de área de la casilla

  int radio = std::min(anchoCelda, alturaCelda) / 2;

  // vamos a establecer el lápiz que se usa en el buffer para dibujar los
  // circulos del tablero
  bufferDibujo.SetPen(wxPen(*wxBLACK, 2));

  // vamos a ir iterando para dibujar los circulos en cada celda del tablero
  // vamos rellenando por filas
    for (int i = 0; i < estadoActual->filas; i++) {
      for (int j = 0; j < estadoActual->columnas; j++) {
        if(estadoActual->estadoCelda(i,j)==1){
          bufferDibujo.SetBrush(*wxYELLOW_BRUSH);
        }else if(estadoActual->estadoCelda(i,j)==2){
          bufferDibujo.SetBrush(*wxRED_BRUSH);
        }else{
            bufferDibujo.SetBrush(*wxWHITE_BRUSH);
        }
        // calculamos el eje x del centro del circulo
        int ejeX = j * anchoCelda + anchoCelda / 2;
        int ejeY = i * alturaCelda + alturaCelda / 2;
        bufferDibujo.DrawCircle(ejeX, ejeY, radio);
      }
    }

  // dibuja la animación

  if (hayAnimacion) {
    // en lugar de por el espacio de la celda, seleccionamos el color por el
    // jugador
    const wxBrush* brush = (estadoActual->jugadorActual->getColor() == 1)
                               ? wxYELLOW_BRUSH
                               : wxRED_BRUSH;
    bufferDibujo.SetBrush(*brush);
    // vamos a usar las cordenas de ese momento del eje Y y X
    int ejeX = columnaObjetivo * anchoCelda + anchoCelda / 2;
    int ejeY = valEjeY;
    bufferDibujo.DrawCircle(ejeX, ejeY, radio);
  }
}

void VistaJuego::insertarFichaGUI(int columna) {
  int fila = estadoActual->insertarFicha(columna);
  // Si la fila es distinta de -1 es válida
  if (fila != -1) {
    iniciarAnimacion(columna, fila);

  } else {
    // TO-DO: Manajear caso donde no se logró insertar
    wxMessageBox("La columna está llena, selecciona otra columna.");
  }
}

void VistaJuego::onClick(wxMouseEvent& event) {
  // verificamos que se ejecute solo cuando es un humano quien juega}
  //también verificamos que haya una instancia de estado en ese momento
  if (estadoActual && !estadoActual->esHumano()) {
    return;
  }

  int anchoPanel = espacioTablero->GetClientSize().GetWidth();

  int anchoCelda = anchoPanel / estadoActual->columnas;
  // obtenemos la coordenada del eje X del evento del click, coordenada relativa
  // al tamaño de espacioTablero
  int coordX = event.GetX();
  // covertimos coordenada en columna
  int columnaClick = coordX / anchoCelda;

  // llamamos a método común para insertar una ficha
  insertarFichaGUI(columnaClick);
}

void VistaJuego::onClose(wxCloseEvent& event) {
  if (confNuevoJuego) {
    confNuevoJuego->Close(true);
    //confNuevoJuego = nullptr;
  }
    //desabilitamos todos los eventos de vistaJuego
    espacioTablero->Unbind(wxEVT_PAINT, &VistaJuego::onPaint, this);
    espacioTablero->Unbind(wxEVT_LEFT_DOWN, &VistaJuego::onClick, this);
    espacioTablero->Unbind(wxEVT_RIGHT_DOWN, &VistaJuego::onClick, this);
    espacioTablero->Unbind(wxEVT_MIDDLE_DOWN, &VistaJuego::onClick, this);
    Unbind(wxEVT_CLOSE_WINDOW, &VistaJuego::onClose, this);

     if (timer) {
        timer->Stop();
        delete timer;
        timer = nullptr;
    }


  event.Skip();
}

void VistaJuego::onBotonSalir(wxCommandEvent& event) { Close(true); }