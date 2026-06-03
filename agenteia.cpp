#include "agenteia.h"

#include "casa.h"
#include "piedracurling.h"

#include <QRandomGenerator>
#include <QtMath>

AgenteIA::AgenteIA()
    : margenError(14.0f), nivelDificultad(1)
{
}

void AgenteIA::percibir(int nivelActual)
{
    nivelDificultad = nivelActual;
}

void AgenteIA::analizar()
{
    margenError = qMax(4.0f, 16.0f - nivelDificultad * 3.0f);
}

void AgenteIA::actuar(PiedraCurling &piedra, const Casa &casa)
{
    const Vector2D objetivo = casa.centroCasa();
    const float dx = objetivo.x - piedra.getX();
    const float dy = piedra.getY() - objetivo.y;
    const float anguloBase = qRadiansToDegrees(std::atan2(dy, dx));
    const float ruido = static_cast<float>((QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * margenError);
    piedra.aplicarFuerza(300.0f, anguloBase + ruido);
}

void AgenteIA::ajustarDificultad(bool fallo)
{
    if (fallo) {
        margenError += 2.0f;
    } else {
        margenError = qMax(3.0f, margenError - 1.0f);
    }
}
