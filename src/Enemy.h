#pragma once
#include "Vector2d.h"
#include "raylib.h"
class Enemy
{
public:
	Vector2d position;
	bool isAlive;

	Enemy(Vector2d startPosition, const char* texturePath, float scale = 2.0f);
	~Enemy();

	void Update();
	void Draw();
	void TakeDamage();

	float GetWidth() { return (float)texture.width * scale; }
	float GetHeight() { return (float)texture.height * scale; }

	// Collision box is smaller, scale to fit actual sprite
	float GetCollisionWidth() { return GetWidth() * 0.4f; }   // 60% of texture size
	float GetCollisionHeight() { return GetHeight() * 0.4f; }

	// Center the collision box on the sprite
	Vector2d GetCollisionPosition()
	{
		float offsetX = (GetWidth() - GetCollisionWidth()) / 2;
		float offsetY = (GetHeight() - GetCollisionHeight()) / 2;
		return { position.x + offsetX, position.y + offsetY };
	}

private:
	Texture2D texture;
	float scale;
};
