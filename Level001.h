#pragma once
#include "LevelBase.h"
class Level001 : public LevelBase
{
public:
	Level001();
	~Level001();

	void draw(sf::RenderWindow *window) override;
	void update() override;
};

