#include "Powerup.h"

Powerup::Powerup(Vector2d startPosition, PowerupType powerupType)
{
	position = startPosition;
	type = powerupType;
	isActive = true;
	fallSpeed = 100.0f;
	pulseTimer = 0;

	velocity = { 0, 1 };

	if (type == MISSILE_REFILL)
	{
		powerupColor = SKYBLUE;
	}
	else if (type == EXTRA_MISSILES)
	{
		powerupColor = PURPLE;
	}
	else if (type == HEALTH_PACK)
	{
		powerupColor = GREEN;
	}
}

void Powerup::Update()
{
	float dT = GetFrameTime();

	Vector2d movement = velocity.ScaleVector(fallSpeed * dT);
	position = position.SetVectorOffset(movement);
	pulseTimer += dT + 5.0f;
}

void Powerup::Draw()
{
	if (isActive)
	{
		float pulse = 1.0f + 0.3f * sinf(pulseTimer);
		float glowSize = 20.0f * pulse;

		// Glow
		DrawCircle((int)position.x, (int)position.y, glowSize, Fade(powerupColor, 0.3f));
		DrawCircle((int)position.x, (int)position.y, 15, Fade(powerupColor, 0.6f));

		// Core
		DrawCircle((int)position.x, (int)position.y, 12, powerupColor);
		DrawCircle((int)position.x, (int)position.y, 8, WHITE);

		if (type == MISSILE_REFILL)
		{
			DrawText("M", (int)position.x - 5, (int)position.y - 7, 15, DARKBLUE);
		}
		else if (type == EXTRA_MISSILES)
		{
			DrawText("M+", (int)position.x - 8, (int)position.y - 7, 12, DARKPURPLE);
		}
		else if (type == HEALTH_PACK)
		{
			DrawText("H", (int)position.x - 5, (int)position.y - 7, 15, DARKGREEN);
		}
	}
}

bool Powerup::IsOffScreen(float screenHeight)
{
	return position.y > screenHeight + 50;
}


