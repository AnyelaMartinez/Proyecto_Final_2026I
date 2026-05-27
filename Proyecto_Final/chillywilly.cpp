#include "chillywilly.h"

ChillyWilly::ChillyWilly() : Personaje()
{
    velocidad = 3.0f;
    agilidad = 1.5f;
    barriendoActivo = false;
    bonusVelocidad = 1.0f;
    duracionBonus = 0.0f;
    inestabilidad = 0.2f;
}

ChillyWilly::~ChillyWilly()
{
}

void ChillyWilly::actualizar(float dt)
{
    if (duracionBonus > 0)
    {
        duracionBonus = duracionBonus - dt;
        if (duracionBonus <= 0)
        {
            bonusVelocidad = 1.0f;
            duracionBonus = 0;
        }
    }
}

void ChillyWilly::mover(int dx, int dy)
{
    Vector2D nueva = pos;
    nueva.x = nueva.x + dx * velocidad * bonusVelocidad;
    nueva.y = nueva.y + dy * velocidad * bonusVelocidad;
    setPosicion(nueva);
}

void ChillyWilly::barrer()
{
    barriendoActivo = true;
}

void ChillyWilly::detenerBarrido()
{
    barriendoActivo = false;
}

bool ChillyWilly::estaBarriendo()
{
    return barriendoActivo;
}

void ChillyWilly::activarBonus(float seg)
{
    bonusVelocidad = 1.5f;
    duracionBonus = seg;
}
