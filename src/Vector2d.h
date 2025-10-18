#pragma once
class Vector2d
{
public:
    float x;
    float y;

    float CalculateMagnitude();
    Vector2d SetVectorOffset(Vector2d inVectorToAdd);
    Vector2d ScaleVector(float inScalar);
    Vector2d VectorTowardsTarget(Vector2d inTargetVector);
    float DistanceToTarget(Vector2d inTargetedVector);
    Vector2d NormalizeVector();
};

