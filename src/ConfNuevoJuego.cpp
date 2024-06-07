#include <wx/spinctrl.h>
#include <wx/wx.h>
#include <memory>
#include <EstadoJuego.hh>
#include <ConfNuevoJuego.hh>
#include <VistaJuego.hh>

ConfNuevoJuego::ConfNuevoJuego(MainFrame* mainFrame, const wxString& title)
    : wxFrame(mainFrame, wxID_ANY, title, wxDefaultPosition, wxSize(500, 400)) {
  // luego se va a sobreescribir pero es para evitar errores:

  numFilasTablero = numColumnasTablero = 4;

  wxPanel* panelPrincipal = new wxPanel(this);
  panelPrincipal->SetBackgroundColour((wxColour("#07c3ed")));

  wxBoxSizer* panelVertical = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* panelHorizontal = new wxBoxSizer(wxHORIZONTAL);

  // creando fuente para el texto de los botones
  wxFont fuente(wxFontInfo(20).Bold().FaceName("Arial"));

  wxFont fuenteR(wxFontInfo(20).FaceName("Arial"));

  wxFont fuenteT(wxFontInfo(15).Bold().FaceName("Arial"));

  wxStaticText* staticText =
      new wxStaticText(panelPrincipal, wxID_ANY,
                       "Configuraciones del nuevo juego", wxDefaultPosition);
  staticText->SetFont(fuente);

  wxArrayString choices;
  //radioBox nos devolvera un 0 si es el humano
  choices.Add("Humano");
  //radioBox nos devolvera 1 si es el IA fácil
  choices.Add("IA Facil");
  //radioBox nos devolvera 2 si es el IA díficil
  choices.Add("IA Dificil");

  wxRadioBox* radioBox1 = new wxRadioBox(
      panelPrincipal, wxID_ANY, "Seleccione el Jugador 1 : ", wxDefaultPosition,
      wxDefaultSize, choices);
  wxRadioBox* radioBox2 = new wxRadioBox(
      panelPrincipal, wxID_ANY, "Seleccione el Jugador 2 : ", wxDefaultPosition,
      wxDefaultSize, choices);

  radioBox1->SetFont(fuenteR);
  radioBox2->SetFont(fuenteR);

  wxStaticText* textoSpin = new wxStaticText(
      panelPrincipal, wxID_ANY, "Seleccione las dimenciones del tablero",
      wxDefaultPosition);
  textoSpin->SetFont(fuenteT);
  wxStaticText* textoSpin2 = new wxStaticText(
      panelPrincipal, wxID_ANY, "Casillas Horizontales: ", wxPoint(120, 150));
  textoSpin2->SetFont(fuenteR);
  wxSpinCtrl* spinCtrl =
      new wxSpinCtrl(panelPrincipal, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxSP_ARROW_KEYS, 4, 10, 4);
  spinCtrl->SetFont(fuenteR);
  wxStaticText* textoSpin3 = new wxStaticText(
      panelPrincipal, wxID_ANY, "Casillas Verticales: ", wxDefaultPosition);
  textoSpin3->SetFont(fuenteR);
  wxSpinCtrl* spinCtrl2 =
      new wxSpinCtrl(panelPrincipal, wxID_ANY, wxEmptyString, wxDefaultPosition,
                     wxDefaultSize, wxSP_ARROW_KEYS, 4, 10, 4);
  spinCtrl2->SetFont(fuenteR);
  wxButton* botonIniciarJuego = new wxButton(
      panelPrincipal, wxID_ANY, "INICIAR", wxDefaultPosition, wxSize(400, 100));
  wxButton* botonRegresar = new wxButton(panelPrincipal, wxID_ANY, "Regresar",
                                         wxDefaultPosition, wxSize(400, 100));

  botonIniciarJuego->SetFont(fuente);
  botonRegresar->SetFont(fuente);

  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(botonIniciarJuego, 0, wxALL | wxEXPAND, 10);
  panelHorizontal->Add(botonRegresar, 0, wxALL | wxEXPAND, 10);
  panelHorizontal->AddStretchSpacer();

  panelVertical->Add(staticText, 0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();
  panelVertical->Add(radioBox1, 0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();
  panelVertical->Add(radioBox2, 0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();
  panelVertical->Add(textoSpin, 0, wxALL | wxEXPAND, 10);
  panelVertical->Add(textoSpin2, 0, wxALL | wxEXPAND, 10);
  panelVertical->Add(spinCtrl, 0, wxALL | wxEXPAND, 10);
  panelVertical->Add(textoSpin3, 0, wxALL | wxEXPAND, 10);
  panelVertical->Add(spinCtrl2, 0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();
  panelVertical->Add(panelHorizontal, 0, wxALL | wxEXPAND, 10);

  panelPrincipal->SetSizer(panelVertical);

  radioBox1->Bind(wxEVT_RADIOBOX, &ConfNuevoJuego::jugadorUno, this);
  radioBox2->Bind(wxEVT_RADIOBOX, &ConfNuevoJuego::jugadorDos, this);
  spinCtrl->Bind(wxEVT_SPINCTRL, &ConfNuevoJuego::filasTablero, this);
  spinCtrl2->Bind(wxEVT_SPINCTRL, &ConfNuevoJuego::columnasTablero, this);
  botonIniciarJuego->Bind(wxEVT_BUTTON, &ConfNuevoJuego::botonIniciar, this);
  botonRegresar->Bind(wxEVT_BUTTON, &ConfNuevoJuego::botonRegresar, this);
 

  Maximize(true);
}

// manejo de eventos

void ConfNuevoJuego::jugadorUno(wxCommandEvent& event) {
  // obtener puntero al radiobox
  wxRadioBox* radioBox1 = dynamic_cast<wxRadioBox*>(event.GetEventObject());

  // si no fuera un objeto wxRadioBox nos devulve un nullptr

  if (radioBox1) {
    // como sabemos que sí es un puntero no nulo a un wxRadioBox podemos usar
    // métodos de este
    tipoJugadorUno = radioBox1->GetSelection();
  }
}
void ConfNuevoJuego::jugadorDos(wxCommandEvent& event) {
  // obtener puntero al radiobox
  wxRadioBox* radioBox2 = dynamic_cast<wxRadioBox*>(event.GetEventObject());

  // si no fuera un objeto wxRadioBox nos devulve un nullptr

  if (radioBox2) {
    // como sabemos que sí es un puntero no nulo a un wxRadioBox podemos usar
    // métodos de este
    tipoJugadorDos = radioBox2->GetSelection();
  }
}

void ConfNuevoJuego::filasTablero(wxCommandEvent& event) {
  // obtener puntero al SpinCtrl
  wxSpinCtrl* spinCtrl = dynamic_cast<wxSpinCtrl*>(event.GetEventObject());

  // si no fuera un objeto wxSpinCtrl nos devulve un nullptr
  if (spinCtrl) {
    numFilasTablero = spinCtrl->GetValue();
  }
}

void ConfNuevoJuego::columnasTablero(wxCommandEvent& event) {
  // obtener puntero al SpinCtrl
  wxSpinCtrl* spinCtrl2 = dynamic_cast<wxSpinCtrl*>(event.GetEventObject());

  // si no fuera un objeto wxSpinCtrl nos devulve un nullptr
  if (spinCtrl2) {
    numColumnasTablero = spinCtrl2->GetValue();
  }
}
void ConfNuevoJuego::botonRegresar(wxCommandEvent& event) { Close(true); }

void ConfNuevoJuego::botonIniciar(wxCommandEvent& event) {
  auto estado= make_unique<EstadoJuego>(numFilasTablero,numColumnasTablero,tipoJugadorUno, tipoJugadorDos);
  VistaJuego* juego =
      new VistaJuego(this,"4 en linea", move(estado));
  juego->Show(true);
  this->Hide();
}
