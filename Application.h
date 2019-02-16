#pragma once

class Game;
#include <SFML/Graphics.hpp>

// The main class that holds all the information about the program
class Application
{
	// Nested struct that holds the options that are to be read
	struct Options
	{
		float WIDTH;
		float HEIGHT;
		int MAX_LEVEL;
	};

public:
	// Getter used to receive a pointer to the instance of the class
	static Application *getInstance();

	static Options *getOptions();

	sf::RenderWindow *getWindow() const;

	sf::Font &getFont();

	sf::Time getRunningTime();
	sf::Time getDeltaTime();

	// Contains the main loop of the application
	void Run();

	// Saving and closing the program
	static void close();

private:
	// Constructor - used for the initialization of the application
	Application();

	// Destructor - used for clearing resources
	~Application();

	// Polling events
	void pollEvents();

	// Updating the logic
	void update();

	// Display the graphics
	void draw();

	// Reads the "options.ini" file and loads the options
	bool loadOptions();

public:

	

private:
	bool closeFlag;

	// Pointer to an instance of the nested struct above
	static Options* s_options;

	// Pointer to the instance of the class
	static Application *s_instance;

	// Pointer to the window
	sf::RenderWindow *m_window;

	// Used to handle the events
	sf::Event m_evnt;
	
	// Holding the game data
	Game *m_game;

	// Clock used to calculate the delta time
	sf::Clock m_deltaClock;

	// Used to stop the possible variation of game speed based on the computer performance
	sf::Time m_deltaTime;

	// The font all the texts are gonna be loaded in
	sf::Font *m_font;
};

