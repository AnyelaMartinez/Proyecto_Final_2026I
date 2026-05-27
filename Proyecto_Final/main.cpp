#include <QApplication>
#include "ventanaprincipal.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    VentanaPrincipal w;
    w.show();
    return app.exec();
}
