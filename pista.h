#ifndef PISTA_H
#define PISTA_H

#include "zona.h"

#include <memory>
#include <vector>

class Pista
{
public:
    Pista(int anchoInicial = 760, int altoInicial = 510);

    Zona *zonaEn(float x, float y) const;
    void agregarZona(std::unique_ptr<Zona> zona);
    void aplicarZona(PiedraCurling &piedra) const;
    void dibujar(QGraphicsScene *scene) const;
    int getAncho() const;
    int getAlto() const;

private:
    int ancho;
    int alto;
    std::vector<std::unique_ptr<Zona>> zonas;
};

#endif
