#include <App.hh>
#include <MainFrame.hh>
#include <wx/wx.h>


bool App::OnInit(){
    MainFrame* mainFrame=new MainFrame ("C++ GUI");
    //cambiar tamaño y que la ventana este centrada:
    mainFrame->SetClientSize (800,600);
    mainFrame->Show();
    //por default el frame está ocukto así que hay que llamar al método show
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(App);
