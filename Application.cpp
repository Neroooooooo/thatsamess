#include "Application.h"
#include <fstream>
#include "Game.h"

Application * Application::s_instance = 0;

Application::Options * Application::s_options = 0;

Application * Application::getInstance()
{
	if (s_instance == 0)
	{
		s_instance = new Application();
	}

	return s_instance;
}

Application::Options * Application::getOptions()
{
	return s_options;
}

sf::RenderWindow * Application::getWindow() const
{
	return m_window;
}

sf::Font &Application::getFont()
{
	return (*m_font);
}

sf::Time Application::getRunningTime()
{
	return m_deltaClock.getElapsedTime();
}

sf::Time Application::getDeltaTime()
{
	return m_deltaTime;
}

void Application::Run()
{
	while (!closeFlag)
	{
		pollEvents();

		update();

		draw();
	}
}

void Application::close()
{
	delete s_instance;
}

Application::Application()
	:	closeFlag(false),
		m_window(nullptr)
{
	sf::ContextSettings windowSettings;

	if (loadOptions())
	{
		windowSettings.antialiasingLevel = 8;
		m_window = new sf::RenderWindow
		(
			sf::VideoMode(s_options->WIDTH, s_options->HEIGHT), // The size of the window
			"App",												// The name of the window
			sf::Style::Close | sf::Style::Titlebar,				// The style of the window
			windowSettings										// The context settings of the window
		);

		m_game = new Game;
		m_font = new sf::Font;
		m_font->loadFromFile("Franklin Gothic Condensed.ttf");
	}
	else
	{
		closeFlag = true;
	}
}

Application::~Application()
{
	delete s_options;
	delete m_window;
	delete m_game;
	delete m_font;
}

void Application::pollEvents()
{
	m_game->pollEvents();
	while (m_window->pollEvent(m_evnt))
	{
		if (m_evnt.type == sf::Event::Closed)
		{
			closeFlag = true;
		}
	}
}

void Application::update()
{
	static sf::Time helper;
	m_deltaTime = m_deltaClock.getElapsedTime() - helper;
	helper = m_deltaClock.getElapsedTime();

	m_game->update();
}

void Application::draw()
{
	m_window->clear();
	m_game->draw(m_window);
	m_window->display();
}

bool Application::loadOptions()
{
	std::fstream file("options.ini");
	std::string property = "";
	char dummy;

	float width;
	float height;
	int maxLevel;

	while (file >> property)
	{
		file >> dummy;
		if (property == "width")
		{
			file >> width;
		}
		else if (property == "height")
		{
			file >> height;
		}
		else if (property == "renders")
		{
			file >> maxLevel;
		}
		else
		{
			return false;
		}
	}

	s_options = new Options{ width, height, (35632 - maxLevel) };
	return true;
}
