#include "hielonormal.h"

HieloNormal::HieloNormal(int x, int y, int ancho, int alto)
    : Zona(x, y, ancho, alto)
{
    friccion = 0.05f;
}

void HieloNormal::aplicarEfecto(Piedra *p, float dt)
{
    p->setCoefRoce(friccion);
}
