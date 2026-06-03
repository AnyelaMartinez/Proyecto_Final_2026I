#include "zona.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>

Zona::Zona(Vector2D posicion, int anchoZona, int altoZona, float friccionZona)
    : pos(posicion),
      ancho(anchoZona),
      alto(altoZona),
      friccion(friccionZona),
      fisica(std::make_unique<FisicaFriccion>(friccionZona))
{
}

Zona::~Zona()
{
}

bool Zona::contiene(float px, float py) const
{
    return QRectF(pos.x, pos.y, ancho, alto).contains(px, py);
}

void Zona::aplicarEfecto(PiedraCurling &piedra) const
{
    fisica->aplicar(piedra, 0.016f);
}

HieloNormal::HieloNormal(Vector2D posicion, int ancho, int alto)
    : Zona(posicion, ancho, alto, 0.48f)
{
}

void HieloNormal::dibujar(QGraphicsScene *scene) const
{
    scene->addRect(pos.x, pos.y, ancho, alto, QPen(Qt::NoPen), QBrush(QColor(232, 248, 255)));
}

HieloResbaladizo::HieloResbaladizo(Vector2D posicion, int ancho, int alto)
    : Zona(posicion, ancho, alto, 0.22f)
{
}

void HieloResbaladizo::aplicarEfecto(PiedraCurling &piedra) const
{
    Zona::aplicarEfecto(piedra);
}

void HieloResbaladizo::dibujar(QGraphicsScene *scene) const
{
    scene->addRect(pos.x, pos.y, ancho, alto, QPen(Qt::NoPen), QBrush(QColor(178, 232, 255)));
    QGraphicsSimpleTextItem *txt = scene->addSimpleText("Hielo resbaladizo");
    txt->setPos(pos.x + 12, pos.y + 12);
}

NieveEspesa::NieveEspesa(Vector2D posicion, int ancho, int alto)
    : Zona(posicion, ancho, alto, 0.90f)
{
}

void NieveEspesa::aplicarEfecto(PiedraCurling &piedra) const
{
    Zona::aplicarEfecto(piedra);
}

void NieveEspesa::dibujar(QGraphicsScene *scene) const
{
    scene->addRect(pos.x, pos.y, ancho, alto, QPen(Qt::NoPen), QBrush(QColor(248, 248, 248)));
    QGraphicsSimpleTextItem *txt = scene->addSimpleText("Nieve espesa");
    txt->setPos(pos.x + 12, pos.y + 12);
}

ZonaMagica::ZonaMagica(Vector2D posicion, int ancho, int alto)
    : Zona(posicion, ancho, alto, 0.40f)
{
    fisica = std::make_unique<FisicaPerturbacion>(38.0f, 7.0f, 0.0f);
}

void ZonaMagica::aplicarEfecto(PiedraCurling &piedra) const
{
    piedra.setFriccion(friccion);
    fisica->aplicar(piedra, 0.016f);
}

void ZonaMagica::dibujar(QGraphicsScene *scene) const
{
    scene->addRect(pos.x, pos.y, ancho, alto, QPen(Qt::NoPen), QBrush(QColor(215, 190, 255, 170)));
    QGraphicsSimpleTextItem *txt = scene->addSimpleText("Zona magica");
    txt->setPos(pos.x + 12, pos.y + 12);
}
