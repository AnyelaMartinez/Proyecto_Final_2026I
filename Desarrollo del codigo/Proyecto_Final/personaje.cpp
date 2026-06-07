#include "personaje.h"

Personaje::Personaje(int xInicial, int yInicial, const QString &spriteInicial)
    : ObjetoBase(xInicial, yInicial, spriteInicial), velocidad(120.0f), agilidad(1.0f)
{
}

void Personaje::mover(int dx, int dy)
{
    float factor = (velocidad / 100.0f) * agilidad;
    int nuevoX = x + static_cast<int>(dx * factor);
    int nuevoY = y + static_cast<int>(dy * factor);
    setPosicion(nuevoX, nuevoY);
}

float Personaje::getVelocidad() const
{
    return velocidad;
}

float Personaje::getAgilidad() const
{
    return agilidad;
}
