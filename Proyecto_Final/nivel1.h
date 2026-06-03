#ifndef NIVEL1_H
#define NIVEL1_H

#include "casa.h"
#include "nivel.h"

class Personaje;
class PiedraCurling;

class Nivel1 : public Nivel
{
public:
    Nivel1();

    void inicializar() override;
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;
    void procesarTecla(int tecla) override;
    bool terminado() const override;

    void lanzarPiedra(float fuerza, float angulo, PiedraCurling &piedra);
    int calcularPuntuacion(const PiedraCurling &piedra) const;
    void cambiarTurno();
    Personaje *turnoActual();
    int getLanzamientosRestantes() const;
    Casa &getCasa();

private:
    int lanzamientosRestantes;
    bool turnoJugador;
    Casa casa;
};

#endif
