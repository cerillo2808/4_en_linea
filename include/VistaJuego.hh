#ifndef VISTAJUEGO_HH
#define VISTAJUEGO_HH
#include <EstadoJuego.hh>

#include <wx/wx.h>

/*Esta clase es la encargada de representar la vista del juego, 
enviarle los inputs del usuario a controlar,
 modificar su vista de acuerdo a lo que reciba del estado del juego */

class VistaJuego:public wxFrame{
    public:
        VistaJuego(const wxString& title,int filas, int columnas);
        //void actualizarTablero(const EstadoJuego& estadoActual);



    private:
        void onPaint(wxPaintEvent& event);
        wxPanel* espacioTablero;
        int numColumnas;
        int numFilas;
};


#endif