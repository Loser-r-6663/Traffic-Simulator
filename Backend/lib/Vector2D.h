#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
    double x;
    double y;

    Vector2D() : x(0), y(0) {}
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D operator*(double scalar) const
    {
        return Vector2D(x * scalar, y * scalar);
    }
};

#endif /* VECTOR2D_H */