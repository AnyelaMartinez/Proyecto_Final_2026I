#include "vector2d.h"

#include <cmath>

Vector2D::Vector2D(float xValor, float yValor)
    : x(xValor), y(yValor)
{
}

Vector2D Vector2D::sumar(const Vector2D &v) const
{
    return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::multiplicar(float factor) const
{
    return Vector2D(x * factor, y * factor);
}

float Vector2D::magnitud() const
{
    return std::sqrt(x * x + y * y);
}

float Vector2D::distancia(const Vector2D &v) const
{
    const float dx = x - v.x;
    const float dy = y - v.y;
    return std::sqrt(dx * dx + dy * dy);
}
