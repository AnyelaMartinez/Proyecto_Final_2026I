#include "smedley.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QRadialGradient>

Smedley::Smedley(int xInicial, int yInicial)
    : Personaje(xInicial, yInicial, "smedley"), patron(1), velocidadPatrulla(95.0f), direccion(1)
{
}

void Smedley::interferir(PiedraCurling &piedra)
{
    const int dx = piedra.getX() - x;
    const int dy = piedra.getY() - y;
    if (dx * dx + dy * dy < 2600) {
        piedra.aplicarEmpuje(45.0f, direccion * 35.0f);
    }
}

void Smedley::actualizarRuta()
{
    if (y < 80 || y > 390) {
        direccion *= -1;
    }
}

void Smedley::actualizar(float dt)
{
    y += static_cast<int>(direccion * velocidadPatrulla * dt);
    actualizarRuta();
    ObjetoBase::actualizar(dt);
}

void Smedley::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    scene->addEllipse(-24, 19, 48, 13, QPen(Qt::NoPen), QBrush(QColor(0, 0, 0, 55)));

    QRadialGradient rojo(-8, -12, 42);
    rojo.setColorAt(0.0, QColor(255, 145, 125));
    rojo.setColorAt(0.55, QColor(205, 70, 60));
    rojo.setColorAt(1.0, QColor(120, 25, 30));

    QGraphicsEllipseItem *cuerpo = scene->addEllipse(-21, -17, 42, 42,
                                                     QPen(QColor(100, 20, 25), 3),
                                                     QBrush(rojo));
    scene->addEllipse(-10, -33, 20, 22, QPen(QColor(100, 20, 25), 2), QBrush(QColor(235, 120, 105)))->setParentItem(cuerpo);
    scene->addEllipse(-8, -27, 5, 6, QPen(Qt::black), QBrush(Qt::black))->setParentItem(cuerpo);
    scene->addEllipse(3, -27, 5, 6, QPen(Qt::black), QBrush(Qt::black))->setParentItem(cuerpo);
    scene->addLine(-9, -19, 9, -19, QPen(QColor(80, 0, 0), 2))->setParentItem(cuerpo);
    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Smedley");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-28, 23);
    grafico = cuerpo;
    grafico->setZValue(6);
    grafico->setPos(x, y);
}
