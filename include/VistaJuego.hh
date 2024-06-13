#ifndef VISTAJUEGO_HH
#define VISTAJUEGO_HH
#include <wx/timer.h>
#include <wx/wx.h>
#include <ConfNuevoJuego.hh>
#include <EstadoJuego.hh>
#include <memory>

/*Esta clase es la encargada de representar la vista del juego,
enviarle los inputs del usuario a controlar,
 modificar su vista de acuerdo a lo que reciba del estado del juego */

class VistaJuego : public wxFrame {
 public:
  VistaJuego(ConfNuevoJuego* confNuevoJuego, const wxString title,
             unique_ptr<EstadoJuego> estado);
  unique_ptr<EstadoJuego> estadoActual;

  wxStaticText* puntajeJugadorUno;
  wxStaticText* puntajeJugadorDos;
 private:
  // métodos
  void onPaint(wxPaintEvent& event);
  void onClick(wxMouseEvent& event);
  void onClose(wxCloseEvent& event);
  void onBotonSalir(wxCommandEvent& event);
  void controladorTurnos();
  void insertarFichaGUI(int columna);
  void llamarJugarIAs();
  void actualizarEstado();

  // atributos
  wxPanel* espacioTablero;
  wxStaticText* turno;
  ConfNuevoJuego* confNuevoJuego;
 

};

#endif