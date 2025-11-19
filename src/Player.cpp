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

	// Bullets
	shootCooldown = 0.2f;
	timeSinceLastShot = 0;

	// Missiles
	missileCooldown = 1.0f;
	timeSinceLastMissile = 0;
	missileCount = 10;
}

Player::~Player()
{
	UnloadTexture(playerTexture);
}

void Player::SetScreenBounds(float width, float height)
{
	screenWidth = width;
	screenHeight = height;
}

void Player::Update()
{
	timeSinceLastShot += GetFrameTime();
	timeSinceLastMissile += GetFrameTime();

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
	if (IsKeyPressed(KEY_SPACE) && timeSinceLastShot >= shootCooldown || IsKeyDown(KEY_SPACE) && timeSinceLastShot >= shootCooldown)
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

void Player::HandleMissiles(Enemy* nearestEnemy)
{
	if ((IsKeyPressed(KEY_M) || IsKeyPressed(KEY_RIGHT_SHIFT)) &&
		timeSinceLastMissile >= missileCooldown &&
		missileCount > 0)
	{
		Vector2d missileStartPos = {
			position.x + playerTexture.width / 2.0f,
			position.y
		};

		// SLOWER SPEED = better tracking
		HomingMissile newMissile(missileStartPos, 200.0f);  // Reduced from 300

		if (nearestEnemy != nullptr && nearestEnemy->isAlive)
		{
			Vector2d targetCenter = {
				nearestEnemy->position.x + nearestEnemy->GetWidth() / 2,
				nearestEnemy->position.y + nearestEnemy->GetHeight() / 2
			};
			Vector2d toTarget = missileStartPos.VectorTowardsTarget(targetCenter);
			newMissile.velocity = toTarget.NormalizeVector().ScaleVector(200.0f);
		}

		homingMissiles.push_back(newMissile);

		timeSinceLastMissile = 0;
		missileCount--;
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

void Player::UpdateMissiles()
{

	homingMissiles.erase(
		std::remove_if(homingMissiles.begin(), homingMissiles.end(),
			[this](HomingMissile& m) { return m.IsOffScreen(screenHeight); }),
		homingMissiles.end()
	);
}

void Player::Draw()
{
	DrawTexture(playerTexture,
		(int)position.x,
		(int)position.y,
		WHITE);

	DrawBullets();
	DrawMissiles();

	DrawText(TextFormat("Missiles: %d", missileCount), 10, 60, 20, YELLOW);
}

void Player::DrawBullets()
{
	for (auto& bullet : bullets)
	{
		bullet.Draw();
	}
}

void Player::DrawMissiles()
{
	for (auto& missile : homingMissiles)
	{
		missile.Draw();
	}
}