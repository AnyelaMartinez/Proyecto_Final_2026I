#include "objetobase.h"

ObjetoBase::ObjetoBase(int xInicial, int yInicial, const QString &spriteInicial)
    : x(xInicial), y(yInicial), sprite(spriteInicial), activo(true), grafico(nullptr)
{
}

ObjetoBase::~ObjetoBase()
{
}

void ObjetoBase::actualizar(float)
{
    if (grafico) {
        grafico->setPos(x, y);
        grafico->setVisible(activo);
    }
}

int ObjetoBase::getX() const
{
    return x;
}

int ObjetoBase::getY() const
{
    return y;
}

bool ObjetoBase::estaActivo() const
{
    return activo;
}

void ObjetoBase::setActivo(bool valor)
{
    activo = valor;
    if (grafico) {
        grafico->setVisible(valor);
    }
}

void ObjetoBase::setPosicion(int nuevaX, int nuevaY)
{
    x = nuevaX;
    y = nuevaY;
    if (grafico) {
        grafico->setPos(x, y);
    }
}

void ObjetoBase::limpiarGrafico()
{
    grafico = nullptr;
}
