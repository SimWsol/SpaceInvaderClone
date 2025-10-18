#pragma once
#include "Vector2d.h"
#include "raylib.h"

class Player
{
public:
	Vector2d position;

	Player(const char* imagePath, float startX, float startY);
	~Player();

	void Draw();
	void Update();
	void SetScreenBounds(float width, float height);

private:
	Texture2D playerTexture;
	float speed;
	float screenWidth;
	float screenHeight;
};

