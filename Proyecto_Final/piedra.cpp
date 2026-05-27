#include "piedra.h"
#include <cmath>

Piedra::Piedra() : Entidad()
{
    masa = 1.0f;
    coefRoce = 0.05f;
    enMovimiento = false;
}

Piedra::~Piedra()
{
}

void Piedra::actualizar(float dt)
{
    // Movimiento basico: pos = pos + vel*dt
    Vector2D nueva = pos.sumar(vel.escalar(dt));
    setPosicion(nueva);

    // Frenado simple para detectar cuando se detiene.
    // La fisica real se aplicara con la clase Fisica mas adelante.
    if (vel.magnitud() < 0.1f)
    {
        vel = Vector2D(0, 0);
        enMovimiento = false;
    }
}

void Piedra::aplicarFuerza(float fuerza, float angulo)
{
    // a = F / m
    float ax = (fuerza / masa) * cos(angulo);
    float ay = (fuerza / masa) * sin(angulo);
    vel = vel.sumar(Vector2D(ax, ay));
    enMovimiento = true;
}

bool Piedra::detenida()
{
    return !enMovimiento;
}

float Piedra::getMasa()
{
    return masa;
}

float Piedra::getCoefRoce()
{
    return coefRoce;
}

void Piedra::setCoefRoce(float r)
{
    coefRoce = r;
}
