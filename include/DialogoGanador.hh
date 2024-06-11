#ifndef DIALOGOGANADOR_HH
#define DIALOGOGANADOR_HH
#include <wx/msgdlg.h>

#include <VistaJuego.hh>
#include <string>

class DialogoGanador : public wxDialog {
 public:
  // Constructor
  DialogoGanador(VistaJuego* ventanaVista, string nombreJugador);

 private:
  void continuar(wxCommandEvent& event);
  void salir(wxCommandEvent& event);
  VistaJuego* ventanaVista;
  string nombreJugador;
};

#endif