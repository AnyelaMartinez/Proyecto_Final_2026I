#include "pista.h"

Pista::Pista(int ancho, int alto)
{
    this->ancho = ancho;
    this->alto = alto;
}

Pista::~Pista()
{
    for (int i = 0; i < (int)zonas.size(); i++)
    {
        delete zonas[i];
    }
    zonas.clear();
}

Zona* Pista::zonaEn(int x, int y)
{
    for (int i = 0; i < (int)zonas.size(); i++)
    {
        if (zonas[i]->contiene(x, y))
            return zonas[i];
    }
    return nullptr;
}

void Pista::agregarZona(Zona *z)
{
    zonas.push_back(z);
}

int Pista::getAncho()
{
    return ancho;
}

int Pista::getAlto()
{
    return alto;
}
