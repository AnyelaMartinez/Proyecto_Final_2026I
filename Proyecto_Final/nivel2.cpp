#include "nivel2.h"

#include <QBrush>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QLinearGradient>
#include <QPen>
#include <QPolygonF>
#include <QRadialGradient>
#include <QRandomGenerator>
#include <Qt>

Nivel2::Nivel2()
    : tiempoLimite(90.0f), tiempoRestante(90.0f), metaX(660)
{
    // Zonas a la altura del carril lateral (la piedra va por y ~= 400)
    pista.agregarZona(std::make_unique<NieveEspesa>(Vector2D(220, 380), 75, 55));
    pista.agregarZona(std::make_unique<NieveEspesa>(Vector2D(420, 380), 75, 55));
    pista.agregarZona(std::make_unique<ZonaMagica>(Vector2D(325, 380), 65, 55));
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
    const int W = pista.getAncho();
    const int H = pista.getAlto();
    const int sueloY = 360;

    // Cielo
    QLinearGradient sky(0, 0, 0, sueloY);
    sky.setColorAt(0.0, QColor(100, 150, 220));
    sky.setColorAt(1.0, QColor(200, 230, 255));
    scene->addRect(0, 0, W, sueloY, QPen(Qt::NoPen), QBrush(sky));

    // Montanas
    QPolygonF m1;
    m1 << QPointF(-20, sueloY) << QPointF(180, 200) << QPointF(400, sueloY);
    scene->addPolygon(m1, QPen(Qt::NoPen), QBrush(QColor(110, 140, 180, 200)));

    QPolygonF m2;
    m2 << QPointF(300, sueloY) << QPointF(550, 170) << QPointF(800, sueloY);
    scene->addPolygon(m2, QPen(Qt::NoPen), QBrush(QColor(130, 160, 200, 180)));

    QPolygonF p1;
    p1 << QPointF(155, 225) << QPointF(180, 200) << QPointF(205, 225);
    scene->addPolygon(p1, QPen(Qt::NoPen), QBrush(QColor(255, 255, 255, 230)));

    QPolygonF p2;
    p2 << QPointF(525, 195) << QPointF(550, 170) << QPointF(575, 195);
    scene->addPolygon(p2, QPen(Qt::NoPen), QBrush(QColor(255, 255, 255, 230)));

    // Suelo
    QLinearGradient ground(0, sueloY, 0, H);
    ground.setColorAt(0.0, QColor(220, 240, 255));
    ground.setColorAt(1.0, QColor(170, 210, 245));
    scene->addRect(0, sueloY, W, H - sueloY, QPen(Qt::NoPen), QBrush(ground));

    for (int y = sueloY + 20; y < H; y += 25) {
        scene->addLine(0, y, W, y, QPen(QColor(255, 255, 255, 60), 1));
    }
    scene->addLine(0, sueloY, W, sueloY, QPen(QColor(80, 110, 150), 2));

    // Manchones de nieve espesa sobre el carril
    QRandomGenerator rng(7777);
    auto dibujarBlobNieve = [&](int cx, int cy) {
        QRadialGradient g(cx, cy, 50);
        g.setColorAt(0.0, QColor(255, 255, 255, 230));
        g.setColorAt(0.7, QColor(255, 255, 255, 130));
        g.setColorAt(1.0, QColor(255, 255, 255, 0));
        scene->addEllipse(cx - 50, cy - 25, 100, 50, QPen(Qt::NoPen), QBrush(g));
        for (int i = 0; i < 6; i++) {
            int dx = rng.bounded(-30, 30);
            int dy = rng.bounded(-15, 15);
            int r = rng.bounded(8, 18);
            scene->addEllipse(cx + dx - r, cy + dy - r / 2, r * 2, r,
                              QPen(Qt::NoPen), QBrush(QColor(255, 255, 255, 220)));
        }
    };
    dibujarBlobNieve(255, 408);
    dibujarBlobNieve(455, 408);

    // Manchon magico
    int mcx = 358, mcy = 408;
    QRadialGradient gm(mcx, mcy, 45);
    gm.setColorAt(0.0, QColor(220, 170, 250, 220));
    gm.setColorAt(0.6, QColor(180, 130, 230, 130));
    gm.setColorAt(1.0, QColor(180, 130, 230, 0));
    scene->addEllipse(mcx - 45, mcy - 25, 90, 50, QPen(Qt::NoPen), QBrush(gm));
    for (int i = 0; i < 8; i++) {
        int dx = rng.bounded(-30, 30);
        int dy = rng.bounded(-15, 15);
        int tam = rng.bounded(3, 6);
        scene->addEllipse(mcx + dx, mcy + dy, tam, tam,
                          QPen(Qt::NoPen), QBrush(QColor(255, 240, 180, 230)));
    }

    // Casa-objetivo sobre el hielo (mas grande para que sea mas facil acertarle)
    int cx = metaX, cy = sueloY + 70;
    scene->addEllipse(cx - 70, cy - 26, 140, 52,
                      QPen(QColor(50, 80, 130), 3), QBrush(QColor(225, 240, 255, 230)));
    scene->addEllipse(cx - 45, cy - 17, 90, 34,
                      QPen(QColor(180, 30, 30), 3), QBrush(QColor(255, 235, 235, 220)));
    scene->addEllipse(cx - 22, cy - 9, 44, 18,
                      QPen(QColor(50, 80, 130), 2), QBrush(QColor(225, 240, 255, 230)));
    scene->addEllipse(cx - 8, cy - 3, 16, 8,
                      QPen(Qt::NoPen), QBrush(QColor(220, 30, 30)));

    QFont fonte("Arial", 11, QFont::Bold);
    QGraphicsSimpleTextItem *meta = scene->addSimpleText("CASA", fonte);
    meta->setBrush(QBrush(QColor(180, 30, 30)));
    meta->setPos(metaX - 18, sueloY - 25);

    // Borde
    scene->addRect(0, 0, W, H, QPen(QColor(50, 80, 130), 4), Qt::NoBrush);
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
    // El barrido solo cambia la friccion en Juego, ya no extiende el tiempo
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

void Nivel2::setTiempoRestante(float t)
{
    if (t < 0.0f) t = 0.0f;
    if (t > tiempoLimite) t = tiempoLimite;
    tiempoRestante = t;
}
