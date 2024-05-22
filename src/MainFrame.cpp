#include <MainFrame.hh>
#include <wx/wx.h>
#include<wx/spinctrl.h>

MainFrame::MainFrame (const wxString&title):wxFrame(nullptr,wxID_ANY,title){
    //Panel: donde metemos el resto
    wxPanel* panel=new wxPanel(this);

}