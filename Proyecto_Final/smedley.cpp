#include "smedley.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QPixmap>
#include <QRadialGradient>
#include <QRandomGenerator>

Smedley::Smedley(int xInicial, int yInicial)
    : Personaje(xInicial, yInicial, "smedley"),
    velocidadPatrulla(95.0f),
    direccion(1),
    patronVertical(true),
    enLane(true),
    tiempoEstado(0.0f),
    cooldownColision(0.0f),
    colision(0.80f),
    frameActual(0),
    tiempoAnim(0.0f)
{
}

void Smedley::interferir(PiedraCurling &piedra)
{
    if (cooldownColision > 0.0f) return;
    if (!patronVertical && !enLane) return;
    if (piedra.detenido()) return;
    const int dx = piedra.getX() - x;
    const int dy = piedra.getY() - y;
    if (dx * dx + dy * dy < 2600) {
        colision.aplicarContra(piedra, static_cast<float>(dx), static_cast<float>(dy));
        if (patronVertical) {
            piedra.aplicarEmpuje(25.0f, direccion * 18.0f);
        } else {
            piedra.aplicarEmpuje(-25.0f, 0.0f);
        }
        cooldownColision = 0.8f;
    }
}

void Smedley::actualizarRuta()
{
    if (patronVertical) {
        if (y < 80 || y > 390) {
            direccion *= -1;
        }
    }
}

void Smedley::actualizar(float dt)
{
    if (cooldownColision > 0.0f) cooldownColision -= dt;

    if (patronVertical) {
        y += static_cast<int>(direccion * velocidadPatrulla * dt);
        actualizarRuta();
    } else {
        // Ciclo: 3 seg visible en un punto aleatorio, 3 seg escondido
        tiempoEstado += dt;
        if (enLane) {
            if (tiempoEstado > 3.0f) {
                enLane = false;
                tiempoEstado = 0.0f;
                x = -200;
            }
        } else {
            if (tiempoEstado > 3.0f) {
                enLane = true;
                tiempoEstado = 0.0f;
                x = 150 + QRandomGenerator::global()->bounded(401);
            }
        }
    }

    // Animacion
    tiempoAnim += dt;
    int nuevoFrame;
    if (cooldownColision > 0.5f) {
        nuevoFrame = 4; // gruñido al chocar
    } else {
        nuevoFrame = static_cast<int>(tiempoAnim * 8.0f) % 4; // ciclo de carrera
    }
    if (grafico && nuevoFrame != frameActual) {
        frameActual = nuevoFrame;
        QGraphicsPixmapItem *p = static_cast<QGraphicsPixmapItem*>(grafico);
        p->setPixmap(spriteSheet.copy(frameActual * 96, 0, 96, 96));
    }

    ObjetoBase::actualizar(dt);
}

void Smedley::setPatronVertical(bool v)
{
    patronVertical = v;
    direccion = 1;
    enLane = true;
    tiempoEstado = 0.0f;
    cooldownColision = 0.0f;
}

void Smedley::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    if (spriteSheet.isNull()) {
        spriteSheet.load(":/sprites/smedley_sheet.png");
    }
    QGraphicsPixmapItem *cuerpo = scene->addPixmap(spriteSheet.copy(0, 0, 96, 96));
    cuerpo->setOffset(-48, -48);
    cuerpo->setScale(0.65);
    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Smedley");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-28, 23);
    grafico = cuerpo;
    grafico->setZValue(6);
    grafico->setPos(x, y);
    frameActual = 0;
}
