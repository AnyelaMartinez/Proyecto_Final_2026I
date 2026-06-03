#ifndef PIEDRACURLING_H
#define PIEDRACURLING_H

#include "objetobase.h"
#include "vector2d.h"

class Casa;

class PiedraCurling : public ObjetoBase
{
public:
    PiedraCurling(int xInicial = 90, int yInicial = 255);

    void aplicarFuerza(float fuerza, float angulo);
    void actualizarFisica(float dt);
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;
    bool detenido() const;
    float distanciaA(const Casa &casa) const;
    void reiniciar(int nuevaX = 90, int nuevaY = 255);
    void setFriccion(float nuevaFriccion);
    void aplicarEmpuje(float dx, float dy);
    Vector2D posicionVector() const;
    Vector2D getVelocidad() const;
    void setVelocidad(const Vector2D &nuevaVelocidad);
    float getMasa() const;

private:
    Vector2D vel;
    float friccion;
    bool enMovimiento;
    float masa;
};

#endif
