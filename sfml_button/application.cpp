#include "application.h"
#include <string>


namespace {
const char BUTTON_EXAMPLE_LABEL[] = "\nPress\n  Me";
const sf::Vector2f BUTTON_EXAMPLE_POS = sf::Vector2f(350, 250);
const char WINDOW_TITLE_SUFFIX[] = " times pressed";

std::string GetApplicationTitle(int timesPressed)
{
	return std::to_string(timesPressed) + WINDOW_TITLE_SUFFIX;
}
}


SApplication::SApplication()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GetApplicationTitle(0))
{
	assets.Init();
	window.setFramerateLimit(DEFAULT_FPS);
	buttonExample.Init(assets, BUTTON_EXAMPLE_LABEL);
	buttonExample.SetPosition(BUTTON_EXAMPLE_POS);
	buttonExample.handler = [&]() {
		++timesPressed;
		window.setTitle(GetApplicationTitle(timesPressed));
	};
}

void SApplication::Exec()
{
    while (window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event))
        {
			if (buttonExample.OnEvent(event))
			{
				continue;
			}
            switch (event.type)
			{
			case sf::Event::Closed:
                window.close();
                break;
			default:
				break;
            }
		}
		window.clear(sf::Color::Black);
		buttonExample.Draw(window);
        window.display();
	}
}
