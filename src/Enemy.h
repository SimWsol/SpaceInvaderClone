#pragma once
#include "Vector2d.h"
#include "raylib.h"
class Enemy
{
public:
	Vector2d position;
	bool isAlive;

	Enemy(Vector2d startPosition, const char* texturePath);
	~Enemy();

	void Update();
	void Draw();
	void TakeDamage();

	float GetWidth() { return (float)texture.width; }
	float GetHeight() { return (float)texture.height; }

private:
	Texture2D texture;
};
