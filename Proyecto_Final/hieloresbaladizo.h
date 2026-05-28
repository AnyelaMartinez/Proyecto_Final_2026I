#ifndef HIELORESBALADIZO_H
#define HIELORESBALADIZO_H

#include "zona.h"

class HieloResbaladizo : public Zona
{
public:
    HieloResbaladizo(int x, int y, int ancho, int alto);
    void aplicarEfecto(Piedra *p, float dt);

private:
    float factorInercia;
};

#endif // HIELORESBALADIZO_H
