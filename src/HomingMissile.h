#pragma once
#include "Vector2d.h"
#include "Enemy.h"
#include "raylib.h"
#include <deque>

struct TrailParticle
{
	Vector2d position;
	float lifetime;
	float maxLifetime;
};

class HomingMissile
{
public:
	Vector2d position;
	Vector2d velocity;
	bool isActive;

	HomingMissile(Vector2d startPosition, float speed);

	void Update(Enemy* targetEnemy);
	void Draw();
	bool IsOffScreen(float screenHeight);

private:
	float missileSpeed;
	float maxTurnRate;
	Color missileColor;
	float trailTimer;
	float trailSpawnInterval;

	std::deque<TrailParticle> trail;

	void UpdateTrail();
	void DrawTrail();
};

