#include "entidad.h"

Entidad::Entidad() : QGraphicsPixmapItem()
{
}

Entidad::~Entidad()
{
}

Vector2D Entidad::getPosicion()
{
    return pos;
}

void Entidad::setPosicion(Vector2D p)
{
    pos = p;
    setPos(p.x, p.y);
}

Vector2D Entidad::getVelocidad()
{
    return vel;
}

void Entidad::setVelocidad(Vector2D v)
{
    vel = v;
}
