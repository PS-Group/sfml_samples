#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

static const sf::Vector2f CUSTOM_BUTTON_SIZE = sf::Vector2f(100, 100);

struct SAssets;

struct SCustomButton
{
	enum class State {
		Normal,
		Hovered,
		Pressed
	};

	void Init(SAssets &assets, std::string const& title);
	void SetTitle(std::string const& title);
	void SetSize(sf::Vector2f const& size);
	bool DoesHit(sf::Vector2f const& point) const;
	void SetPosition(sf::Vector2f const& point);

	void Draw(sf::RenderWindow &window);
	/// @returns true if event handled by button.
	bool OnEvent(sf::Event const& event);
	void SetState(State newState);

    sf::RectangleShape shape;
    sf::Text text;
	std::function<void()> handler;
	State state;
};
