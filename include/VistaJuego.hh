#ifndef VISTAJUEGO_HH
#define VISTAJUEGO_HH
#include <wx/wx.h>
#include <memory>
#include <EstadoJuego.hh>

/*Esta clase es la encargada de representar la vista del juego,
enviarle los inputs del usuario a controlar,
 modificar su vista de acuerdo a lo que reciba del estado del juego */

class VistaJuego : public wxFrame {
 public:
  VistaJuego(const wxString& title, unique_ptr<EstadoJuego> estado);
  // void actualizarTablero(const EstadoJuego& estadoActual);

 private:
  void onPaint(wxPaintEvent& event);
  void onClick(wxMouseEvent& event);
  wxPanel* espacioTablero;
  unique_ptr<EstadoJuego> estadoActual;
};

#endif