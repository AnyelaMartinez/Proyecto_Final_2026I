#include "zona.h"

#include "piedracurling.h"

#include <QBrush>
#include <QPen>
#include <QRadialGradient>
#include <QRandomGenerator>
#include <QtMath>

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
    // El fondo lo pinta Pista
    Q_UNUSED(scene);
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
    QRandomGenerator rng(static_cast<quint32>(pos.x * 100 + pos.y + 1));

    // Blob principal con gradiente radial que se desvanece a transparente
    float cx = pos.x + ancho / 2.0f;
    float cy = pos.y + alto / 2.0f;
    float rMax = qMax(ancho, alto) / 2.0f + 12.0f;

    QRadialGradient mainGrad(cx, cy, rMax);
    mainGrad.setColorAt(0.0, QColor(150, 220, 255, 170));
    mainGrad.setColorAt(0.5, QColor(170, 230, 255, 110));
    mainGrad.setColorAt(0.85, QColor(190, 240, 255, 40));
    mainGrad.setColorAt(1.0, QColor(200, 245, 255, 0));
    scene->addEllipse(cx - rMax, cy - rMax, rMax * 2, rMax * 2,
                      QPen(Qt::NoPen), QBrush(mainGrad));

    // Blobs secundarios para irregularidad
    for (int i = 0; i < 3; i++) {
        float bx = pos.x + rng.bounded(ancho);
        float by = pos.y + rng.bounded(alto);
        float br = rng.bounded(18, 35);
        QRadialGradient g(bx, by, br);
        g.setColorAt(0.0, QColor(180, 235, 255, 130));
        g.setColorAt(1.0, QColor(190, 240, 255, 0));
        scene->addEllipse(bx - br, by - br, br * 2, br * 2,
                          QPen(Qt::NoPen), QBrush(g));
    }

    // Destellos pequenos (siguen siendo crisp para dar caracter de hielo)
    for (int i = 0; i < 3; i++) {
        float sx = pos.x + 15 + rng.bounded(ancho - 30);
        float sy = pos.y + 15 + rng.bounded(alto - 30);
        scene->addLine(sx - 3, sy, sx + 3, sy, QPen(QColor(255, 255, 255, 220), 1));
        scene->addLine(sx, sy - 3, sx, sy + 3, QPen(QColor(255, 255, 255, 220), 1));
    }
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
    QRandomGenerator rng(static_cast<quint32>(pos.x * 100 + pos.y + 3));

    // Blob central blanco que se desvanece
    float cx = pos.x + ancho / 2.0f;
    float cy = pos.y + alto / 2.0f;
    float rMax = qMax(ancho, alto) / 2.0f + 15.0f;

    QRadialGradient mainGrad(cx, cy, rMax);
    mainGrad.setColorAt(0.0, QColor(255, 255, 255, 220));
    mainGrad.setColorAt(0.5, QColor(255, 255, 255, 150));
    mainGrad.setColorAt(0.85, QColor(248, 250, 255, 50));
    mainGrad.setColorAt(1.0, QColor(248, 250, 255, 0));
    scene->addEllipse(cx - rMax, cy - rMax, rMax * 2, rMax * 2,
                      QPen(Qt::NoPen), QBrush(mainGrad));

    // Drifts secundarios para textura irregular
    for (int i = 0; i < 12; i++) {
        float bx = pos.x + rng.bounded(ancho);
        float by = pos.y + rng.bounded(alto);
        float br = rng.bounded(12, 28);
        QRadialGradient g(bx, by, br);
        g.setColorAt(0.0, QColor(255, 255, 255, 180));
        g.setColorAt(0.7, QColor(255, 255, 255, 60));
        g.setColorAt(1.0, QColor(255, 255, 255, 0));
        scene->addEllipse(bx - br, by - br, br * 2, br * 2,
                          QPen(Qt::NoPen), QBrush(g));
    }

    // Algunas sombras suaves para profundidad sutil
    for (int i = 0; i < 4; i++) {
        float bx = pos.x + rng.bounded(ancho);
        float by = pos.y + rng.bounded(alto);
        float br = rng.bounded(10, 18);
        QRadialGradient s(bx, by, br);
        s.setColorAt(0.0, QColor(200, 215, 235, 80));
        s.setColorAt(1.0, QColor(200, 215, 235, 0));
        scene->addEllipse(bx - br, by - br, br * 2, br * 2,
                          QPen(Qt::NoPen), QBrush(s));
    }
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
    QRandomGenerator rng(static_cast<quint32>(pos.x * 100 + pos.y + 4));

    // Aura purpura principal con gradiente radial muy suave
    float cx = pos.x + ancho / 2.0f;
    float cy = pos.y + alto / 2.0f;
    float rMax = qMax(ancho, alto) / 2.0f + 20.0f;

    QRadialGradient mainGrad(cx, cy, rMax);
    mainGrad.setColorAt(0.0, QColor(200, 150, 240, 180));
    mainGrad.setColorAt(0.4, QColor(180, 130, 230, 130));
    mainGrad.setColorAt(0.8, QColor(160, 110, 220, 50));
    mainGrad.setColorAt(1.0, QColor(140, 90, 200, 0));
    scene->addEllipse(cx - rMax, cy - rMax, rMax * 2, rMax * 2,
                      QPen(Qt::NoPen), QBrush(mainGrad));

    // Wisps purpura secundarios
    for (int i = 0; i < 4; i++) {
        float bx = pos.x + rng.bounded(ancho);
        float by = pos.y + rng.bounded(alto);
        float br = rng.bounded(18, 32);
        QRadialGradient g(bx, by, br);
        g.setColorAt(0.0, QColor(220, 170, 250, 120));
        g.setColorAt(1.0, QColor(220, 170, 250, 0));
        scene->addEllipse(bx - br, by - br, br * 2, br * 2,
                          QPen(Qt::NoPen), QBrush(g));
    }

    // Sparkles dorados (crisp para dar el efecto magico)
    for (int i = 0; i < 8; i++) {
        float sx = pos.x + 10 + rng.bounded(ancho - 20);
        float sy = pos.y + 10 + rng.bounded(alto - 20);
        float tam = rng.bounded(3, 5);
        scene->addEllipse(sx - tam / 2, sy - tam / 2, tam, tam,
                          QPen(Qt::NoPen), QBrush(QColor(255, 240, 180, 230)));
        scene->addLine(sx - tam - 2, sy, sx + tam + 2, sy,
                       QPen(QColor(255, 240, 180, 180), 1));
        scene->addLine(sx, sy - tam - 2, sx, sy + tam + 2,
                       QPen(QColor(255, 240, 180, 180), 1));
    }
}
