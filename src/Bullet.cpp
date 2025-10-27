#include "Bullet.h"

Bullet::Bullet(Vector2d startPosition, Vector2d direction, float speed)
{
	position = startPosition;
	bulletSpeed = speed;
	bulletColor = YELLOW;

	velocity = direction.NormalizeVector().ScaleVector(bulletSpeed);
}

void Bullet::Update()
{
	float dT = GetFrameTime();

	Vector2d movement = velocity.ScaleVector(dT);
	position = position.SetVectorOffset(movement);
}

void Bullet::Draw()
{
	DrawRectangle((int)position.x - 2, (int)position.y - 10, 4, 10, bulletColor);
}

bool Bullet::IsOffScreen(float screenHeight)
{
	return position.y < -20;
}

