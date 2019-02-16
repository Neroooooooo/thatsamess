#pragma once

namespace sf {
	class RectangleShape;
	class RenderWindow;
	class Vector2f;
}

class LevelSelector
{
public:
	LevelSelector(sf::Vector2f *startingPosition);
	~LevelSelector();

	void pollEvents();
	void update();
	void draw(sf::RenderWindow *window);

private:
	sf::RectangleShape *levelSelectorSprite;
	int selectedLevel;
	int 
};

