#pragma once

#include <math.h>
#include <SFML/System.hpp>

float VecLength(sf::Vector2f a)
{
    return sqrtf(a.x*a.x + a.y*a.y);
}
