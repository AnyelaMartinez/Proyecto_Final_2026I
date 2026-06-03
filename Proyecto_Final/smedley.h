#ifndef SMEDLEY_H
#define SMEDLEY_H

#include "personaje.h"
#include "fisica.h"

class PiedraCurling;

class Smedley : public Personaje
{
public:
    Smedley(int xInicial = 420, int yInicial = 120);

    void interferir(PiedraCurling &piedra);
    void actualizarRuta();
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;

private:
    int patron;
    float velocidadPatrulla;
    int direccion;
    FisicaColisionElastica colision;
};

#endif
