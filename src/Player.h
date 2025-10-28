#pragma once
#include "Vector2d.h"
#include "raylib.h"
#include "Bullet.h"
#include <vector>

class Player
{
public:
	Vector2d position;

	Player(const char* imagePath, float startX, float startY);
	~Player();

	void Draw();
	void Update();
	void SetScreenBounds(float width, float height);

	std::vector<Bullet>& GetBullets() { return bullets; }

private:
	Texture2D playerTexture;
	float speed;
	float screenWidth;
	float screenHeight;

	// Bullet management
	std::vector<Bullet> bullets;
	float shootCooldown;
	float timeSinceLastShot;

	void HandleMovement();
	void HandleShooting();
	void UpdateBullets();
	void DrawBullets();
};