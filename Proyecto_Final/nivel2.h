#ifndef NIVEL2_H
#define NIVEL2_H

#include "nivel.h"

class Nivel2 : public Nivel
{
public:
    Nivel2();

    void inicializar() override;
    void actualizar(float dt) override;
    void dibujar(QGraphicsScene *scene) override;
    void procesarTecla(int tecla) override;
    bool terminado() const override;

    void procesarBarrido();
    bool verificarLlegada(int xPiedra) const;
    bool verificarTiempo() const;
    float getTiempoRestante() const;

private:
    float tiempoLimite;
    float tiempoRestante;
    int metaX;
};

#endif
