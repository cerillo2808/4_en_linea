#include <VistaJuego.hh>
#include <wx/dcbuffer.h>
#include <wx/wx.h>

VistaJuego::VistaJuego(const wxString& title, int filas, int columnas)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize),
      numFilas(filas),
      numColumnas(columnas)
{   
    //crear el espacio, panel, para el tablero 
     espacioTablero = new wxPanel(this);

    espacioTablero->Bind(wxEVT_PAINT, &VistaJuego::onPaint, this);

    // creando fuente para el texto de los botones
    wxFont fuenteBotones(wxFontInfo(30).Bold().FaceName("Arial"));

    //marcadores de las partidas ganadas
     wxGridSizer* tablaPuntaje=new wxGridSizer(2, 2, 5, 5);

    wxStaticText* etiquetaJugadorUno = new wxStaticText(this, wxID_ANY, "Jugador 1");
    wxStaticText* etiquetaJugadorDos = new wxStaticText(this, wxID_ANY, "Jugador 2");

    wxStaticText* puntajeJugadorUno= new wxStaticText(this, wxID_ANY, "0");
    wxStaticText* puntajeJugadorDos = new wxStaticText(this, wxID_ANY, "0");

    //ingresando todo a la tabla
    tablaPuntaje->Add(etiquetaJugadorUno, 0, wxALIGN_CENTER);
    tablaPuntaje->Add(etiquetaJugadorDos, 0, wxALIGN_CENTER);
    tablaPuntaje->Add(puntajeJugadorUno, 0, wxALIGN_CENTER);
    tablaPuntaje->Add( puntajeJugadorDos, 0, wxALIGN_CENTER);

    wxBoxSizer* panelVertical = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* panelHorizontal = new wxBoxSizer(wxHORIZONTAL);

    //que el marcador quede en la esquina superior derecha

     panelHorizontal->Add(tablaPuntaje, 0, wxALIGN_RIGHT | wxALL, 10);

    panelVertical->Add(panelHorizontal, 0, wxEXPAND | wxTOP | wxRIGHT, 10);
    panelVertical->Add(espacioTablero, 1, wxEXPAND | wxALL, 10);

    this->SetSizerAndFit(panelVertical);

    Maximize(true);

}


//método que se va a llamar cada que el tablero ocupe ser redibujado- por ejemplo que tenga que cambiar de tamaño
void VistaJuego::onPaint(wxPaintEvent& event){
    //el objeto wxBufferedPaintDC permite hacer el dibujo primero en un bufer fuera de la pantalla, cuando ya está se copia en la pantalla
    //esto ayuda a reducir el parpadeo
    wxBufferedPaintDC bufferDibujo(espacioTablero);
    //limpia el area del dibujo:
    bufferDibujo.Clear();

    int alturaPanel,anchoPanel;

    //obtiene el tamaño del panel y lo guarda en las variables altura y ancho del panel
    
    espacioTablero->GetClientSize(&anchoPanel,&alturaPanel);

    //para calcular el ancho y largo de las celdas dividimos el ancho por la cantidad de columnas y el largo por la cantidad de filas

    int anchoCelda= anchoPanel/numColumnas;
    int alturaCelda=alturaPanel/numFilas;

    //entre el ancho y la altura tomamos el menor valor para asegurar que no se nos salga el circulo de área de la casilla
    
    int radio=std::min(anchoCelda,alturaCelda) / 2;


    //vamos a establecer el lápiz que se usa en el buffer para dibujar los circulos del tablero
    bufferDibujo.SetPen(wxPen(*wxBLACK,2));
    //establecemos brush para rellenar las celdas 
    bufferDibujo.SetBrush(*wxWHITE_BRUSH);

    //vamos a ir iterando para dibujar los circulos en cada celda del tablero
    //vamos rellenando por filas

    for(int i=0;i<numColumnas;i++){
        for(int j=0; j<numFilas;j++){
            //calculamos el eje x del centro del circulo
            int ejeX= i*anchoCelda + anchoCelda/2;
            int ejeY=j*alturaCelda + alturaCelda/2;
            bufferDibujo.DrawCircle(ejeX,ejeY,radio);
        }
    }

}



