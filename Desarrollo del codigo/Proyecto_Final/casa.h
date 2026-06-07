#ifndef CASA_H
#define CASA_H

#include "vector2d.h"

#include <QGraphicsScene>

class PiedraCurling;

class Casa
{
public:
    Casa(Vector2D centroInicial = Vector2D(650, 255), int radioInicial = 80);

    void dibujar(QGraphicsScene *scene) const;
    int calcularPuntos(const PiedraCurling &piedra) const;
    bool contiene(const PiedraCurling &piedra) const;
    Vector2D centroCasa() const;
    void setCentro(Vector2D nuevoCentro);

private:
    Vector2D centro;
    int radio;
};

#endif
