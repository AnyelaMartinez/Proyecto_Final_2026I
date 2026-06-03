#include "personaje.h"

Personaje::Personaje(int xInicial, int yInicial, const QString &spriteInicial)
    : ObjetoBase(xInicial, yInicial, spriteInicial), velocidad(120.0f), agilidad(1.0f)
{
}

void Personaje::mover(int dx, int dy)
{
    setPosicion(x + dx, y + dy);
}

float Personaje::getVelocidad() const
{
    return velocidad;
}

float Personaje::getAgilidad() const
{
    return agilidad;
}
