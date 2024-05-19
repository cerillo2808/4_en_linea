#include <MainFrame.hh>
#include <wx/wx.h>

MainFrame::MainFrame (const wxString&title):wxFrame(nullptr,wxID_ANY,title){

    wxPanel* panel=new wxPanel(this);
    wxButton* button=new wxButton(panel,wxID_ANY,"Buttom lol",wxPoint(150,50),wxSize(120,35));

}