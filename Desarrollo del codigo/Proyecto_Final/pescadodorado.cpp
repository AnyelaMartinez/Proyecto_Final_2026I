#include "pescadodorado.h"

#include "chillywilly.h"

#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPen>
#include <QPolygonF>
#include <QPixmap>
#include <QRadialGradient>
#include <QRandomGenerator>
#include <QtMath>

PescadoDorado::PescadoDorado(int xInicial, int yInicial)
    : ObjetoBase(xInicial, yInicial, "pescado"),
    duracionBonus(8.0f),
    recolectado(false),
    tiempo(0.0f),
    baseY(yInicial),
    direccion(1),
    modoRandom(false),
    xMinR(310), xMaxR(470),
    yMinR(360), yMaxR(360),
    frameActual(0)
{
}

void PescadoDorado::setModoRandom(bool r, int xMin, int xMax, int yMin, int yMax)
{
    modoRandom = r;
    xMinR = xMin;
    xMaxR = xMax;
    yMinR = yMin;
    yMaxR = yMax;
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
    if (recolectado) {
        ObjetoBase::actualizar(dt);
        return;
    }
    tiempo += dt;
    // Ciclo: 5 seg visible, 3 seg escondido
    float cycle = std::fmod(tiempo, 8.0f);
    bool deberiaActivo = cycle < 5.0f;
    bool acabaDeAparecer = deberiaActivo && !activo;
    if (activo != deberiaActivo) {
        setActivo(deberiaActivo);
    }

    if (acabaDeAparecer && modoRandom) {
        // Aparece en un punto aleatorio del tablero
        QRandomGenerator *rng = QRandomGenerator::global();
        int rangoX = qMax(1, xMaxR - xMinR);
        int rangoY = qMax(1, yMaxR - yMinR);
        x = xMinR + rng->bounded(rangoX);
        y = yMinR + rng->bounded(rangoY);
        baseY = y;
    } else if (activo && !modoRandom) {
        // Modo patrullaje horizontal (Nivel 2)
        x += direccion;
        if (x < 310 || x > 470) {
            direccion *= -1;
        }
        y = baseY + static_cast<int>(std::sin(tiempo * 5.0f) * 10.0f);
    } else if (activo && modoRandom) {
        // Pequeno bobbing en el sitio aleatorio
        y = baseY + static_cast<int>(std::sin(tiempo * 5.0f) * 6.0f);
    }

    // Animacion de aleteo
    int nuevoFrame = static_cast<int>(tiempo * 4.0f) % 4;
    if (grafico && nuevoFrame != frameActual) {
        frameActual = nuevoFrame;
        QGraphicsPixmapItem *p = static_cast<QGraphicsPixmapItem*>(grafico);
        p->setPixmap(spriteSheet.copy(frameActual * 96, 0, 96, 96));
    }

    ObjetoBase::actualizar(dt);
}

void PescadoDorado::dibujar(QGraphicsScene *scene)
{
    if (!scene || grafico) {
        return;
    }

    if (spriteSheet.isNull()) {
        spriteSheet.load(":/sprites/pescado_sheet.png");
    }
    QGraphicsPixmapItem *pez = scene->addPixmap(spriteSheet.copy(0, 0, 96, 96));
    pez->setOffset(-48, -48);
    pez->setScale(0.65);
    grafico = pez;
    grafico->setZValue(5);
    grafico->setPos(x, y);
    frameActual = 0;
}
