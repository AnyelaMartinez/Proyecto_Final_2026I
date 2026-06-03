#include "chillywilly.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QRadialGradient>

ChillyWilly::ChillyWilly(int xInicial, int yInicial)
    : Personaje(xInicial, yInicial, "chilly"), barriendo(false), bonusActivo(false), tiempoBonus(0.0f)
{
    velocidad = 150.0f;
    agilidad = 1.2f;
}

void ChillyWilly::barrer()
{
    barriendo = true;
}

void ChillyWilly::dejarDeBarrer()
{
    barriendo = false;
}

void ChillyWilly::lanzar(PiedraCurling &piedra, float fuerza, float angulo)
{
    piedra.aplicarFuerza(bonusActivo ? fuerza * 1.15f : fuerza, angulo);
}

void ChillyWilly::recogerPescado()
{
    bonusActivo = true;
    tiempoBonus = 8.0f;
}

void ChillyWilly::actualizar(float dt)
{
    if (bonusActivo) {
        tiempoBonus -= dt;
        if (tiempoBonus <= 0.0f) {
            bonusActivo = false;
            tiempoBonus = 0.0f;
        }
    }
    ObjetoBase::actualizar(dt);
}

void ChillyWilly::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    QGraphicsEllipseItem *sombra = scene->addEllipse(-25, 18, 50, 14,
                                                     QPen(Qt::NoPen),
                                                     QBrush(QColor(0, 0, 0, 55)));

    QRadialGradient azul(-8, -18, 44);
    azul.setColorAt(0.0, QColor(95, 170, 245));
    azul.setColorAt(0.55, QColor(35, 95, 175));
    azul.setColorAt(1.0, QColor(12, 45, 95));

    QGraphicsEllipseItem *cuerpo = scene->addEllipse(-20, -30, 40, 58,
                                                     QPen(QColor(10, 35, 75), 3),
                                                     QBrush(azul));
    sombra->setParentItem(cuerpo);
    sombra->setPos(0, 0);

    scene->addEllipse(-12, -18, 24, 34, QPen(QColor(20, 40, 80), 1), QBrush(Qt::white))->setParentItem(cuerpo);
    scene->addEllipse(-7, -24, 14, 13, QPen(QColor(110, 75, 0), 1), QBrush(QColor(255, 215, 55)))->setParentItem(cuerpo);
    scene->addEllipse(-9, -10, 6, 8, QPen(Qt::black), QBrush(Qt::black))->setParentItem(cuerpo);
    scene->addEllipse(3, -10, 6, 8, QPen(Qt::black), QBrush(Qt::black))->setParentItem(cuerpo);
    scene->addEllipse(-7, -8, 2, 2, QPen(Qt::NoPen), QBrush(Qt::white))->setParentItem(cuerpo);
    scene->addEllipse(5, -8, 2, 2, QPen(Qt::NoPen), QBrush(Qt::white))->setParentItem(cuerpo);
    scene->addPolygon(QPolygonF() << QPointF(-3, -1) << QPointF(14, 3) << QPointF(-3, 8),
                      QPen(QColor(180, 120, 0), 1), QBrush(QColor(255, 190, 45)))
        ->setParentItem(cuerpo);
    scene->addEllipse(-24, 15, 16, 10, QPen(QColor(10, 35, 75), 2), QBrush(QColor(20, 80, 150)))->setParentItem(cuerpo);
    scene->addEllipse(8, 15, 16, 10, QPen(QColor(10, 35, 75), 2), QBrush(QColor(20, 80, 150)))->setParentItem(cuerpo);

    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Chilly");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-24, 31);
    grafico = cuerpo;
    grafico->setZValue(6);
    grafico->setPos(x, y);
}

bool ChillyWilly::estaBarriendo() const
{
    return barriendo;
}

bool ChillyWilly::tieneBonus() const
{
    return bonusActivo;
}
