#include <raylib.h>
#include "Vector2d.h"
#include "Player.h"
#include "Menu.h"

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
				currentState = PLAYING;
			}
		}
		else if (currentState == PLAYING)
		{
			player->Update();
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
		}

		EndDrawing();
	}

	if (player != nullptr) 
	{
		delete player;
	}

	CloseWindow();
	return 0;
}