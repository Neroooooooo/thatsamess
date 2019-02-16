#include "LevelSelector.h"
#include "Application.h"

#define MAX_LEVEL Application::getOptions()->MAX_LEVEL

LevelSelector::LevelSelector(sf::Vector2f *startingPosition)
{
	levelSelectorSprite = new sf::RectangleShape(sf::Vector2f(Application::getOptions()->WIDTH / 14, Application::Application::getOptions()->WIDTH / 14));
	levelSelectorSprite->setOrigin(levelSelectorSprite->getSize() / 2.0f);
	levelSelectorSprite->setFillColor(sf::Color::Transparent);
	levelSelectorSprite->setOutlineColor(sf::Color::White);
	levelSelectorSprite->setOutlineThickness(Application::getOptions()->HEIGHT / 64);
	levelSelectorSprite->setPosition(*startingPosition);
	selectedLevel = MAX_LEVEL;
}


LevelSelector::~LevelSelector()
{
}

void LevelSelector::pollEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
	}
}

void LevelSelector::update()
{
}

void LevelSelector::draw(sf::RenderWindow * window)
{
	window->draw(*levelSelectorSprite);
}
