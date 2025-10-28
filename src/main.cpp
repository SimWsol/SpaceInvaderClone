#include <raylib.h>
#include "Vector2d.h"
#include "Player.h"
#include "Menu.h"
#include "EnemyManager.h"

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
		DrawFPS(50, 50);
		
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
			player->Update();
			enemyManager->Update();

			enemyManager->CheckBulletCollisions(player->GetBullets());
		}

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

	CloseWindow();
	return 0;
}