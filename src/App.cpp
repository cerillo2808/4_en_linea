#include <App.hh>
#include <mainFrame.hh>
#include <wx/wx.h>

wxIMPLEMENT_App(App);

bool App::OnInit(){
    MainFrame* mainFrame=new MainFrame ("C++ GUI");
    //cambiar tamaño y que la ventana este centrada:
    mainFrame->SetClientsSize (800,600);
    mainFrame->Show();
    //por default el frame está ocukto así que hay que llamar al método show
    mainFrame->Show();
    return true;
}

