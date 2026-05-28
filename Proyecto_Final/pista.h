#ifndef PISTA_H
#define PISTA_H

#include <vector>
#include "zona.h"

class Pista
{
public:
    Pista(int ancho, int alto);
    ~Pista();

    Zona* zonaEn(int x, int y);
    void agregarZona(Zona *z);

    int getAncho();
    int getAlto();

private:
    std::vector<Zona*> zonas;
    int ancho;
    int alto;
};

#endif // PISTA_H
