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
#include <QRandomGenerator>

ChillyWilly::ChillyWilly(int xInicial, int yInicial)
    : Personaje(xInicial, yInicial, "chilly"),
    barriendo(false), bonusActivo(false), tiempoBonus(0.0f),
    inestabilidad(0.2f),
    frameActual(0), tiempoAnim(0.0f),
    ultimaX(xInicial), ultimaY(yInicial), tiempoLanzando(0.0f)
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
    // Inestabilidad: anade ruido aleatorio al angulo y la fuerza
    float ruidoAngulo = static_cast<float>((QRandomGenerator::global()->generateDouble() * 2.0 - 1.0)) * inestabilidad * 6.0f;
    float ruidoFuerza = static_cast<float>((QRandomGenerator::global()->generateDouble() * 2.0 - 1.0)) * inestabilidad * 25.0f;
    float fuerzaFinal = (bonusActivo ? fuerza * 1.15f : fuerza) + ruidoFuerza;
    float anguloFinal = angulo + ruidoAngulo;
    piedra.aplicarFuerza(fuerzaFinal, anguloFinal);
    tiempoLanzando = 0.4f;
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

    tiempoAnim += dt;
    if (tiempoLanzando > 0.0f) tiempoLanzando -= dt;
    bool moviendose = (x != ultimaX || y != ultimaY);
    ultimaX = x;
    ultimaY = y;

    int nuevoFrame;
    if (tiempoLanzando > 0.0f) {
        nuevoFrame = 3;
    } else if (barriendo) {
        nuevoFrame = 4 + (static_cast<int>(tiempoAnim * 6.0f) % 2);
    } else if (moviendose) {
        nuevoFrame = 1 + (static_cast<int>(tiempoAnim * 5.0f) % 2);
    } else {
        nuevoFrame = 0;
    }

    if (grafico && nuevoFrame != frameActual) {
        frameActual = nuevoFrame;
        QGraphicsPixmapItem *p = static_cast<QGraphicsPixmapItem*>(grafico);
        p->setPixmap(spriteSheet.copy(frameActual * 96, 0, 96, 96));
    }

    ObjetoBase::actualizar(dt);
}

void ChillyWilly::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    if (spriteSheet.isNull()) {
        spriteSheet.load(":/sprites/chilly_sheet.png");
    }
    QGraphicsPixmapItem *cuerpo = scene->addPixmap(spriteSheet.copy(0, 0, 96, 96));
    cuerpo->setOffset(-48, -48);
    cuerpo->setScale(0.65);
    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Chilly");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-24, 32);
    grafico = cuerpo;
    grafico->setZValue(6);
    grafico->setPos(x, y);
    frameActual = 0;
}

bool ChillyWilly::estaBarriendo() const
{
    return barriendo;
}

bool ChillyWilly::tieneBonus() const
{
    return bonusActivo;
}

void ChillyWilly::setInestabilidad(float i)
{
    inestabilidad = i;
}
