#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D
{
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }
    Vector2D operator-(const Vector2D &other) const
    {
        return {x - other.x, y - other.y};
    }
    Vector2D operator*(float scalar) const
    {
        return Vector2D(x * scalar, y * scalar);
    }
    Vector2D operator/(float scalar) const
    {
        if (scalar != 0.0f)
            return {x / scalar, y / scalar};
        return {0.0f, 0.0f};
    }
};

#endif /* VECTOR2D_H */