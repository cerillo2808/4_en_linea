#include <wx/wx.h>

#include <ConfNuevoJuego.hh>
#include <MainFrame.hh>

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
              wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX |
                  wxMINIMIZE_BOX) {
  wxPanel* panelPrincipal = new wxPanel(this);
  panelPrincipal->SetBackgroundColour((wxColour("#07c3ed")));

  wxFont fuenteT(wxFontInfo(50).Bold().FaceName("Bangers"));

  wxStaticText* msjBienvenida =
      new wxStaticText(panelPrincipal, wxID_ANY,
                       "Bienvenid@s a 4 en Linea!", wxDefaultPosition);
  msjBienvenida->SetFont(fuenteT);

  // creando fuente para el texto de los botones
  wxFont fuenteBotones(wxFontInfo(30).Bold().FaceName("Arial"));

  
  wxBoxSizer* panelVertical = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* panelHorizontal = new wxBoxSizer(wxHORIZONTAL);

  // botones de las opciones
  wxButton* nuevoJuegoBoton =
      new wxButton(panelPrincipal, wxID_ANY, "NUEVO JUEGO", wxDefaultPosition,
                   wxSize(550, 120));
  wxButton* salirBoton = new wxButton(panelPrincipal, wxID_ANY, "SALIR",
                                      wxDefaultPosition, wxSize(550, 120));

  nuevoJuegoBoton->SetFont(fuenteBotones);
  salirBoton->SetFont(fuenteBotones);

  nuevoJuegoBoton->Bind(wxEVT_BUTTON, &MainFrame::nuevoJuego, this);
  salirBoton->Bind(wxEVT_BUTTON, &MainFrame::salir, this);
  
  panelVertical->AddStretchSpacer();
  panelVertical->Add(msjBienvenida,0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();
  panelVertical->Add(nuevoJuegoBoton, 0, wxALL | wxEXPAND, 10);
  panelVertical->Add(salirBoton, 0, wxALL | wxEXPAND, 10);
  panelVertical->AddStretchSpacer();

  // agregamos espacio al lado izquierdo
  panelHorizontal->AddStretchSpacer();
  panelHorizontal->Add(panelVertical, 0, wxALL | wxEXPAND, 10);
  // agregamos espacio al lado derecho
  panelHorizontal->AddStretchSpacer();

  panelPrincipal->SetSizer(panelHorizontal);

  // que inicialmente este maximizado
  Maximize(true);
}

void MainFrame::nuevoJuego(wxCommandEvent& event) {
  ConfNuevoJuego* ventanaConf =
      new ConfNuevoJuego(this,"Ventana de configuración para el nuevo juego");
  ventanaConf->Show();
}

void MainFrame::salir(wxCommandEvent& event) { Close(true); }

