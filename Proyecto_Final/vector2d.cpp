#include "vector2d.h"
#include <cmath>

Vector2D::Vector2D()
{
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::sumar(Vector2D otro)
{
    return Vector2D(x + otro.x, y + otro.y);
}

Vector2D Vector2D::restar(Vector2D otro)
{
    return Vector2D(x - otro.x, y - otro.y);
}

Vector2D Vector2D::escalar(float k)
{
    return Vector2D(x * k, y * k);
}

float Vector2D::magnitud()
{
    return sqrt(x * x + y * y);
}

float Vector2D::angulo()
{
    return atan2(y, x);
}
