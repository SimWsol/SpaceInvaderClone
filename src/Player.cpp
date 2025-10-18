#include "Player.h"

Player::Player(const char* imagePath, float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	playerTexture = LoadTexture(imagePath);
	speed = 300.f;
	screenWidth = 0;
	screenHeight = 0;
}

Player::~Player()
{
	UnloadTexture(playerTexture);
}

void Player::Draw()
{
	DrawTexture(playerTexture,
		(int)position.x,
		(int)position.y,
		WHITE);
}

void Player::SetScreenBounds(float width, float height)
{
	screenWidth = width;
	screenHeight = height;
}

void Player::Update()
{
	float dT = GetFrameTime();

	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
	{
		position.x -= speed * dT;
	}
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
	{
		position.x += speed * dT;
	}

	if (screenWidth > 0)
	{
		if (position.x < 0)
		{
			position.x = 0;
		}
		if (position.x > screenWidth - playerTexture.width)
		{
			position.x = screenWidth - playerTexture.width;
		}
	}
}