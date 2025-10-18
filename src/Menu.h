#pragma once
#include "raylib.h"
class Menu
{
public:
	Menu(const char* shipPaths[], int numShips, float screenWidth, float screenHeight);
	~Menu();

	bool Update();
	void Draw();
	const char* GetSelectedShipPath();

private:
	const char** spaceshipPaths;
	Texture2D* previewTextures;
	int numShips;
	int selectedShip;
	float screenWidth;
	float screenHeight;

	void HandleInput();
	void DrawShipPreviews();
};

