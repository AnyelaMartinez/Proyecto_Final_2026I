#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QGraphicsPixmapItem>
#include "vector2d.h"

class Entidad : public QGraphicsPixmapItem
{
public:
    Entidad();
    virtual ~Entidad();

    virtual void actualizar(float dt) = 0;

    Vector2D getPosicion();
    void setPosicion(Vector2D p);
    Vector2D getVelocidad();
    void setVelocidad(Vector2D v);

protected:
    Vector2D pos;
    Vector2D vel;
};

#endif // ENTIDAD_H
