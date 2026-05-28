#include "zonamagica.h"
#include <cmath>

ZonaMagica::ZonaMagica(int x, int y, int ancho, int alto)
    : Zona(x, y, ancho, alto)
{
    friccion = 0.03f;
    amplitud = 50.0f;
    frecuencia = 2.0f;
    tiempo = 0.0f;
}

void ZonaMagica::aplicarEfecto(Piedra *p, float dt)
{
    p->setCoefRoce(friccion);

    // Perturbacion oscilatoria simple. Luego se reemplaza por la clase Fisica.
    tiempo = tiempo + dt;
    float empuje = amplitud * sin(frecuencia * tiempo);
    Vector2D v = p->getVelocidad();
    v.y = v.y + empuje * dt;
    p->setVelocidad(v);
}
