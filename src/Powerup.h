#pragma once
#include "Vector2d.h"
#include "raylib.h"

enum PowerupType
{
	MISSILE_REFILL,
	EXTRA_MISSILES
};

class Powerup
{
public:
	Vector2d position;
	Vector2d velocity;
	PowerupType type;
	bool isActive;

	Powerup(Vector2d startPosition, PowerupType powerupType);

	void Update();
	void Draw();
	bool IsOffScreen(float screenHeight);

private:
	float fallSpeed;
	Color powerupColor;
	float pulseTimer;
};

