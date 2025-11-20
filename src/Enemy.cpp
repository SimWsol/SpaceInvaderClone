#include "Enemy.h"

Enemy::Enemy(Vector2d startPosition, const char* texturePath, float scale)
{
	position = startPosition;
	isAlive = true;
	this->scale = scale;
	texture = LoadTexture(texturePath);

	shootCooldown = 2.0f + (float)GetRandomValue(0, 300) / 100.0f;
	timeSinceLastShot = 0;
}

Enemy::~Enemy()
{
	UnloadTexture(texture);
}

void Enemy::Update()
{
	float dT = GetFrameTime();
	timeSinceLastShot += dT;
}

void Enemy::Draw()
{
	if (isAlive)
	{
		DrawTextureEx(texture,
			{ position.x, position.y },
			0.0f,
			scale,
			WHITE);
	}
}

void Enemy::TakeDamage()
{
	isAlive = false;
}

bool Enemy::ShouldShoot()
{
	if (timeSinceLastShot >= shootCooldown)
	{
		return true;
	}
	return false;
}

void Enemy::ResetShootCooldown()
{
	timeSinceLastShot = 0;
	shootCooldown = 2.0f + (float)GetRandomValue(0, 300) / 100.0f;
}

Vector2d Enemy::GetShootPosition()
{
	return {
		position.x + GetWidth() / 2,
		position.y + GetHeight()
	};
}





