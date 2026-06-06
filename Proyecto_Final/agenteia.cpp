#include "agenteia.h"

#include "casa.h"
#include "piedracurling.h"

#include <QRandomGenerator>
#include <QVector>
#include <QtMath>

AgenteIA::AgenteIA()
    : margenError(5.0f), nivelDificultad(1), sesgoAngulo(0.0f), sesgoFuerza(0.0f), ultimaDecision{0.0f, 0.0f}
{
}

void AgenteIA::percibir(int nivelActual)
{
    nivelDificultad = nivelActual;
}

void AgenteIA::analizar()
{
    // No reseteamos margenError aqui, se ajusta solo en ajustarDificultad
    margenError = qBound(2.0f, margenError, 12.0f);
}

Percepcion AgenteIA::percibirEstado(const PiedraCurling &piedra, const Casa &casa)
{
    const Vector2D objetivo = casa.centroCasa();
    return Percepcion{static_cast<float>(piedra.getX()),
                      static_cast<float>(piedra.getY()),
                      objetivo.x,
                      objetivo.y};
}

Decision AgenteIA::razonar(const Percepcion &percepcion)
{
    const float dx = percepcion.objetivoX - percepcion.piedraX;
    const float dy = percepcion.piedraY - percepcion.objetivoY;
    const float anguloBase = qRadiansToDegrees(std::atan2(dy, dx));
    const float distancia = std::sqrt(dx * dx + dy * dy);
    // Multiplicador calibrado para la friccion del hielo normal (~0.48)
    const float fuerza = distancia * 0.50f + sesgoFuerza;
    return Decision{fuerza, anguloBase + sesgoAngulo};
}

void AgenteIA::actuar(PiedraCurling &piedra, const Casa &casa)
{
    const Percepcion percepcion = percibirEstado(piedra, casa);
    const Decision decision = razonar(percepcion);
    const float ruido = static_cast<float>((QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * margenError);
    ultimaDecision = decision;
    piedra.aplicarFuerza(decision.fuerza, decision.angulo + ruido);
}

void AgenteIA::setMargenError(float m)
{
    margenError = m;
    sesgoFuerza = 0.0f;
    sesgoAngulo = 0.0f;
    historial.clear();
}

void AgenteIA::ajustarDificultad(bool fallo)
{
    if (fallo) {
        margenError += 2.0f;
    } else {
        margenError = qMax(3.0f, margenError - 1.0f);
    }
}

void AgenteIA::registrarResultado(float distanciaFinal, float xFinal, float xObjetivo)
{
    historial.push_back(Lanzamiento{ultimaDecision.fuerza, ultimaDecision.angulo, distanciaFinal, xFinal});
    calcularCorreccion(xObjetivo);
}

void AgenteIA::calcularCorreccion(float xObjetivo)
{
    if (historial.isEmpty()) {
        return;
    }

    const Lanzamiento ultimo = historial.last();
    // Error proporcional: positivo = se paso a la derecha, negativo = se quedo corto
    float error = ultimo.xFinal - xObjetivo;
    if (qAbs(error) > 30.0f) {
        // Ajuste proporcional al error
        sesgoFuerza -= error * 0.20f;
        sesgoAngulo *= 0.95f;
    } else {
        // Quedo cerca: refinar
        sesgoFuerza *= 0.9f;
        margenError = qMax(2.0f, margenError - 0.5f);
    }
    sesgoFuerza = qBound(-200.0f, sesgoFuerza, 200.0f);
}
