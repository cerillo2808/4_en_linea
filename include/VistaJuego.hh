#ifndef VISTAJUEGO_HH
#define VISTAJUEGO_HH
#include <wx/wx.h>
#include <wx/timer.h>
#include <memory>
#include <EstadoJuego.hh>
#include <ConfNuevoJuego.hh>

/*Esta clase es la encargada de representar la vista del juego,
enviarle los inputs del usuario a controlar,
 modificar su vista de acuerdo a lo que reciba del estado del juego */

class VistaJuego : public wxFrame {
 public:
  VistaJuego(ConfNuevoJuego* confNuevoJuego,const wxString title, unique_ptr<EstadoJuego> estado);
  unique_ptr<EstadoJuego> estadoActual;
 private:
 //métodos 
  void onPaint(wxPaintEvent& event);
  void onClick(wxMouseEvent& event);
  void onTimer(wxTimerEvent& event);
  void animacion(int columna, int color);
  void onClose(wxCloseEvent& event);
  void controladorTurnos();

  //atributos
  wxPanel* espacioTablero;
  wxStaticText* turno;
  ConfNuevoJuego* confNuevoJuego;

  int columna;
  int filaDondeInserto;
  int turnoActual;
  int colorFicha;
  wxTimer* timer;
  bool hayAnimacion;
  int valEjeY;
  
};

#endif