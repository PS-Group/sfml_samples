#pragma once

#include <SFML/Graphics.hpp>

#ifdef _MSC_VER
static const char FONT_UBUNTU_TTF[] = "~build/fonts/Ubuntu-R.ttf";
#else
static const char FONT_UBUNTU_TTF[] = "../fonts/Ubuntu-R.ttf";
#endif

struct SAssets
{
	sf::Font fontMain;

	void Init();
};
