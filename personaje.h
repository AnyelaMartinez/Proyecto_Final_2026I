#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "objetobase.h"

class Personaje : public ObjetoBase
{
public:
    Personaje(int xInicial, int yInicial, const QString &spriteInicial);
    void mover(int dx, int dy);
    float getVelocidad() const;
    float getAgilidad() const;

protected:
    float velocidad;
    float agilidad;
};

#endif
