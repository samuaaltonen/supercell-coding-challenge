#include "MathUtils.h"

float VecLength(sf::Vector2f a)
{
    return sqrtf(a.x * a.x + a.y * a.y);
}

sf::Vector2f VecNormalize(sf::Vector2f a)
{
    float   length = VecLength(a);

    if (length == 0.f)
        return a;
    return sf::Vector2f(a.x / length, a.y / length);
}
