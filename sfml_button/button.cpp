#include "button.h"
#include "assets.h"

using namespace sf;


namespace {
const int TITLE_TEXT_SIZE = 12;
const sf::Color TEXT_COLOR_NORMAL = Color(0x22, 0x22, 0x22);
const sf::Color TEXT_COLOR_HOVERED = Color(0x00, 0x00, 0x00);
const sf::Color TEXT_COLOR_PRESSED = Color(0x40, 0x40, 0x40);
const sf::Color BACK_COLOR_NORMAL = Color(0xE0, 0xF8, 0xE0);
const sf::Color BACK_COLOR_HOVERED = Color(0xFF, 0xFF, 0xF0);
const sf::Color BACK_COLOR_PRESSED = Color(0xC8, 0xF0, 0xC8);
const sf::Color BORDER_COLOR_NORMAL = Color(0x80, 0xD0, 0x80);
const sf::Color BORDER_COLOR_HOVERED = Color(0x92, 0xE0, 0x92);
const sf::Color BORDER_COLOR_PRESSED = Color(0x50, 0xA0, 0x50);
const float BORDER_WIDTH = 3.f;
}


void SCustomButton::Init(SAssets& assets, const std::string& title)
{
	text.setFont(assets.fontMain);
	text.setCharacterSize(TITLE_TEXT_SIZE);
	text.setString(title);
	shape.setOutlineThickness(BORDER_WIDTH);
	text.setStyle(sf::Text::Bold);
	SetSize(CUSTOM_BUTTON_SIZE);
	SetPosition(Vector2f(0, 0));
	SetState(State::Normal);
}

void SCustomButton::SetTitle(std::string const& title)
{
	text.setString(title);
}

void SCustomButton::SetSize(Vector2f const& size)
{
	shape.setSize(size - 2.f * Vector2f(BORDER_WIDTH, BORDER_WIDTH));
}

bool SCustomButton::DoesHit(sf::Vector2f const& point) const
{
	return shape.getGlobalBounds().contains(point);
}

void SCustomButton::SetPosition(const Vector2f& point)
{
	shape.setPosition(BORDER_WIDTH + point.x, BORDER_WIDTH + point.y);
}

void SCustomButton::Draw(RenderWindow& window)
{
	FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(0.5f * textBounds.width, textBounds.height);
	text.setPosition(shape.getPosition() + 0.5f * shape.getSize());
	window.draw(shape);
	window.draw(text);
}

bool SCustomButton::OnEvent(const Event& event)
{
	auto mouseButtonHits = [&]() {
		Vector2f mousePoint(float(event.mouseButton.x), float(event.mouseButton.y));
		return (event.mouseButton.button == sf::Mouse::Left) && DoesHit(mousePoint);
	};
	auto mouseMoveHits = [&]() {
		Vector2f mousePoint(float(event.mouseMove.x), float(event.mouseMove.y));
		return DoesHit(mousePoint);
	};

	switch (event.type) {
	case sf::Event::MouseMoved:
		if (state != State::Pressed)
		{
			SetState(mouseMoveHits() ? State::Hovered : State::Normal);
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (mouseButtonHits())
		{
			SetState(State::Pressed);
			return true;
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (state == State::Pressed)
		{
			SetState(mouseButtonHits() ? State::Hovered : State::Normal);
			if (handler)
			{
				handler();
			}
			return true;
		}
		break;
	case sf::Event::MouseLeft:
		SetState(State::Normal);
		break;
	default:
		break;
	}

	return false;
}

void SCustomButton::SetState(SCustomButton::State newState)
{
	state = newState;
	switch (newState)
	{
	case State::Normal:
		text.setColor(TEXT_COLOR_NORMAL);
		shape.setFillColor(BACK_COLOR_NORMAL);
		shape.setOutlineColor(BORDER_COLOR_NORMAL);
		break;
	case State::Hovered:
		text.setColor(TEXT_COLOR_HOVERED);
		shape.setFillColor(BACK_COLOR_HOVERED);
		shape.setOutlineColor(BORDER_COLOR_HOVERED);
		break;
	case State::Pressed:
		text.setColor(TEXT_COLOR_PRESSED);
		shape.setFillColor(BACK_COLOR_PRESSED);
		shape.setOutlineColor(BORDER_COLOR_PRESSED);
		break;
	}
}
