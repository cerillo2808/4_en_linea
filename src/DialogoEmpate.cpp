#include <DialogoEmpate.hh>
#include <VistaJuego.hh>
#include <wx/msgdlg.h>

DialogoEmpate::DialogoEmpate(VistaJuego* ventanaVista):
    wxDialog(ventanaVista, wxID_ANY,"", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE ),ventanaVista(ventanaVista){
        wxBoxSizer* vertical=new wxBoxSizer(wxVERTICAL);

    wxStaticText* empateGrande= new wxStaticText(this,wxID_ANY,"EMPATE!");
    wxStaticText* empatePregunta= new wxStaticText(this,wxID_ANY,"Ha sucedido un empate, Deseas continuar o salir?",wxDefaultPosition);
    wxFont fuenteEmpate(wxFontInfo(15).Bold().FaceName("Georgia"));
    empateGrande->SetFont(fuenteEmpate);

    wxBoxSizer* horizontal=new wxBoxSizer(wxHORIZONTAL);
    wxButton* continuar=new wxButton(this,wxID_ANY, "Continuar",wxDefaultPosition);
    wxButton* salir=new wxButton(this, wxID_ANY, "SALIR",wxDefaultPosition);
  
    horizontal->AddStretchSpacer();
    horizontal->Add(continuar,0,wxALL | wxEXPAND,10);
    horizontal->AddStretchSpacer();
    horizontal->Add(salir,0, wxALL | wxEXPAND,10);
    horizontal->AddStretchSpacer();

    vertical->Add(empateGrande,0,wxALL | wxALIGN_CENTER_HORIZONTAL,10);
    vertical->Add(empatePregunta,0,wxALL | wxALIGN_CENTER_HORIZONTAL,10);
    vertical->AddStretchSpacer();
    vertical->Add(horizontal,0,wxALL| wxEXPAND,10 );

    this->SetSizer(vertical);
    this->Fit();

    continuar->Bind(wxEVT_BUTTON,&DialogoEmpate::continuar,this);
    salir->Bind(wxEVT_BUTTON,&DialogoEmpate::salir,this);


}


 void DialogoEmpate::continuar(wxCommandEvent& event){
    //aquí requerimos algo como VistaJuego->estadoActual->clearTablero();
    //¿Se le puede enviar desde aquí un refresh? 
 }

void DialogoEmpate::salir(wxCommandEvent& event){
//verificamos que vista no sea un puntero nulo
if (ventanaVista) {
        ventanaVista->Close(true);
        //nos aseguramos que no siga existiendo el puntero a ventana vista 
        ventanaVista = nullptr;
    } 
    //cerramos el dialogo
    EndModal(wxID_CANCEL);
}