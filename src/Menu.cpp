#include "Menu.h"

Menu::Menu(const char* shipPaths[], int numShips, float screenWidth, float screenHeight)
{
	this->numShips = numShips;
	this->selectedShip = 0;
	this->spaceshipPaths = shipPaths;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	previewTextures = new Texture2D[numShips];
	for (int i = 0; i < numShips; i++)
	{
		previewTextures[i] = LoadTexture(shipPaths[i]);
	}
}

Menu::~Menu()
{
	for (int i = 0; i < numShips; i++)
	{
		UnloadTexture(previewTextures[i]);
	}
	delete[] previewTextures;
}

bool Menu::Update()
{
	HandleInput();

	return IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE);
}

void Menu::HandleInput()
{
	if (IsKeyPressed(KEY_ONE) && numShips > 0) selectedShip = 0;
	if (IsKeyPressed(KEY_TWO) && numShips > 1) selectedShip = 1;
	if (IsKeyPressed(KEY_THREE) && numShips > 2) selectedShip = 2;
	if (IsKeyPressed(KEY_FOUR) && numShips > 3) selectedShip = 3;
	if (IsKeyPressed(KEY_FIVE) && numShips > 4) selectedShip = 4;
}

void Menu::Draw()
{
    const char* titleText = "SELECT YOUR SPACESHIP";
    int titleWidth = MeasureText(titleText, 40);
    DrawText(titleText, (screenWidth - titleWidth) / 2, 100, 40, WHITE);

    const char* instructText = "Press 1-5 to select";
    int instructWidth = MeasureText(instructText, 20);
    DrawText(instructText, (screenWidth - instructWidth) / 2, 160, 20, GRAY);

    const char* startText = "Press ENTER to start";
    int startWidth = MeasureText(startText, 20);
    DrawText(startText, (screenWidth - startWidth) / 2, screenHeight - 100, 20, GREEN);

    DrawShipPreviews();
}

void Menu::DrawShipPreviews()
{
    float spacing = 140;
    float totalWidth = (numShips - 1) * spacing + previewTextures[0].width;

    float startX = (screenWidth - totalWidth) / 2;
    float shipY = screenHeight / 2 - 50; 

    for (int i = 0; i < numShips; i++)
    {
        float shipX = startX + i * spacing;

        // Highlight selected ship
        if (i == selectedShip)
        {
            DrawRectangle(shipX - 5, shipY - 5,
                previewTextures[i].width + 10,
                previewTextures[i].height + 10,
                YELLOW);
        }

        DrawTexture(previewTextures[i], shipX, shipY, WHITE);

        // Draw number below each ship
        const char* numText = TextFormat("%d", i + 1);
        int numWidth = MeasureText(numText, 30);
        DrawText(numText,
            shipX + (previewTextures[i].width - numWidth) / 2,
            shipY + previewTextures[i].height + 10,
            30,
            WHITE);
    }
}

const char* Menu::GetSelectedShipPath()
{
	return spaceshipPaths[selectedShip];
}

