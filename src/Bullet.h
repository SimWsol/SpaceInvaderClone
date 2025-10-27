#pragma once
#include "Vector2d.h"
#include "raylib.h"

class Bullet
{
public:
	Vector2d position;
	Vector2d velocity;

	Bullet(Vector2d startPosition, Vector2d direction, float speed);

	void Update();
	void Draw();
	bool IsOffScreen(float screenheight);

private:
	float bulletSpeed;
	Color bulletColor;
};

