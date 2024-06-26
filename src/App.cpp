#include <wx/wx.h>

#include <App.hh>
#include <MainFrame.hh>

bool App::OnInit() {
  MainFrame* mainFrame = new MainFrame("Frame principal");
  // cambiar tamaño y que la ventana este centrada:
  mainFrame->SetClientSize(800, 600);
  mainFrame->CenterOnScreen();
  // por default el frame está oculto así que hay que llamar al método show
  mainFrame->Show();
  return true;
}

wxIMPLEMENT_APP(App);