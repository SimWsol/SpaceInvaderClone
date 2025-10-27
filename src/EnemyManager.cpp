#include "EnemyManager.h"

EnemyManager::EnemyManager(float screenWidth, float screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	currentWave = 0;

	SpawnWave();
}

EnemyManager::~EnemyManager()
{
	for (auto enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
}

WaveConfig EnemyManager::GetWaveConfig(int waveNum)
{
	WaveConfig config;
	config.waveNumber = waveNum;

	switch (waveNum)
	{
	case 1:
		config.enemiesPerRow = 6;
		config.rows = 2;
		config.enemySpeed = 50.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";
		break;

	case 2:
		config.enemiesPerRow = 7;
		config.rows = 2;
		config.enemySpeed = 60.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";
		break;

	case 3:
		config.enemiesPerRow = 8;
		config.rows = 3;
		config.enemySpeed = 70.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";
		break;

	default:
		config.enemiesPerRow = 6 + waveNum;
		config.rows = 2 + (waveNum - 1) / 2;
		config.enemySpeed = 50.0f + waveNum * 10.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";

		// Maximums
		if (config.enemiesPerRow > 12) config.enemiesPerRow = 12;
		if (config.rows > 5) config.rows = 5;
		break;
	}

	return config;
}

void EnemyManager::SpawnWave()
{
	currentWave++;

	for (auto enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();

	WaveConfig config = GetWaveConfig(currentWave);

	float spacingX = 80.f;
	float spacingY = 60.f;

	// Temp texure to get the size for centering
	Texture2D tempTexture = LoadTexture(config.enemyTexture);
	float enemyWidth = tempTexture.width;
	UnloadTexture(tempTexture);

	float totalWidth = (config.enemiesPerRow - 1) * spacingX + enemyWidth;
	float startX = (screenWidth - totalWidth) / 2;
	float startY = 50;

	// Spawning the enemies in a "grid"
	for (int row = 0; row < config.rows; row++)
	{
		for (int col = 0; col < config.enemiesPerRow; col++)
		{
			Vector2d enemyPos = {
				startX + col * spacingX,
				startY + row * spacingY
			};

			enemies.push_back(new Enemy(enemyPos, config.enemyTexture));
		}
	}
}

void EnemyManager::Update()
{
	if (AllEnemiesDefeated())
	{
		SpawnWave();
	}

	for (auto enemy : enemies)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	for (auto enemy : enemies)
	{
		enemy->Draw();
	}

	DrawText(TextFormat("Wave: %d", currentWave), screenWidth - 150, 10, 20, WHITE);
	DrawText(TextFormat("Enemies: %d", GetEnemiesRemaining()), screenWidth - 150, 35, 20, WHITE);
}