#include "pescadodorado.h"

#include "chillywilly.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QPolygonF>
#include <QRadialGradient>
#include <QtMath>

PescadoDorado::PescadoDorado(int xInicial, int yInicial)
    : ObjetoBase(xInicial, yInicial, "pescado"),
      duracionBonus(8.0f),
      recolectado(false),
      tiempo(0.0f),
      baseY(yInicial),
      direccion(1)
{
}

void PescadoDorado::otorgarBonus(ChillyWilly &c)
{
    if (!recolectado) {
        c.recogerPescado();
        recolectado = true;
        setActivo(false);
    }
}

void PescadoDorado::reiniciar(int nuevaX, int nuevaY)
{
    recolectado = false;
    tiempo = 0.0f;
    baseY = nuevaY;
    direccion = 1;
    setPosicion(nuevaX, nuevaY);
    setActivo(true);
}

void PescadoDorado::actualizar(float dt)
{
    if (activo && !recolectado) {
        tiempo += dt;
        x += direccion;
        if (x < 310 || x > 470) {
            direccion *= -1;
        }
        y = baseY + static_cast<int>(std::sin(tiempo * 5.0f) * 10.0f);
    }
    ObjetoBase::actualizar(dt);
}

void PescadoDorado::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    scene->addEllipse(-23, 9, 46, 9, QPen(Qt::NoPen), QBrush(QColor(0, 0, 0, 45)));

    QRadialGradient oro(-7, -6, 32);
    oro.setColorAt(0.0, QColor(255, 245, 115));
    oro.setColorAt(0.55, QColor(255, 190, 35));
    oro.setColorAt(1.0, QColor(205, 120, 0));

    QGraphicsEllipseItem *pez = scene->addEllipse(-18, -10, 36, 20,
                                                  QPen(QColor(190, 130, 0), 2),
                                                  QBrush(oro));
    scene->addPolygon(QPolygonF() << QPointF(-18, 0) << QPointF(-34, -12) << QPointF(-34, 12),
                      QPen(QColor(190, 130, 0), 2), QBrush(QColor(255, 205, 45)))
        ->setParentItem(pez);
    scene->addEllipse(7, -4, 5, 5, QPen(Qt::black), QBrush(Qt::black))->setParentItem(pez);
    scene->addEllipse(9, -3, 1.5, 1.5, QPen(Qt::NoPen), QBrush(Qt::white))->setParentItem(pez);
    grafico = pez;
    grafico->setZValue(5);
    grafico->setPos(x, y);
}
