#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <TableroGUI.hh>
#include <iostream>
#include <algorithm>

using namespace std;

TableroGUI::TableroGUI(const wxString& title,int filas, int columnas)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(500, 400)),numColumnas(columnas),numFilas(filas) {


    //asegurarse que el panel se repinte adecuadamente
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    //No lo enlazamos a un objeto especifico si no a la misma ventana
    //evento para el caso de dibujar el tablero
    Bind(wxEVT_PAINT, &TableroGUI::onPaint,this);
    //evento para los clicks del usuario
    Bind(wxEVT_LEFT_DOWN, &TableroGUI::onMouseClick,this);

    

}

//método que se va a llamar cada que el tablero ocupe ser redibujado- por ejemplo que tenga que cambiar de tamaño
void TableroGUI::onPaint(wxPaintEvent& event){
    //el objeto wxBufferedPaintDC permite hacer el dibujo primero en un bufer fuera de la pantalla, cuando ya está se copia en la pantalla
    //esto ayuda a reducir el parpadeo
    wxBufferedPaintDC bufferDibujo(this);
    //limpia el area del dibujo:
    bufferDibujo.Clear();

    int alturaPanel,anchoPanel;

    //obtiene el tamaño del panel y lo guarda en las variables altura y ancho del panel
    
    GetClientSize(&anchoPanel,&alturaPanel);

    //para calcular el ancho y largo de las celdas dividimos el ancho por la cantidad de columnas y el largo por la cantidad de filas

    int anchoCelda= anchoPanel/numColumnas;
    int alturaCelda=alturaCelda/numFilas;

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
            int ejeY=j*alturaCelda* alturaCelda/2;
            bufferDibujo.DrawCircle(ejeX,ejeY,radio);
        }
    }

}

void TableroGUI::onMouseClick(wxMouseEvent& event){

}