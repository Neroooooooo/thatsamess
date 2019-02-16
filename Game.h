#pragma once
#include <vector>

class Character;
class LevelBase;
class LevelSelector;
namespace sf
{
	class RenderWindow;
	class RectangleShape;
	class Text;
	class Time;
	class Clock;
}

enum State
{
	menu,
	levelSelection,
	inLevel,
	credits
};


class Game
{
public:
	Game();
	~Game();

	// Polling events related to the game
	void pollEvents();

	// Updating the game
	void update();

	// Drawing elemenets of the game
	void draw(sf::RenderWindow *window);

private:
	void modifyState(State state);

	// MENU STATE RELATED METHODS
	void initMenuStateRelatedFields();

	void checkForMenuChoice(sf::RectangleShape *rectangleShape, sf::Text *text);

	// LEVEL SELECTION STATE RELATED FIELDS
	void initLevelSelectionRelatedFields();

public:


private:
	// Pointer to the character controlled by the player
	Character *m_character;

	// Store the current level
	LevelBase *m_level;

	// The state of the game
	State m_state;

	// Bounds of the game
	sf::RectangleShape *m_gameOutliner;

	// MENU STATE RELATED FIELDS
		sf::RectangleShape *m_playRectangle;
		sf::Text *m_playText;

		sf::RectangleShape *m_creditRectangle;
		sf::Text *m_creditText;

		sf::Text *m_controlsText;

	// LEVEL SELECTION STATE RELATED FIELDS
		std::vector<sf::RectangleShape>m_levelsIcons;
		LevelSelector *levelSelector;
};

