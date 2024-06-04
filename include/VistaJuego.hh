#ifndef VISTAJUEGO_HH
#define VISTAJUEGO_HH
#include <wx/wx.h>
#include <memory>
#include <EstadoJuego.hh>
#include <ConfNuevoJuego.hh>

/*Esta clase es la encargada de representar la vista del juego,
enviarle los inputs del usuario a controlar,
 modificar su vista de acuerdo a lo que reciba del estado del juego */

class VistaJuego : public wxFrame {
 public:
  VistaJuego(ConfNuevoJuego* confNuevoJuego,const wxString title, unique_ptr<EstadoJuego> estado);

 private:
  void onPaint(wxPaintEvent& event);
  void onClick(wxMouseEvent& event);
  wxPanel* espacioTablero;
  wxStaticText* turno;
  unique_ptr<EstadoJuego> estadoActual;
  ConfNuevoJuego* confNuevoJuego;
  void onClose(wxCloseEvent& event);
};

#endif