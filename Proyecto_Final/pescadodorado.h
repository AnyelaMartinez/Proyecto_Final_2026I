#ifndef PESCADODORADO_H
#define PESCADODORADO_H

#include "objetobase.h"

#include <QPixmap>

class ChillyWilly;

class PescadoDorado : public ObjetoBase
{
public:
    PescadoDorado(int xInicial = 355, int yInicial = 330);

    void otorgarBonus(ChillyWilly &c);
    void reiniciar(int nuevaX = 350, int nuevaY = 360);
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;

    void setModoRandom(bool r, int xMin, int xMax, int yMin, int yMax);

private:
    float duracionBonus;
    bool recolectado;
    float tiempo;
    int baseY;
    int direccion;
    bool modoRandom;
    int xMinR;
    int xMaxR;
    int yMinR;
    int yMaxR;
    QPixmap spriteSheet;
    int frameActual;
};

#endif
