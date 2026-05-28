#ifndef ZONAMAGICA_H
#define ZONAMAGICA_H

#include "zona.h"

class ZonaMagica : public Zona
{
public:
    ZonaMagica(int x, int y, int ancho, int alto);
    void aplicarEfecto(Piedra *p, float dt);

private:
    float amplitud;
    float frecuencia;
    float tiempo;
};

#endif // ZONAMAGICA_H
