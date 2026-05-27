#ifndef PIEDRA_H
#define PIEDRA_H

#include "entidad.h"

class Piedra : public Entidad
{
public:
    Piedra();
    ~Piedra();

    void actualizar(float dt);
    void aplicarFuerza(float fuerza, float angulo);
    bool detenida();

    float getMasa();
    float getCoefRoce();
    void setCoefRoce(float r);

private:
    float masa;
    float coefRoce;
    bool enMovimiento;
};

#endif // PIEDRA_H
