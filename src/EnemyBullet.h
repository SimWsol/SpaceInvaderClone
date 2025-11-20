#pragma once
#include "Vector2d.h"
#include "raylib.h"

class EnemyBullet
{
public:
	Vector2d position;
	Vector2d velocity;
	bool isActive;

	EnemyBullet(Vector2d startPosition, Vector2d direction, float speed);

	void Update();
	void Draw();
	bool IsOffScreen(float screenHeight);

private:
	float bulletSpeed;
	Color bulletColor;
};

