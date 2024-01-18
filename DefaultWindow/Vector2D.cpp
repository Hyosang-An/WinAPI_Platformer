#include "stdafx.h"
#include "Vector2D.h"
#include "Define.h"

Vector2D operator*(double scalar, const Vector2D& vec)
{
    return Vector2D(scalar * vec.x, scalar * vec.y);
}

Vector2D Vector2D::operator+(const tagInfo& other) const
{
    return Vector2D(x + other.fX, y + other.fY);
}
