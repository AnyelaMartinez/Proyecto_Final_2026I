#include "nivel2.h"

#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>
#include <Qt>

Nivel2::Nivel2()
    : tiempoLimite(20.0f), tiempoRestante(20.0f), metaX(650)
{
}

void Nivel2::inicializar()
{
    tiempoTranscurrido = 0.0f;
    tiempoRestante = tiempoLimite;
}

void Nivel2::actualizar(float dt)
{
    tiempoTranscurrido += dt;
    tiempoRestante -= dt;
    if (tiempoRestante < 0.0f) {
        tiempoRestante = 0.0f;
    }
}

void Nivel2::dibujar(QGraphicsScene *scene)
{
    pista.dibujar(scene);
    scene->addRect(metaX - 8, 0, 16, pista.getAlto(), QPen(Qt::darkGreen, 2), QBrush(QColor(180, 255, 180, 120)));
    scene->addText("Meta de barrido")->setPos(metaX - 55, 20);
}

void Nivel2::procesarTecla(int tecla)
{
    Q_UNUSED(tecla);
}

bool Nivel2::terminado() const
{
    return tiempoRestante <= 0.0f;
}

void Nivel2::procesarBarrido()
{
    tiempoRestante += 0.20f;
    if (tiempoRestante > tiempoLimite) {
        tiempoRestante = tiempoLimite;
    }
}

bool Nivel2::verificarLlegada(int xPiedra) const
{
    return xPiedra >= metaX;
}

bool Nivel2::verificarTiempo() const
{
    return tiempoRestante > 0.0f;
}

float Nivel2::getTiempoRestante() const
{
    return tiempoRestante;
}
