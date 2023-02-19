#include "MathHelper.h"

float MathHelper::GetDistance(const sf::Vector2f& Vector1, const sf::Vector2f& Vector2)
{
    sf::Vector2f DistanceVector = Vector2 - Vector1;
    float Distance = sqrt(DistanceVector.x * DistanceVector.x + DistanceVector.y * DistanceVector.y);

    return Distance;
}
