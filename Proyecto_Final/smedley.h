#ifndef SMEDLEY_H
#define SMEDLEY_H

#include "personaje.h"
#include "fisica.h"

#include <QPixmap>

class PiedraCurling;

class Smedley : public Personaje
{
public:
    Smedley(int xInicial = 420, int yInicial = 120);

    void interferir(PiedraCurling &piedra);
    void actualizarRuta();
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;
    void setPatronVertical(bool v);

private:
    float velocidadPatrulla;
    int direccion;
    bool patronVertical;
    bool enLane;
    float tiempoEstado;
    float cooldownColision;
    FisicaColisionElastica colision;
    QPixmap spriteSheet;
    int frameActual;
    float tiempoAnim;
};

#endif
