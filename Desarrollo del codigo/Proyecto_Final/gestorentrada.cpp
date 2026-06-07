#include "gestorentrada.h"

#include <Qt>

void GestorEntrada::presionar(int tecla)
{
    teclas.insert(tecla);
}

void GestorEntrada::soltar(int tecla)
{
    teclas.remove(tecla);
}

bool GestorEntrada::teclaPresionada(int tecla) const
{
    return teclas.contains(tecla);
}

bool GestorEntrada::flechaArriba() const
{
    return teclaPresionada(Qt::Key_Up);
}

bool GestorEntrada::flechaAbajo() const
{
    return teclaPresionada(Qt::Key_Down);
}

bool GestorEntrada::flechaIzquierda() const
{
    return teclaPresionada(Qt::Key_Left);
}

bool GestorEntrada::flechaDerecha() const
{
    return teclaPresionada(Qt::Key_Right);
}

bool GestorEntrada::espacio() const
{
    return teclaPresionada(Qt::Key_Space);
}

char GestorEntrada::leerTecla() const
{
    if (espacio()) {
        return ' ';
    }
    if (flechaArriba()) {
        return 'U';
    }
    if (flechaAbajo()) {
        return 'D';
    }
    if (flechaIzquierda()) {
        return 'L';
    }
    if (flechaDerecha()) {
        return 'R';
    }
    return '\0';
}
