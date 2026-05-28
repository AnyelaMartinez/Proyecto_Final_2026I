#include "hieloresbaladizo.h"

HieloResbaladizo::HieloResbaladizo(int x, int y, int ancho, int alto)
    : Zona(x, y, ancho, alto)
{
    friccion = 0.01f;
    factorInercia = 0.95f;
}

void HieloResbaladizo::aplicarEfecto(Piedra *p, float dt)
{
    p->setCoefRoce(friccion);
}
