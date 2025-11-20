#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(Vector2d startPosition, Vector2d direction, float speed)
{
	position = startPosition;
	bulletSpeed = speed;
	bulletColor = RED;
	isActive = true;

	velocity = direction.NormalizeVector().ScaleVector(bulletSpeed);
}

void EnemyBullet::Update()
{
	float dT = GetFrameTime();
	
	Vector2d movement = velocity.ScaleVector(dT);
	position = position.SetVectorOffset(movement);
}

void EnemyBullet::Draw()
{
	if (isActive)
	{
		DrawCircle((int)position.x, (int)position.y, 4, bulletColor);
		DrawCircle((int)position.x, (int)position.y, 2, ORANGE);
	}
}

bool EnemyBullet::IsOffScreen(float screenHeight)
{
	return position.y > screenHeight + 20 || position.y < -20;
}


