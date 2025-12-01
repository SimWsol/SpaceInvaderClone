#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "WaveConfig.h"
#include <vector>
#include "HomingMissile.h"
#include "Player.h"
#include "EnemyBullet.h"

class EnemyManager
{
public:
	EnemyManager(float screenWidth, float screenHeight);
	~EnemyManager();

	void Update();
	void Draw();
	void CheckBulletCollisions(std::vector<Bullet>& bullets);
	void CheckMissileCollisions(std::vector<HomingMissile>& missiles);
	void UpdateMissileTargets(std::vector<HomingMissile>& missiles);
	void UpdateEnemyShooting(Player* player);
	void CheckEnemyBulletCollisions(Player* player);
	void CheckPowerupCollisions(Player* player);

	Enemy* GetNearestEnemyToPosition(Vector2d position);

	int GetCurrentWave();
	int GetEnemiesRemaining();

private:
	std::vector<Enemy*> enemies;
	std::vector<EnemyBullet> enemyBullets;
	std::vector<Powerup> powerups;
	float screenWidth;
	float screenHeight;
	int currentWave;

	Sound powerupPickupSound;

	Enemy* FindClosestEnemy(Vector2d position);

	Vector2d CalculatePredictiveShot(Vector2d shooterPos, Vector2d targetPos,
		Vector2d targetVel, float bulletSpeed);

	void UpdateEnemyBullets();
	void DrawEnemyBullets();

	void SpawnWave();
	bool AllEnemiesDefeated();
	WaveConfig GetWaveConfig(int waveNum);

	void SpawnPowerup(Vector2d position);
	void UpdatePowerups();
	void DrawPowerups();
};
