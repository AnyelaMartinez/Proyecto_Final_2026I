#include "casa.h"

#include "piedracurling.h"

#include <QBrush>
#include <QPen>

Casa::Casa(Vector2D centroInicial, int radioInicial)
    : centro(centroInicial), radio(radioInicial)
{
}

void Casa::dibujar(QGraphicsScene *scene) const
{
    scene->addEllipse(centro.x - radio, centro.y - radio, radio * 2, radio * 2,
                      QPen(Qt::darkBlue, 4), QBrush(QColor(220, 242, 255)));
    scene->addEllipse(centro.x - radio * 0.65f, centro.y - radio * 0.65f,
                      radio * 1.3f, radio * 1.3f, QPen(Qt::red, 4), Qt::NoBrush);
    scene->addEllipse(centro.x - radio * 0.32f, centro.y - radio * 0.32f,
                      radio * 0.64f, radio * 0.64f, QPen(Qt::darkBlue, 4), Qt::NoBrush);
    scene->addEllipse(centro.x - 6, centro.y - 6, 12, 12, QPen(Qt::black), QBrush(Qt::red));
}

int Casa::calcularPuntos(const PiedraCurling &piedra) const
{
    const float d = piedra.distanciaA(*this);
    if (d <= radio * 0.32f) {
        return 10;
    }
    if (d <= radio * 0.65f) {
        return 6;
    }
    if (d <= radio) {
        return 3;
    }
    return 0;
}

bool Casa::contiene(const PiedraCurling &piedra) const
{
    return piedra.distanciaA(*this) <= radio;
}

Vector2D Casa::centroCasa() const
{
    return centro;
}

void Casa::setCentro(Vector2D nuevoCentro)
{
    centro = nuevoCentro;
}
