#pragma once

namespace sf
{
	class RenderWindow;
	class Time;
	class RectangleShape;
}

class Character
{
public:
	Character();
	~Character();

	// Polling events related to the player
	void pollEvents();

	// To update the character
	void update();

	// Drawing the plyer
	void draw(sf::RenderWindow *window);

	// Getter for the sprite
	sf::RectangleShape *getSprite() const;

private:
	// The graphical representation of the character
	sf::RectangleShape *m_sprite;

	// The velocity of the Character
	float m_velocity;

	// The velocity coeficient of the Character
	int m_velocityCoeficient;
};

