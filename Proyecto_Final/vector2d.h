#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D sumar(Vector2D otro);
    Vector2D restar(Vector2D otro);
    Vector2D escalar(float k);
    float magnitud();
    float angulo();
};

#endif // VECTOR2D_H
