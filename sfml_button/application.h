#pragma once

#include <SFML/Graphics.hpp>
#include "button.h"
#include "assets.h"

struct SApplication
{
    static const int DEFAULT_FPS = 60;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

	SApplication();
	void Exec();

	sf::RenderWindow window;
	SAssets assets;
	SCustomButton buttonExample;
	int timesPressed = 0;
};
