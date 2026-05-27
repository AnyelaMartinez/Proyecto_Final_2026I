#include "ventanaprincipal.h"
#include <QLabel>

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Mundo de Chilly Willy");
    resize(800, 600);

    // Por ahora solo mostramos un letrero. Luego pondremos aqui el menu.
    QLabel *titulo = new QLabel("Mundo de Chilly Willy", this);
    titulo->setAlignment(Qt::AlignCenter);
    setCentralWidget(titulo);
}

VentanaPrincipal::~VentanaPrincipal()
{
}
