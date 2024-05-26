#ifndef TABLEROGUI_HH
#define TABLEROGUI_HH

class TableroGUI : public wxFrame {
 public:
  // Constructor toma el nombre de la ventana como parametro así como las filas y columnas
  TableroGUI(const wxString& title,int filas, int columnas);

  //Manejar el evento de pintar el tablero
  void onPaint(wxPaintEvent& event);
  //Manejar los click del usuario en e tablero
  void onMouseClick(wxMouseEvent& event);

private:

    int numColumnas;
    int numFilas;

};

#endif