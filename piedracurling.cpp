#include "piedracurling.h"

#include "casa.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QRadialGradient>
#include <QtMath>

PiedraCurling::PiedraCurling(int xInicial, int yInicial)
    : ObjetoBase(xInicial, yInicial, "piedra"), vel(0, 0), friccion(0.48f), enMovimiento(false)
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

    scene->addEllipse(-22, 13, 44, 11, QPen(Qt::NoPen), QBrush(QColor(0, 0, 0, 60)));
    QRadialGradient grad(-8, -10, 35);
    grad.setColorAt(0.0, QColor(255, 255, 255));
    grad.setColorAt(0.55, QColor(205, 225, 245));
    grad.setColorAt(1.0, QColor(75, 105, 150));
    QGraphicsEllipseItem *piedra = scene->addEllipse(-18, -18, 36, 36,
                                                     QPen(QColor(25, 55, 105), 3),
                                                     QBrush(grad));
    scene->addEllipse(-8, -8, 16, 16, QPen(Qt::blue, 2), QBrush(QColor(150, 210, 255)))
        ->setParentItem(piedra);
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
