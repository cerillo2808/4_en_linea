#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>

class MainFrame : public wxFrame {
 public:
  // Constructor toma el nombre de la ventana como parametro
  MainFrame(const wxString& title);

 private:
  // event handlers del menu inicial
  void nuevoJuego(wxCommandEvent& event);
  void salir(wxCommandEvent& event);
};

#endif