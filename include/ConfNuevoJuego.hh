#ifndef CONFNUEVOJUEGO_HH
#define CONFNUEVOJUEGO_HH
#include <MainFrame.hh>
#include <wx/wx.h>

class ConfNuevoJuego : public wxFrame {
 public:
  // Constructor toma el nombre de la ventana como parametro
  ConfNuevoJuego(MainFrame* mainFrame,const wxString& title);

 private:
  void jugadorUno(wxCommandEvent& event);
  void jugadorDos(wxCommandEvent& event);
  void filasTablero(wxCommandEvent& event);
  void columnasTablero(wxCommandEvent& event);
  void botonRegresar(wxCommandEvent& event);
  void botonIniciar(wxCommandEvent& event);

  MainFrame* mainFrame;
  int tipoJugadorUno;
  int tipoJugadorDos;
  int numFilasTablero;
  int numColumnasTablero;
};

#endif