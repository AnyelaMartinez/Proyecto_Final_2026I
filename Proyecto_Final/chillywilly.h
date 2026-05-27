#ifndef CHILLYWILLY_H
#define CHILLYWILLY_H

#include "personaje.h"

class ChillyWilly : public Personaje
{
public:
    ChillyWilly();
    ~ChillyWilly();

    void actualizar(float dt);
    void mover(int dx, int dy);

    void barrer();
    void detenerBarrido();
    bool estaBarriendo();

    void activarBonus(float seg);

private:
    bool barriendoActivo;
    float bonusVelocidad;
    float duracionBonus;
    float inestabilidad;
};

#endif // CHILLYWILLY_H
