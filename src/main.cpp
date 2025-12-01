#include <raylib.h>
#include "Vector2d.h"
#include "Player.h"
#include "Menu.h"
#include "EnemyManager.h"
#include "Powerup.h"

enum GameState
{
	MENU,
	PLAYING
};

int main()
{
	int screenWidth = 1280;
	int screenHeight = 1024;

	float halfScreenWidth = (float)(screenWidth / 2);
	float halfScreenHeight = (float)(screenHeight / 2);

	InitWindow(screenWidth, screenHeight, "Space Invaders");
	SetTargetFPS(60);

	InitAudioDevice();

	Music bgMusic = LoadMusicStream("resources/music/bg_galaxy.wav");
	PlayMusicStream(bgMusic);
	SetMusicVolume(bgMusic, 0.5f);

	GameState currentState = MENU;

	const char* spaceshipPaths[5] = {
		"resources/graphics/spaceship_blue.png",
		"resources/graphics/spaceship_green.png",
		"resources/graphics/spaceship_orange.png",
		"resources/graphics/spaceship_pink.png",
		"resources/graphics/spaceship_red.png"
	};

	Menu menu(spaceshipPaths, 5, screenWidth, screenHeight);
	Player* player = nullptr;
	EnemyManager* enemyManager = nullptr;

	while (!WindowShouldClose())
	{
		DrawFPS(50, 100);

		if (currentState == MENU)
		{
			if (menu.Update())
			{
				player = new Player(menu.GetSelectedShipPath(),
					halfScreenWidth,
					screenHeight - 100);
				player->SetScreenBounds(screenWidth, screenHeight);

				enemyManager = new EnemyManager(screenWidth, screenHeight);

				currentState = PLAYING;
			}
		}
		else if (currentState == PLAYING)
		{
			if (!player->isAlive())
			{
				// Game Over
				DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2, 40, RED);
				DrawText("Press R to restart", screenWidth / 2 - 75, screenHeight / 2 + 50, 20, WHITE);

				if (IsKeyPressed(KEY_R))
				{
					delete player;
					delete enemyManager;

					player = new Player(menu.GetSelectedShipPath(),
						halfScreenWidth, screenHeight - 100);
					player->SetScreenBounds(screenWidth, screenHeight);
					enemyManager = new EnemyManager(screenWidth, screenHeight);
				}
			}
			else
			{
				Enemy* nearestEnemy = enemyManager->GetNearestEnemyToPosition(player->position);

				player->Update();
				player->HandleMissiles(nearestEnemy);

				enemyManager->UpdateMissileTargets(player->GetHomingissiles());
				enemyManager->Update();
				enemyManager->UpdateEnemyShooting(player);

				enemyManager->CheckBulletCollisions(player->GetBullets());
				enemyManager->CheckMissileCollisions(player->GetHomingissiles());
				enemyManager->CheckPowerupCollisions(player);
				enemyManager->CheckEnemyBulletCollisions(player);

				player->UpdateMissiles();
			}
		}

		UpdateMusicStream(bgMusic);
		BeginDrawing();
		ClearBackground(BLACK);

		if (currentState == MENU)
		{
			menu.Draw();
		}
		else if (currentState == PLAYING)
		{
			player->Draw();
			enemyManager->Draw();
		}

		EndDrawing();
	}

	if (player != nullptr)
	{
		delete player;
	}
	if (enemyManager != nullptr)
	{
		delete enemyManager;
	}

	UnloadMusicStream(bgMusic);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}