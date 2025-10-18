#include "Vector2d.h"
#include <cmath>

float Vector2d::CalculateMagnitude()
{
    float magnitudeSquared = x * x + y * y;
    float magnitude = sqrtf(magnitudeSquared);
    return magnitude;
}
