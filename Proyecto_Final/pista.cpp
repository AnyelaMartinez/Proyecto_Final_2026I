#include "pista.h"

#include "piedracurling.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsSimpleTextItem>
#include <QLinearGradient>
#include <QPen>

Pista::Pista(int anchoInicial, int altoInicial)
    : ancho(anchoInicial), alto(altoInicial)
{
    // Fondo: hielo normal cubriendo toda la pista
    agregarZona(std::make_unique<HieloNormal>(Vector2D(0, 0), ancho, alto));

    // Manchones de hielo resbaladizo
    agregarZona(std::make_unique<HieloResbaladizo>(Vector2D(170, 90), 110, 70));
    agregarZona(std::make_unique<HieloResbaladizo>(Vector2D(380, 330), 100, 60));

    // Manchones de nieve espesa
    agregarZona(std::make_unique<NieveEspesa>(Vector2D(290, 200), 90, 70));
    agregarZona(std::make_unique<NieveEspesa>(Vector2D(450, 90), 80, 80));

    // Manchon magico
    agregarZona(std::make_unique<ZonaMagica>(Vector2D(180, 290), 100, 100));
}

Zona *Pista::zonaEn(float px, float py) const
{
    // Recorre al reves para que los manchones tengan prioridad sobre el fondo
    for (auto it = zonas.rbegin(); it != zonas.rend(); ++it) {
        if ((*it)->contiene(px, py)) {
            return it->get();
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
    // Fondo con gradiente suave azul-blanco
    QLinearGradient fondo(0, 0, 0, alto);
    fondo.setColorAt(0.0, QColor(180, 215, 240));
    fondo.setColorAt(1.0, QColor(230, 245, 255));
    scene->setBackgroundBrush(QBrush(fondo));

    // Dibuja todas las zonas (fondo primero, manchones encima)
    for (const auto &zona : zonas) {
        zona->dibujar(scene);
    }

    // Linea de lanzamiento
    scene->addLine(85, 0, 85, alto, QPen(QColor(70, 100, 160, 180), 2, Qt::DashLine));

    // Borde de la pista
    scene->addRect(0, 0, ancho, alto, QPen(QColor(50, 80, 130), 4), Qt::NoBrush);

    // Etiquetas
    QFont fontEtiqueta("Arial", 10, QFont::Bold);
    QGraphicsSimpleTextItem *inicio = scene->addSimpleText("LANZAMIENTO", fontEtiqueta);
    inicio->setBrush(QBrush(QColor(40, 60, 100)));
    inicio->setPos(12, 12);

    QGraphicsSimpleTextItem *meta = scene->addSimpleText("CASA", fontEtiqueta);
    meta->setBrush(QBrush(QColor(160, 30, 30)));
    meta->setPos(622, 12);
}

int Pista::getAncho() const
{
    return ancho;
}

int Pista::getAlto() const
{
    return alto;
}
