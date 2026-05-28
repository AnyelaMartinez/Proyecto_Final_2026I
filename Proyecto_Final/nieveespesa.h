#ifndef NIEVEESPESA_H
#define NIEVEESPESA_H

#include "zona.h"

class NieveEspesa : public Zona
{
public:
    NieveEspesa(int x, int y, int ancho, int alto);
    void aplicarEfecto(Piedra *p, float dt);

private:
    float factorFreno;
};

#endif // NIEVEESPESA_H
