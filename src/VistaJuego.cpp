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
      espacioTablero(new wxPanel(this)),
      turno(new wxStaticText(this, wxID_ANY, "Turno: Jugador 1"))
  {



  espacioTablero->Bind(wxEVT_PAINT, &VistaJuego::onPaint, this);
  espacioTablero->Bind(wxEVT_LEFT_DOWN, &VistaJuego::onClick, this);
  espacioTablero->Bind(wxEVT_RIGHT_DOWN, &VistaJuego::onClick, this);
  espacioTablero->Bind(wxEVT_MIDDLE_DOWN, &VistaJuego::onClick, this);
  Bind(wxEVT_CLOSE_WINDOW, &VistaJuego::onClose, this);

  // creando fuente para el texto de los botones
  wxFont fuenteBotones(wxFontInfo(30).Bold().FaceName("Arial"));
  wxFont fuenteMarcador(wxFontInfo(15).Bold().FaceName("Arial"));

  turno->SetFont(fuenteBotones);

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
  int columna=0;
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
  } else if(estadoActual->empate()) {
    DialogoEmpate* empate =
        new DialogoEmpate(this, (estadoActual->jugadorActual->getNombre()));
    empate->ShowModal();
  }
  // cualquiera de los dos casos anteriores les va a dar la posibilidad de
  // salir, si desean continuar o si no sucede ninguna de las dos
  estadoActual->cambiarTurno();
  controladorTurnos();
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
  }


void VistaJuego::insertarFichaGUI(int columna) {
  int fila = estadoActual->insertarFicha(columna);
  // Si la fila es distinta de -1 es válida
  if (fila != -1) {
    actualizarEstado();
    Refresh();
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

   if (!estadoActual) {
        return;
    }
  
    if(!espacioTablero){
        return;
    }


  int anchoPanel = espacioTablero->GetClientSize().GetWidth();


  if (anchoPanel <= 0) {
        return;
    }

  int anchoCelda = anchoPanel / estadoActual->columnas;


   if (anchoCelda <= 0) {
        return;
    }

  // obtenemos la coordenada del eje X del evento del click, coordenada relativa
  // al tamaño de espacioTablero
  int coordX = event.GetX();

  // Verificar si coordX es válida
    if (coordX < 0) {
        return;
    }
  // covertimos coordenada en columna
  int columnaClick = coordX / anchoCelda;

  // Verificar si columnaClick es válida
    if (columnaClick < 0 || columnaClick >= estadoActual->columnas) {
        return;
    }


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


  event.Skip();
}

void VistaJuego::onBotonSalir(wxCommandEvent& event) { Close(true); }