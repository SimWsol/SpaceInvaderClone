#include <raylib.h>
#include "Vector2d.h"
#include "Player.h"

int main()
{
	int screenWidth = 1280;
	int screenHeight = 1024;

	float halfScreenWidth = (float)(screenWidth / 2);
	float halfScreenHeight = (float)(screenHeight / 2);

	InitWindow(screenWidth, screenHeight, "Space Invaders");
	SetTargetFPS(60);

	Player player("resources/graphics/spaceship_orange.png", halfScreenWidth, screenHeight - 100);
	player.SetScreenBounds(screenWidth, screenHeight);
	

	while (!WindowShouldClose())
	{
		
		player.Update();

		BeginDrawing();
		ClearBackground(BLACK);

		player.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}