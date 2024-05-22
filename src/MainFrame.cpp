#include <MainFrame.hh>
#include <wx/wx.h>


MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxRESIZE_BORDER | wxMAXIMIZE_BOX | wxMINIMIZE_BOX)
{   
    wxPanel panelPrincipal= new wxPanel(this,wxID_ANY);
    
    //que inicialmente este maximizado
    Maximize(true);
}

