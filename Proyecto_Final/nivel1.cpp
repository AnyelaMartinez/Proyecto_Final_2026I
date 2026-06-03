#include "nivel1.h"

#include "piedracurling.h"

Nivel1::Nivel1()
    : lanzamientosRestantes(3), turnoJugador(true), casa(Vector2D(650, 255), 80)
{
}

void Nivel1::inicializar()
{
    lanzamientosRestantes = 3;
    turnoJugador = true;
}

void Nivel1::actualizar(float dt)
{
    tiempoTranscurrido += dt;
}

void Nivel1::dibujar(QGraphicsScene *scene)
{
    pista.dibujar(scene);
    casa.dibujar(scene);
}

void Nivel1::procesarTecla(int)
{
}

bool Nivel1::terminado() const
{
    return lanzamientosRestantes <= 0;
}

void Nivel1::lanzarPiedra(float fuerza, float angulo, PiedraCurling &piedra)
{
    if (lanzamientosRestantes > 0) {
        piedra.aplicarFuerza(fuerza, angulo);
        --lanzamientosRestantes;
    }
}

int Nivel1::calcularPuntuacion(const PiedraCurling &piedra) const
{
    return casa.calcularPuntos(piedra);
}

void Nivel1::cambiarTurno()
{
    turnoJugador = !turnoJugador;
}

Personaje *Nivel1::turnoActual()
{
    return nullptr;
}

int Nivel1::getLanzamientosRestantes() const
{
    return lanzamientosRestantes;
}

Casa &Nivel1::getCasa()
{
    return casa;
}
