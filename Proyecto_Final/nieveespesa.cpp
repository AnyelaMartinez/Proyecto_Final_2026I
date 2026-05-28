#include "nieveespesa.h"

NieveEspesa::NieveEspesa(int x, int y, int ancho, int alto)
    : Zona(x, y, ancho, alto)
{
    friccion = 0.20f;
    factorFreno = 1.5f;
}

void NieveEspesa::aplicarEfecto(Piedra *p, float dt)
{
    p->setCoefRoce(friccion);
}
