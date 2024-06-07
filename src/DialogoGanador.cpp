#include <DialogoGanador.hh>
#include <VistaJuego.hh>
#include <wx/msgdlg.h>

DialogoGanador::DialogoGanador(VistaJuego* ventanaVista,std::string nombreJugador):
    wxDialog(ventanaVista, wxID_ANY,"", wxDefaultPosition, wxSize(570, 280), wxDEFAULT_DIALOG_STYLE ),ventanaVista(ventanaVista),nombreJugador(nombreJugador){
    
    wxBoxSizer* vertical=new wxBoxSizer(wxVERTICAL);

    std::string mensajeGanador= "Jugador "+ nombreJugador + " ha GANADO!!" ;

    wxStaticText* textoVictoria= new wxStaticText(this,wxID_ANY,mensajeGanador);
    wxStaticText* pregunta= new wxStaticText(this,wxID_ANY,"Deseas continuar o salir",wxDefaultPosition);
    wxFont fuenteVictoria(wxFontInfo(20).Bold().FaceName("Georgia"));
    textoVictoria->SetFont(fuenteVictoria);

    wxBoxSizer* horizontal=new wxBoxSizer(wxHORIZONTAL);
    wxButton* continuar=new wxButton(this,wxID_ANY, "Continuar",wxDefaultPosition);
    wxButton* salir=new wxButton(this, wxID_ANY, "SALIR",wxDefaultPosition);
  
    horizontal->AddStretchSpacer();
    horizontal->Add(continuar,0,wxALL | wxEXPAND,10);
    horizontal->AddStretchSpacer();
    horizontal->Add(salir,0, wxALL | wxEXPAND,10);
    horizontal->AddStretchSpacer();

    vertical->Add(textoVictoria,0,wxALL | wxALIGN_CENTER_HORIZONTAL,10);
    vertical->Add(pregunta,0,wxALL | wxALIGN_CENTER_HORIZONTAL,10);
    vertical->AddStretchSpacer();
    vertical->Add(horizontal,0,wxALL| wxEXPAND,10 );

    this->SetSizer(vertical);
    this->Layout();
    //this->Fit();

    continuar->Bind(wxEVT_BUTTON,&DialogoGanador::continuar,this);
    salir->Bind(wxEVT_BUTTON,&DialogoGanador::salir,this);


}


 void DialogoGanador::continuar(wxCommandEvent& event){
    //aquí requerimos algo como VistaJuego->estadoActual->clearTablero();
    //¿Se le puede enviar desde aquí un refresh? 
 }

void DialogoGanador::salir(wxCommandEvent& event){
//verificamos que vista no sea un puntero nulo
if (ventanaVista) {
        ventanaVista->Close(true);
        //nos aseguramos que no siga existiendo el puntero a ventana vista 
        ventanaVista = nullptr;
    } 
    //cerramos el dialogo
    EndModal(wxID_CANCEL);
}