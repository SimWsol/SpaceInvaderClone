#include "Player.h"
#include <iostream>

Player::Player(const char* imagePath, float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	playerTexture = LoadTexture(imagePath);
	speed = 300.f;
	screenWidth = 0;
	screenHeight = 0;

	shootCooldown = 0.1f;
	timeSinceLastShot = 0;
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

	DrawBullets();
}

void Player::SetScreenBounds(float width, float height)
{
	screenWidth = width;
	screenHeight = height;
}

void Player::Update()
{
	timeSinceLastShot += GetFrameTime();

	HandleMovement();
	HandleShooting();
	UpdateBullets();
}

void Player::HandleMovement()
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

void Player::HandleShooting()
{
	if (IsKeyPressed(KEY_SPACE) && timeSinceLastShot >= shootCooldown)
	{
		Vector2d bulletStartPos = {
			position.x + playerTexture.width / 2.0f,
			position.y
		};

		Vector2d shootDirection = { 0,-1 };

		bullets.push_back(Bullet(bulletStartPos, shootDirection, 500.0f));

		timeSinceLastShot = 0;
	}
}

void Player::UpdateBullets()
{
	int initialSize = bullets.size();

	for (auto& bullet : bullets)
	{
		bullet.Update();
	}

	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(),
			[this](Bullet& b) { return b.IsOffScreen(screenHeight); }),
		bullets.end()
	);

	if (initialSize != bullets.size())
	{
		std::cout << "Bullets removed! Before: " << initialSize
			<< " After: " << bullets.size() << std::endl;
	}
}

void Player::DrawBullets()
{
	for (auto& bullet : bullets)
	{
		bullet.Draw();
	}
}