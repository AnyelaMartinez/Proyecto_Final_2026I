#include "pista.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsSimpleTextItem>
#include <QPen>

Pista::Pista(int anchoInicial, int altoInicial)
    : ancho(anchoInicial), alto(altoInicial)
{
    agregarZona(std::make_unique<HieloNormal>(Vector2D(0, 0), ancho, alto));
    agregarZona(std::make_unique<HieloResbaladizo>(Vector2D(190, 0), 190, alto));
    agregarZona(std::make_unique<ZonaMagica>(Vector2D(395, 0), 95, alto));
    agregarZona(std::make_unique<NieveEspesa>(Vector2D(510, 0), 95, alto));
}

Zona *Pista::zonaEn(float px, float py) const
{
    for (const auto &zona : zonas) {
        if (zona->contiene(px, py)) {
            return zona.get();
        }
    }
    return nullptr;
}

void Pista::agregarZona(std::unique_ptr<Zona> zona)
{
    zonas.push_back(std::move(zona));
}

void Pista::aplicarZona(PiedraCurling &piedra) const
{
    Zona *zona = zonaEn(piedra.getX(), piedra.getY());
    if (zona) {
        zona->aplicarEfecto(piedra);
    }
}

void Pista::dibujar(QGraphicsScene *scene) const
{
    scene->setBackgroundBrush(QBrush(QColor(210, 235, 245)));
    for (const auto &zona : zonas) {
        zona->dibujar(scene);
    }
    for (int i = 0; i < alto; i += 34) {
        scene->addLine(0, i, ancho, i, QPen(QColor(255, 255, 255, 55), 1));
    }
    scene->addRect(0, 0, ancho, alto, QPen(Qt::darkBlue, 4), Qt::NoBrush);
    scene->addLine(85, 0, 85, alto, QPen(Qt::darkGray, 2, Qt::DashLine));
    QGraphicsSimpleTextItem *inicio = scene->addSimpleText("Zona de lanzamiento");
    inicio->setPos(18, 18);
    QGraphicsSimpleTextItem *meta = scene->addSimpleText("Casa objetivo");
    meta->setPos(595, 455);
}

int Pista::getAncho() const
{
    return ancho;
}

int Pista::getAlto() const
{
    return alto;
}
