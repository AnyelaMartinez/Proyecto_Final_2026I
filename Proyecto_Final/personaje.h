#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "entidad.h"

class Personaje : public Entidad
{
public:
    Personaje();
    virtual ~Personaje();

    virtual void mover(int dx, int dy) = 0;

protected:
    float velocidad;
    float agilidad;
};

#endif // PERSONAJE_H
