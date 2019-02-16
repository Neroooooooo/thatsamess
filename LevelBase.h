#pragma once

namespace sf
{
	class RenderWindow;
	class RectangleShape;
}

class LevelBase
{
public:
	LevelBase();
	~LevelBase();

	virtual void draw(sf::RenderWindow *window);
	virtual void update();

	static int s_totalLevelCount;

protected:
	sf::RectangleShape *m_levelContainer;

};
