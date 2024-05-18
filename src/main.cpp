#include <iostream>
#include <App.hh>
#include <mainFrame.hh>
#include <wx/wx.h>

wxIMPLEMENT_APP_NO_MAIN(App);

int main() {
    std::cout << "Hola" << std::endl;
    wxEntry();
    return 0;
}