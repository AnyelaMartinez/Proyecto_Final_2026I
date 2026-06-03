#ifndef NIVEL_H
#define NIVEL_H

#include "pista.h"

class Nivel
{
public:
    Nivel();
    virtual ~Nivel();

    virtual void inicializar() = 0;
    virtual void actualizar(float dt) = 0;
    virtual void dibujar(QGraphicsScene *scene) = 0;
    virtual void procesarTecla(int tecla) = 0;
    virtual bool terminado() const = 0;

protected:
    Pista pista;
    float tiempoTranscurrido;
};

#endif
