#ifndef DIALOGOEMPATE_HH
#define DIALOGOEMPATE_HH
#include <wx/msgdlg.h>
#include <VistaJuego.hh>

class DialogoEmpate:public wxDialog{
    public:
    //Constructor
    DialogoEmpate(VistaJuego* ventanaVista);
    void continuar(wxCommandEvent& event);
    void salir(wxCommandEvent& event);
    VistaJuego* ventanaVista;
};


#endif