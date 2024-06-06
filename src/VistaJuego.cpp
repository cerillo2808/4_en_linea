#include <wx/dcbuffer.h>
#include <wx/wx.h>
#include <wx/timer.h>
#include <EstadoJuego.hh>
#include <DialogoEmpate.hh>
#include <DialogoGanador.hh>
#include <memory>
#include <VistaJuego.hh>

VistaJuego::VistaJuego(ConfNuevoJuego* confNuevoJuego,const wxString title, unique_ptr<EstadoJuego> estado)
    : wxFrame(confNuevoJuego, wxID_ANY, title, wxDefaultPosition, wxDefaultSize),confNuevoJuego(confNuevoJuego),
      estadoActual(move(estado)) {

  // crear el espacio, panel, para el tablero
  espacioTablero = new wxPanel(this);

  espacioTablero->Bind(wxEVT_PAINT, &VistaJuego::onPaint, this);
  espacioTablero->Bind(wxEVT_LEFT_DOWN, &VistaJuego::onClick,this);
  espacioTablero->Bind(wxEVT_RIGHT_DOWN,&VistaJuego::onClick,this );
  espacioTablero->Bind(wxEVT_MIDDLE_DOWN, &VistaJuego::onClick,this);
  Bind(wxEVT_CLOSE_WINDOW,&VistaJuego::onClose, this);

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

  //Texto estático para indicar el turno de los jugadores
  turno=new wxStaticText(this,wxID_ANY,"Turno: Jugador 1");
  turno->SetFont(fuenteBotones);
  wxButton* botonSalir=new wxButton(this,wxID_ANY,"SALIR", wxDefaultPosition,wxSize(150, 90));
  botonSalir->SetFont(fuenteMarcador);

  wxBoxSizer* panelVertical = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* panelHorizontal = new wxBoxSizer(wxHORIZONTAL);

  // que el marcador quede en la esquina superior derecha

  panelHorizontal->Add(tablaPuntaje, 0, wxALIGN_RIGHT | wxALL, 10);
  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(turno, 0, wxALIGN_CENTER | wxALL, 10 );
  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(botonSalir,0,wxALIGN_LEFT | wxALL, 10);


  int margenLados = 60;
  panelVertical->Add(panelHorizontal, 0, wxEXPAND | wxTOP | wxRIGHT, 10);
  panelVertical->Add(espacioTablero, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, margenLados);

  this->SetSizerAndFit(panelVertical);

  
  //que incialmente este maximizado
  Maximize(true);
}

//método que se llama cuando se va a insertar una ficha, inicializa la animación y los valores que se ocupan para ella
//recibe en que columna se quiere insertar la ficha, así como el color del jugador que la está insertando
//se establecio: 1=amarillo, 2=rojo
void VistaJuego::animacion(int columna, int color){
  columna=columna;
  color=color;
  //el eje Y de la pantalla va a estar originalmente en 0 para que caiga desde arriba
  valEjeY=0;
  hayAnimacion=true;
  //TODO: Correción en estado para que insertarFicha devuelva int
  //insertarficha me devuelve el entero donde se insertar la ficha en la lógica, aquí lo usamos para saber hasta que fila debe de llegar la ficha en su caída
  //fila=estadoActual->insertarFicha();

  //vamos a llamar a onTimer cada 16 milisegundos
  timer->Start(16);
}

//Método que actualiza la posición de la ficha en cada intervalo de tiempo definido por el wxtimer

void VistaJuego::onTimer(wxTimerEvent& event){

  //vamos a ir incrementando la posición de la ficha en el ejeY
  valEjeY=valEjeY+5;

  //si el valor de la ficha en el eje Y llega al valor del eje Y de la fila correspondiente o se pasa detenemos la animación y el timer

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

  for (int i = 0; i < estadoActual->columnas; i++) {
    for (int j = 0; j < estadoActual->filas; j++) {
      if(estadoActual->estadoCelda(i,j)==1){
        bufferDibujo.SetBrush(*wxYELLOW_BRUSH);
      }else if(estadoActual->estadoCelda(i,j)==2){
        bufferDibujo.SetBrush(*wxRED_BRUSH);
      }else{
          bufferDibujo.SetBrush(*wxWHITE_BRUSH);
      }
      // calculamos el eje x del centro del circulo
      int ejeX = i * anchoCelda + anchoCelda / 2;
      int ejeY = j * alturaCelda + alturaCelda / 2;
      bufferDibujo.DrawCircle(ejeX, ejeY, radio);
    }
  }
}





void VistaJuego::onClick(wxMouseEvent& event){

    int anchoPanel=espacioTablero->GetClientSize().GetWidth();
    
    int anchoCelda = anchoPanel / estadoActual->columnas;
    //obtenemos la coordenada del eje X del evento del click, coordenada relativa al tamaño de espacioTablero
    int coordX=event.GetX();
    //covertimos coordenada en columna
    int columnaClick= coordX/anchoCelda;
    
    wxLogMessage("Clic en la columna %d", columnaClick);


    DialogoGanador* ganador= new DialogoGanador(this, "UNO");
    ganador->ShowModal();
    // DialogoEmpate* empate= new DialogoEmpate(this);
    // empate->ShowModal();

    if(estadoActual->insertarFicha(columnaClick)){
      //Sí pudimos insertar ficha, así que con refresh encolamos evento de dibujar
      Refresh();
    }
    //luego de que se pone un ficha verificamo si empate, si ganador y si no cambiamos de turno
    if(estadoActual->verificarGanador()){
    
      }else if(estadoActual->empate()){
      
      }else{
        // estadoActual->cambiarTurno();
        // turno->SetLabel("falta método para obtener nombre del jugador actual");
      }


}



void VistaJuego::onClose(wxCloseEvent& event){
  if (confNuevoJuego){
      confNuevoJuego->Close(true);
  }
  event.Skip();
}


