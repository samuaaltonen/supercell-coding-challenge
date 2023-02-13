#include "MathUtils.h"

float VecLength(sf::Vector2f a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}