#ifndef ZONA_H
#define ZONA_H

#include "piedra.h"

class Zona
{
public:
    Zona(int x, int y, int ancho, int alto);
    virtual ~Zona();

    bool contiene(int px, int py);
    virtual void aplicarEfecto(Piedra *p, float dt) = 0;

protected:
    int x;
    int y;
    int ancho;
    int alto;
    float friccion;
};

#endif // ZONA_H
