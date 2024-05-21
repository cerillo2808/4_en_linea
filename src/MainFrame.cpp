#include <MainFrame.hh>
#include <wx/wx.h>
#include<wx/spinctrl.h>

MainFrame::MainFrame (const wxString&title):wxFrame(nullptr,wxID_ANY,title){
    //Panel: donde metemos el resto
    wxPanel* panel=new wxPanel(this);
    
    //Botón
    wxButton* button=new wxButton(panel,wxID_ANY,"Buttom lol",wxPoint(150,50),wxSize(120,35));
    
    //CheckBox
    wxCheckBox* checkBox=new wxCheckBox(panel,wxID_ANY,"CheckBox",wxPoint(550,55));
   
    //Texto NO editable
    wxStaticText* staticText= new wxStaticText(panel,wxID_ANY,"StaticText- NOT editable", wxPoint(120,150));
    
    //Espacio para que escriba usuario
    wxTextCtrl* textCtrl= new wxTextCtrl(panel,wxID_ANY,"TextCtrl-editable",wxPoint(500,145),wxSize(200,-1)); //-1=default value
    
    //Punto que se mueve 
    wxSlider* slider= new wxSlider (panel,wxID_ANY,25,0,100,wxPoint(100,250),wxSize(200,-1));

    //
    wxGauge* gauge= new wxGauge(panel,wxID_ANY,100,wxPoint(500,255),wxSize(200,-1));//rectangulito vacío
    gauge->SetValue(50); //barrita medio llena

    //pestañita que se abre con opciones
    wxArrayString choices;
    choices.Add("Humano");
    choices.Add("IA Facil");
    choices.Add("IA Dificil");

    wxChoice* choice=new wxChoice(panel,wxID_ANY,wxPoint(150,375),wxSize(100,-1),choices);
    //si quieremos que tenga una opción por default
    choice->Select(0);

    //lista vertical de opciones
    wxListBox* listBox=new wxListBox(panel,wxID_ANY,wxPoint(100,475),wxSize(100,100),choices);

    //otra forma de opción
    wxRadioBox* radioBox= new wxRadioBox(panel,wxID_ANY, "Seleccione un Jugador",wxPoint(485,475),wxDefaultSize,choices);
}