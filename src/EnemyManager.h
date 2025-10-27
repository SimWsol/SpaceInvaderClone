#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "WaveConfig.h"
#include <vector>
class EnemyManager
{
public:
	EnemyManager(float screenWidth, float screenHeight);
	~EnemyManager();

	void Update();
	void Draw();
	void CheckBulletCollisions(std::vector<Bullet>& bullets);

	int GetCurrentWave();
	int GetEnemiesRemaining();

private:
	std::vector<Enemy*> enemies;
	float screenWidth;
	float screenHeight;
	int currentWave;

	void SpawnWave();
	bool AllEnemiesDefeated();
	WaveConfig GetWaveConfig(int waveNum);
};

