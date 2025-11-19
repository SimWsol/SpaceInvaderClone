#include "EnemyManager.h"
#include <iostream>

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
		config.enemiesPerRow = 3;
		config.rows = 2;
		config.enemySpeed = 50.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";
		break;

	case 2:
		config.enemiesPerRow = 6;
		config.rows = 2;
		config.enemySpeed = 60.0f;
		config.enemyTexture = "resources/graphics/enemy_red.png";
		break;

	case 3:
		config.enemiesPerRow = 6;
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

	float enemyScale = 4.0f;

	// Temp texure to get the size for centering
	Texture2D tempTexture = LoadTexture(config.enemyTexture);
	float baseWidth = tempTexture.width;
	float baseHeight = tempTexture.height;
	UnloadTexture(tempTexture);

	// Calculate scaled dimensions
	float scaledWidth = baseWidth * enemyScale;
	float scaledHeight = baseHeight * enemyScale;

	// Spacing should be based on scaled size + gap
	float gapX = 20;  // Gap between enemies
	float gapY = 20;
	float spacingX = scaledWidth + gapX;
	float spacingY = scaledHeight + gapY;

	// Calculate total width for centering
	float totalWidth = (config.enemiesPerRow * scaledWidth) + ((config.enemiesPerRow - 1) * gapX);
	float startX = (screenWidth - totalWidth) / 2;
	float startY = 50;

	// Spawn enemies in grid formation
	for (int row = 0; row < config.rows; row++)
	{
		for (int col = 0; col < config.enemiesPerRow; col++)
		{
			Vector2d enemyPos = {
				startX + col * spacingX,
				startY + row * spacingY
			};

			enemies.push_back(new Enemy(enemyPos, config.enemyTexture, enemyScale));
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

void EnemyManager::CheckBulletCollisions(std::vector<Bullet>& bullets)
{
	for (auto& bullet : bullets)
	{
		for (auto enemy : enemies)
		{
			if (enemy->isAlive)
			{
				Vector2d bulletPos = bullet.position;
				float bulletWidth = 4;
				float bulletHeight = 10;

				// Use collision specific position and size
				if (bulletPos.CheckRectangleCollision(
					bulletWidth,
					bulletHeight,
					enemy->GetCollisionPosition(),
					enemy->GetCollisionWidth(),
					enemy->GetCollisionHeight()))
				{
					enemy->TakeDamage();
					bullet.position.y = -100;
					break;
				}
			}
		}
	}
}

void EnemyManager::UpdateMissileTargets(std::vector<HomingMissile>& missiles)
{
	// Update each missile with closest enemy target
	std::cout << "Updating " << missiles.size() << " missiles" << std::endl;
	for (auto& missile : missiles)
	{
		if (missile.isActive)
		{
			Enemy* target = FindClosestEnemy(missile.position);

			if (target != nullptr)
			{
				std::cout << "Missile has target at (" << target->position.x
					<< ", " << target->position.y << ")" << std::endl;
			}
			else
			{
				std::cout << "Missile has NO TARGET!" << std::endl;
			}

			missile.Update(target);
		}
	}
}

Enemy* EnemyManager::GetNearestEnemyToPosition(Vector2d position)
{
	return FindClosestEnemy(position);
}

Enemy* EnemyManager::FindClosestEnemy(Vector2d position)
{
	Enemy* closest = nullptr;
	float closestDistance = 999999.0f;

	for (auto enemy : enemies)
	{
		if (enemy->isAlive)
		{
			float distance = position.DistanceToTarget(enemy->position);
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closest = enemy;
			}
		}
	}

	return closest;
}

void EnemyManager::CheckMissileCollisions(std::vector<HomingMissile>& missiles)
{
	for (auto& missile : missiles)
	{
		if (!missile.isActive) continue;

		for (auto enemy : enemies)
		{
			if (enemy->isAlive)
			{
				Vector2d collisionPos = enemy->GetCollisionPosition();

				// Calculate enemy center
				Vector2d enemyCenter = {
					collisionPos.x + enemy->GetCollisionWidth() / 2,
					collisionPos.y + enemy->GetCollisionHeight() / 2
				};

				float distance = missile.position.DistanceToTarget(enemyCenter);

				if (distance < 30.0f)
				{
					enemy->TakeDamage();
					missile.isActive = false;
					missile.position.y = -100;
					break;
				}
			}
		}
	}
}

bool EnemyManager::AllEnemiesDefeated()
{
	for (auto enemy : enemies)
	{
		if (enemy->isAlive)
		{
			return false;
		}
	}
	return true;
}

int EnemyManager::GetCurrentWave()
{
	return currentWave;
}

int EnemyManager::GetEnemiesRemaining()
{
	int count = 0;
	for (auto enemy : enemies)
	{
		if (enemy->isAlive)
		{
			count++;
		}
	}
	return count;
}