#pragma once
#include "Vector2d.h"
#include "raylib.h"
#include "Bullet.h"
#include "HomingMissile.h"
#include "Enemy.h"
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
	void UpdateMissiles();
	void HandleMissiles(Enemy* nearestEnemy);
	void TakeDamage();

	std::vector<Bullet>& GetBullets() { return bullets; }
	std::vector<HomingMissile>& GetHomingissiles() { return homingMissiles; }

	int GetHealth() { return health; }
	bool isAlive() { return health > 0; }
	Vector2d GetVelocity();

private:
	Texture2D playerTexture;
	float speed;
	float screenWidth;
	float screenHeight;
	int health;
	int maxHealth;
	Vector2d lastPosition;

	// Bullet management
	std::vector<Bullet> bullets;
	float shootCooldown;
	float timeSinceLastShot;

	// Homing missile management
	std::vector<HomingMissile> homingMissiles;
	float missileCooldown;
	float timeSinceLastMissile;
	int missileCount;

	void HandleMovement();
	void HandleShooting();
	void UpdateBullets();
	void DrawBullets();
	void DrawMissiles();
};