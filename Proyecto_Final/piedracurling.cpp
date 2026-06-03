#include "piedracurling.h"

#include "casa.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QPixmap>
#include <QRadialGradient>
#include <QtMath>

PiedraCurling::PiedraCurling(int xInicial, int yInicial)
    : ObjetoBase(xInicial, yInicial, "piedra"),
      vel(0, 0),
      friccion(0.48f),
      enMovimiento(false),
      masa(18.0f)
{
}

void PiedraCurling::aplicarFuerza(float fuerza, float angulo)
{
    const float rad = qDegreesToRadians(angulo);
    vel = Vector2D(std::cos(rad) * fuerza, -std::sin(rad) * fuerza);
    enMovimiento = true;
}

void PiedraCurling::actualizarFisica(float dt)
{
    if (!enMovimiento) {
        return;
    }

    x += static_cast<int>(vel.x * dt);
    y += static_cast<int>(vel.y * dt);

    const float factor = qMax(0.0f, 1.0f - friccion * dt);
    vel = vel.multiplicar(factor);

    if (vel.magnitud() < 6.0f) {
        vel = Vector2D(0, 0);
        enMovimiento = false;
    }
}

void PiedraCurling::actualizar(float dt)
{
    actualizarFisica(dt);
    ObjetoBase::actualizar(dt);
}

void PiedraCurling::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    QGraphicsPixmapItem *piedra = scene->addPixmap(QPixmap(":/sprites/piedra.png"));
    piedra->setOffset(-48, -48);
    grafico = piedra;
    grafico->setZValue(5);
    grafico->setPos(x, y);
}

bool PiedraCurling::detenido() const
{
    return !enMovimiento;
}

float PiedraCurling::distanciaA(const Casa &casa) const
{
    return posicionVector().distancia(casa.centroCasa());
}

void PiedraCurling::reiniciar(int nuevaX, int nuevaY)
{
    vel = Vector2D(0, 0);
    enMovimiento = false;
    setPosicion(nuevaX, nuevaY);
}

void PiedraCurling::setFriccion(float nuevaFriccion)
{
    friccion = nuevaFriccion;
}

void PiedraCurling::aplicarEmpuje(float dx, float dy)
{
    vel = vel.sumar(Vector2D(dx, dy));
    if (vel.magnitud() > 0.0f) {
        enMovimiento = true;
    }
}

Vector2D PiedraCurling::posicionVector() const
{
    return Vector2D(static_cast<float>(x), static_cast<float>(y));
}

Vector2D PiedraCurling::getVelocidad() const
{
    return vel;
}

void PiedraCurling::setVelocidad(const Vector2D &nuevaVelocidad)
{
    vel = nuevaVelocidad;
    enMovimiento = vel.magnitud() > 0.1f;
}

float PiedraCurling::getMasa() const
{
    return masa;
}
