#include "chillywilly.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QPixmap>
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

    QGraphicsPixmapItem *cuerpo = scene->addPixmap(QPixmap(":/sprites/chilly.png"));
    cuerpo->setOffset(-48, -48);
    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Chilly");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-24, 32);
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
