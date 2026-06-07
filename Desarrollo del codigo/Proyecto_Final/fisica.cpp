#include "fisica.h"

#include "piedracurling.h"

#include <QtMath>

Fisica::~Fisica()
{
}

FisicaFriccion::FisicaFriccion(float coeficiente)
    : mu(coeficiente)
{
}

void FisicaFriccion::aplicar(PiedraCurling &piedra, float dt)
{
    piedra.setFriccion(mu);
    Q_UNUSED(dt);
}

float FisicaFriccion::getCoeficiente() const
{
    return mu;
}

FisicaColisionElastica::FisicaColisionElastica(float restitucion)
    : e(restitucion)
{
}

void FisicaColisionElastica::aplicar(PiedraCurling &piedra, float dt)
{
    Q_UNUSED(piedra);
    Q_UNUSED(dt);
}

void FisicaColisionElastica::aplicarContra(PiedraCurling &piedra, float normalX, float normalY) const
{
    const Vector2D vel = piedra.getVelocidad();
    const float magnitudNormal = qSqrt(normalX * normalX + normalY * normalY);
    if (magnitudNormal <= 0.001f) {
        return;
    }

    const float nx = normalX / magnitudNormal;
    const float ny = normalY / magnitudNormal;
    const float producto = vel.x * nx + vel.y * ny;
    const Vector2D nuevaVelocidad(vel.x - (1.0f + e) * producto * nx,
                                  vel.y - (1.0f + e) * producto * ny);
    piedra.setVelocidad(nuevaVelocidad);
}

FisicaPerturbacion::FisicaPerturbacion(float amplitud, float frecuencia, float fase)
    : A(amplitud), omega(frecuencia), phi(fase), tiempo(0.0f)
{
}

void FisicaPerturbacion::aplicar(PiedraCurling &piedra, float dt)
{
    // En vez de oscilar y, aplica una fuerza perpendicular a la velocidad
    // -> la piedra curva su trayectoria (efecto curling).
    tiempo += dt;
    const Vector2D vel = piedra.getVelocidad();
    const float speed = qSqrt(vel.x * vel.x + vel.y * vel.y);
    if (speed < 1.0f) {
        return;
    }
    const float perpX = -vel.y / speed;
    const float perpY = vel.x / speed;
    // Direccion alterna con el sin para que la curva sea visible pero no caotica
    const float dir = qSin(omega * tiempo + phi) >= 0.0f ? 1.0f : -1.0f;
    const float fuerzaCurl = A * dt * dir;
    piedra.aplicarEmpuje(perpX * fuerzaCurl, perpY * fuerzaCurl);
}
