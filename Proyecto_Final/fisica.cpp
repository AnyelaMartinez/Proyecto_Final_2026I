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
    tiempo += dt;
    const float desplazamiento = A * qSin(omega * tiempo + phi) * dt;
    piedra.aplicarEmpuje(0.0f, desplazamiento);
}
