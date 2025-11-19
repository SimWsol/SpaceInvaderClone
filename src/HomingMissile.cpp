#include "HomingMissile.h"

HomingMissile::HomingMissile(Vector2d startPosition, float speed)
{
    position = startPosition;
    missileSpeed = speed;
    maxTurnRate = 8.0f;
    isActive = true;
    missileColor = YELLOW;
    trailTimer = 0;
    trailSpawnInterval = 0.02f;  // Spawn trail particle every 0.02 seconds
}

void HomingMissile::Update(Enemy* targetEnemy)
{
    float deltaTime = GetFrameTime();

    if (targetEnemy != nullptr && targetEnemy->isAlive)
    {
        Vector2d targetCenter = {
            targetEnemy->position.x + targetEnemy->GetWidth() / 2,
            targetEnemy->position.y + targetEnemy->GetHeight() / 2
        };

        Vector2d toTarget = position.VectorTowardsTarget(targetCenter);
        float distanceToTarget = toTarget.CalculateMagnitude();

        if (distanceToTarget < 50.0f)
        {
            velocity = toTarget.NormalizeVector().ScaleVector(missileSpeed);
        }
        else
        {
            Vector2d desiredDirection = toTarget.NormalizeVector();
            Vector2d currentDirection = velocity.NormalizeVector();

            float dot = currentDirection.DotProduct(desiredDirection);
            if (dot > 1.0f) dot = 1.0f;
            if (dot < -1.0f) dot = -1.0f;

            float angleToTarget = acosf(dot);
            float turnRate = angleToTarget * 3.0f;

            if (turnRate > maxTurnRate * deltaTime)
            {
                turnRate = maxTurnRate * deltaTime;
            }

            float cross = currentDirection.CrossProduct(desiredDirection);
            float rotationAngle = turnRate * (cross > 0 ? 1.0f : -1.0f);

            float cosAngle = cosf(rotationAngle);
            float sinAngle = sinf(rotationAngle);

            float newX = currentDirection.x * cosAngle - currentDirection.y * sinAngle;
            float newY = currentDirection.x * sinAngle + currentDirection.y * cosAngle;

            velocity = Vector2d{ newX, newY }.NormalizeVector().ScaleVector(missileSpeed);
        }
    }

    Vector2d movement = velocity.ScaleVector(deltaTime);
    position = position.SetVectorOffset(movement);

    UpdateTrail();
}

void HomingMissile::UpdateTrail()
{
    float deltaTime = GetFrameTime();
    trailTimer += deltaTime;

    // Spawn new trail particle
    if (trailTimer >= trailSpawnInterval)
    {
        TrailParticle particle;
        particle.position = position;
        particle.maxLifetime = 0.5f;
        particle.lifetime = particle.maxLifetime;

        trail.push_back(particle);
        trailTimer = 0;
    }

    // Update existing particles
    for (auto& particle : trail)
    {
        particle.lifetime -= deltaTime;
    }

    // Remove dead particles
    while (!trail.empty() && trail.front().lifetime <= 0)
    {
        trail.pop_front();
    }
}

void HomingMissile::DrawTrail()
{
    // Draw trail particles oldest to newest
    for (const auto& particle : trail)
    {
        float alpha = particle.lifetime / particle.maxLifetime;
        float size = 3.0f * alpha;  // Shrink as it fades

       
        Color particleColor;
        if (alpha > 0.5f)
        {
            particleColor = ColorAlpha(ORANGE, alpha);
        }
        else
        {
            particleColor = ColorAlpha(RED, alpha * 2);
        }

        // Draw glow effect
        DrawCircle((int)particle.position.x, (int)particle.position.y,
            size + 4, Fade(ORANGE, alpha * 0.3f));
        DrawCircle((int)particle.position.x, (int)particle.position.y,
            size + 2, Fade(YELLOW, alpha * 0.5f));
        DrawCircle((int)particle.position.x, (int)particle.position.y,
            size, particleColor);
    }
}

void HomingMissile::Draw()
{
    if (isActive)
    {
        // Draw trail
        DrawTrail();

        // Draw missile body
        DrawCircle((int)position.x, (int)position.y, 10, Fade(YELLOW, 0.4f));
        DrawCircle((int)position.x, (int)position.y, 7, YELLOW);
        DrawCircle((int)position.x, (int)position.y, 5, GOLD);
        DrawCircle((int)position.x, (int)position.y, 3, WHITE);

        // Draw velocity direction indicator
        Vector2d direction = velocity.NormalizeVector().ScaleVector(25);
        DrawLineEx(
            { position.x, position.y },
            { position.x + direction.x, position.y + direction.y },
            4,
            Fade(RED, 0.8f)
        );
        DrawLineEx(
            { position.x, position.y },
            { position.x + direction.x, position.y + direction.y },
            2,
            ORANGE
        );
    }
}

bool HomingMissile::IsOffScreen(float screenHeight)
{
    if (position.y < -20 || position.y > screenHeight + 20)
    {
        return true;
    }
    return false;
}
