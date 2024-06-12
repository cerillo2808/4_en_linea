#include <wx/msgdlg.h>

#include <DialogoGanador.hh>
#include <VistaJuego.hh>

DialogoGanador::DialogoGanador(VistaJuego* ventanaVista,
                               std::string nombreJugador)
    : wxDialog(ventanaVista, wxID_ANY, "", wxDefaultPosition, wxSize(570, 280),
               wxDEFAULT_DIALOG_STYLE),
      ventanaVista(ventanaVista),
      nombreJugador(nombreJugador) {
  wxBoxSizer* vertical = new wxBoxSizer(wxVERTICAL);

  std::string mensajeGanador = "Jugador " + nombreJugador + " ha GANADO!!";

  wxStaticText* textoVictoria =
      new wxStaticText(this, wxID_ANY, mensajeGanador);
  wxStaticText* pregunta = new wxStaticText(
      this, wxID_ANY, "Deseas continuar o salir", wxDefaultPosition);
  wxFont fuenteVictoria(wxFontInfo(20).Bold().FaceName("Georgia"));
  textoVictoria->SetFont(fuenteVictoria);

  wxBoxSizer* horizontal = new wxBoxSizer(wxHORIZONTAL);
  wxButton* continuar =
      new wxButton(this, wxID_OK, "Continuar", wxDefaultPosition);
  wxButton* salir = new wxButton(this, wxID_CANCEL, "SALIR", wxDefaultPosition);

  horizontal->AddStretchSpacer();
  horizontal->Add(continuar, 0, wxALL | wxEXPAND, 10);
  horizontal->AddStretchSpacer();
  horizontal->Add(salir, 0, wxALL | wxEXPAND, 10);
  horizontal->AddStretchSpacer();

  vertical->Add(textoVictoria, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
  vertical->Add(pregunta, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
  vertical->AddStretchSpacer();
  vertical->Add(horizontal, 0, wxALL | wxEXPAND, 10);

  this->SetSizer(vertical);
  this->Layout();
  // this->Fit();

  continuar->Bind(wxEVT_BUTTON, &DialogoGanador::continuar, this);
  salir->Bind(wxEVT_BUTTON, &DialogoGanador::salir, this);
}

void DialogoGanador::continuar(wxCommandEvent& event) {
  //primero limpiamos tablero
  ventanaVista->estadoActual->clearTablero();
  //obtenemos los ganes actuales de cada ganador
  int ganesJugadorUno = ventanaVista->estadoActual->getGanes("1");
  int ganesJugadorDos = ventanaVista->estadoActual->getGanes("2");
  //actualizar ganes en la tabla
  ventanaVista->puntajeJugadorUno->SetLabel(wxString::Format("%d", ganesJugadorUno));
  ventanaVista->puntajeJugadorDos->SetLabel(wxString::Format("%d", ganesJugadorDos));
  //encolar un refresh para onpaint
  ventanaVista->Refresh();
  EndModal(wxID_OK);
}

void DialogoGanador::salir(wxCommandEvent& event) {
  EndModal(wxID_CANCEL);
  event.Skip(false);
}