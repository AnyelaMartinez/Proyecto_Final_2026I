#ifndef CHILLYWILLY_H
#define CHILLYWILLY_H

#include "personaje.h"

#include <QPixmap>

class PiedraCurling;

class ChillyWilly : public Personaje
{
public:
    ChillyWilly(int xInicial = 80, int yInicial = 335);

    void barrer();
    void dejarDeBarrer();
    void lanzar(PiedraCurling &piedra, float fuerza, float angulo);
    void recogerPescado();
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;
    bool estaBarriendo() const;
    bool tieneBonus() const;

private:
    bool barriendo;
    bool bonusActivo;
    float tiempoBonus;
    float inestabilidad;
    QPixmap spriteSheet;
    int frameActual;
    float tiempoAnim;
    int ultimaX;
    int ultimaY;
    float tiempoLanzando;
};

#endif
