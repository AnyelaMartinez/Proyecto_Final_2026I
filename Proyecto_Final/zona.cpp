#include "zona.h"

Zona::Zona(int x, int y, int ancho, int alto)
{
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
    friccion = 0.05f;
}

Zona::~Zona()
{
}

bool Zona::contiene(int px, int py)
{
    if (px >= x && px <= x + ancho && py >= y && py <= y + alto)
        return true;
    return false;
}
