#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "WaveConfig.h"
#include <vector>
#include "HomingMissile.h"
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

	Enemy* GetNearestEnemyToPosition(Vector2d position);

	int GetCurrentWave();
	int GetEnemiesRemaining();

private:
	std::vector<Enemy*> enemies;
	float screenWidth;
	float screenHeight;
	int currentWave;

	Enemy* FindClosestEnemy(Vector2d position);

	void SpawnWave();
	bool AllEnemiesDefeated();
	WaveConfig GetWaveConfig(int waveNum);
};

