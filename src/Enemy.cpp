#include "Enemy.h"

Enemy::Enemy(Vector2d startPosition, const char* texturePath)
{
	position = startPosition;
	isAlive = true;
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
		DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
	}
}

void Enemy::TakeDamage()
{
	isAlive = false;
}