#include <MainFrame.hh>
#include <wx/wx.h>

enum IDs {
    BUTTON_ID = 2
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(BUTTON_ID, MainFrame::OnBottonClicked)
wxEND_EVENT_TABLE()

MainFrame::MainFrame (const wxString&title):wxFrame(nullptr,wxID_ANY,title){

    wxPanel* panel=new wxPanel(this);
    wxButton* button=new wxButton(panel, BUTTON_ID,"Buttom lol",wxPoint(150,50),wxSize(120,35));

    CreateStatusBar();

}

void MainFrame::OnBottonClicked(wxCommandEvent & evt){
    wxLogStatus("Se presiono el boton");
}