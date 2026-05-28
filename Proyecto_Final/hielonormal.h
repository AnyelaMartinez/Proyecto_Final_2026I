#ifndef HIELONORMAL_H
#define HIELONORMAL_H

#include "zona.h"

class HieloNormal : public Zona
{
public:
    HieloNormal(int x, int y, int ancho, int alto);
    void aplicarEfecto(Piedra *p, float dt);
};

#endif // HIELONORMAL_H
