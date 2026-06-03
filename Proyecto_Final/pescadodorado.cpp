#include "pescadodorado.h"

#include "chillywilly.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QPolygonF>
#include <QPixmap>
#include <QRadialGradient>
#include <QtMath>

PescadoDorado::PescadoDorado(int xInicial, int yInicial)
    : ObjetoBase(xInicial, yInicial, "pescado"),
      duracionBonus(8.0f),
      recolectado(false),
      tiempo(0.0f),
      baseY(yInicial),
      direccion(1)
{
}

void PescadoDorado::otorgarBonus(ChillyWilly &c)
{
    if (!recolectado) {
        c.recogerPescado();
        recolectado = true;
        setActivo(false);
    }
}

void PescadoDorado::reiniciar(int nuevaX, int nuevaY)
{
    recolectado = false;
    tiempo = 0.0f;
    baseY = nuevaY;
    direccion = 1;
    setPosicion(nuevaX, nuevaY);
    setActivo(true);
}

void PescadoDorado::actualizar(float dt)
{
    if (activo && !recolectado) {
        tiempo += dt;
        x += direccion;
        if (x < 310 || x > 470) {
            direccion *= -1;
        }
        y = baseY + static_cast<int>(std::sin(tiempo * 5.0f) * 10.0f);
    }
    ObjetoBase::actualizar(dt);
}

void PescadoDorado::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    QGraphicsPixmapItem *pez = scene->addPixmap(QPixmap(":/sprites/pescado.png"));
    pez->setOffset(-48, -48);
    grafico = pez;
    grafico->setZValue(5);
    grafico->setPos(x, y);
}
