#include "Enemy.h"

Enemy::Enemy(Vector2d startPosition, const char* texturePath, float scale)
{
	position = startPosition;
	isAlive = true;
	this->scale = scale;
	texture = LoadTexture(texturePath);
}

Enemy::~Enemy()
{
	UnloadTexture(texture);
}

void Enemy::Update()
{

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