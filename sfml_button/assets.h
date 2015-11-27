#pragma once

#include <SFML/Graphics.hpp>

static const char FONT_UBUNTU_TTF[] = "../fonts/Ubuntu-R.ttf";

struct SAssets
{
	sf::Font fontMain;

	void Init();
};
