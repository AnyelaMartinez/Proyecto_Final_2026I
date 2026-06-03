#include "smedley.h"

#include "piedracurling.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QPen>
#include <QPixmap>
#include <QRadialGradient>

Smedley::Smedley(int xInicial, int yInicial)
    : Personaje(xInicial, yInicial, "smedley"),
    velocidadPatrulla(95.0f),
    direccion(1),
    colision(0.80f)
{
}

void Smedley::interferir(PiedraCurling &piedra)
{
    const int dx = piedra.getX() - x;
    const int dy = piedra.getY() - y;
    if (dx * dx + dy * dy < 2600) {
        colision.aplicarContra(piedra, static_cast<float>(dx), static_cast<float>(dy));
        piedra.aplicarEmpuje(25.0f, direccion * 18.0f);
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

    QGraphicsPixmapItem *cuerpo = scene->addPixmap(QPixmap(":/sprites/smedley.png"));
    cuerpo->setOffset(-48, -48);
    QGraphicsSimpleTextItem *nombre = scene->addSimpleText("Smedley");
    nombre->setParentItem(cuerpo);
    nombre->setPos(-28, 23);
    grafico = cuerpo;
    grafico->setZValue(6);
    grafico->setPos(x, y);
}
