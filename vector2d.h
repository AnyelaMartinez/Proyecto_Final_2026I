#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    float x;
    float y;

    Vector2D(float xValor = 0.0f, float yValor = 0.0f);
    Vector2D sumar(const Vector2D &v) const;
    Vector2D multiplicar(float factor) const;
    float magnitud() const;
    float distancia(const Vector2D &v) const;
};

#endif
