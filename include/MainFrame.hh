#ifndef MAINFRAME_HH
#define MAINFRAME_HH

#include <wx/wx.h>

class MainFrame:public wxFrame
{
public:
    //Constructor toma el nombre de la ventana como parametro
    MainFrame(const wxString& title);

private:
    void OnBottonClicked(wxCommandEvent & evt);
    wxDECLARE_EVENT_TABLE();
};

#endif 