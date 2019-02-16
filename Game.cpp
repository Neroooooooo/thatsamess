#include "Game.h"
#include "Character.h"
#include "Application.h"
#include "LevelBase.h"
#include "colors.h"	
#include "LevelSelector.h"

#define running_time Application::getInstance()->getRunningTime().asSeconds()

sf::Color colorRamping(int i, int increase = 3, HsvColor startingColor = HsvColor(70,100,130)); // + (0, 100, 100) for more saturation and brightness

Game::Game()
	:	m_character(nullptr),
		m_level(nullptr),
		m_state(State::menu),
		m_gameOutliner(nullptr),
		m_playRectangle(nullptr),
		m_playText(nullptr),
		m_creditRectangle(nullptr),
		m_creditText(nullptr),
		m_controlsText(nullptr),
		m_levelsIcons(50, sf::RectangleShape(sf::Vector2f(static_cast<float>(Application::getOptions()->WIDTH / 16), static_cast<float>(Application::Application::getOptions()->WIDTH / 16)))),
		levelSelector(nullptr)
{
	m_character = new Character;

	m_gameOutliner = new sf::RectangleShape(sf::Vector2f(Application::getOptions()->WIDTH, Application::getOptions()->HEIGHT));
	m_gameOutliner->setFillColor(sf::Color(18.0f, 18.0f, 18.0f));
	m_gameOutliner->setOrigin(m_gameOutliner->getSize() / 2.0f);
	m_gameOutliner->setPosition(Application::getOptions()->WIDTH / 2.0f, Application::getOptions()->HEIGHT / 2.0f);
}


Game::~Game()
{
	delete m_character;
	delete m_level;
	delete m_gameOutliner;
	delete m_playText;
	delete m_playRectangle;
	delete m_creditRectangle;
	delete m_creditText;
	delete m_controlsText;
	delete levelSelector;
}

void Game::pollEvents()
{
	m_character->pollEvents();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (m_playRectangle->getOutlineColor() == sf::Color(100, 100, 100))
		{
			modifyState(State::levelSelection);
		}
		else if (m_creditRectangle->getOutlineColor() == sf::Color(100, 100, 100))
		{
			m_state = State::credits;
		}
	}
	levelSelector->pollEvents();

}

void Game::update()
{
	m_character->update();
	if (m_state == State::menu)
	{
		initMenuStateRelatedFields();
		checkForMenuChoice(m_playRectangle, m_playText);
		checkForMenuChoice(m_creditRectangle, m_creditText);
		m_controlsText->setFillColor(sf::Color(255, 255, 255, static_cast<int>(abs(255 * sin(running_time + Application::getInstance()->getDeltaTime().asSeconds()) - sin(running_time)))));
	}
	else if (m_state == State::levelSelection)
	{
		
	}
}

void Game::draw(sf::RenderWindow * window)
{
	window->draw(*m_gameOutliner);
	if (m_state == State::menu)
	{
		window->draw(*m_playRectangle);
		window->draw(*m_creditRectangle);
		window->draw(*m_playText);
		window->draw(*m_creditText);
		window->draw(*m_controlsText);
		m_character->draw(window);
	}
	else if (m_state == State::levelSelection)
	{
		
		for (const auto level : m_levelsIcons)
		{
			window->draw(level);
		}
		levelSelector->draw(window);
	}
}

void Game::modifyState(State state)
{
	if (m_state == State::menu) {
		delete m_playRectangle;
		delete m_playText;

		delete m_creditRectangle;
		delete m_creditText;

		delete m_controlsText;
	}

	if (state == State::levelSelection)
	{
		initLevelSelectionRelatedFields();
	}

	m_state = state;
}

void Game::checkForMenuChoice(sf::RectangleShape * rectangleShape, sf::Text * text)
{
	if (m_character->getSprite()->getGlobalBounds().intersects((*rectangleShape).getGlobalBounds())
		|| m_character->getSprite()->getGlobalBounds().intersects((*text).getGlobalBounds())
		)
	{
		rectangleShape->setOutlineColor(sf::Color(100, 100, 100));
		text->setFillColor(sf::Color(100, 100, 100));
	}
	else
	{
		rectangleShape->setOutlineColor(sf::Color::White);
		text->setFillColor(sf::Color::White);
	}
}

void Game::initMenuStateRelatedFields()
{
	if (!m_playRectangle)
	{
		m_playRectangle = new sf::RectangleShape(sf::Vector2f(static_cast<float>(Application::getOptions()->HEIGHT / 10), static_cast<float>(Application::getOptions()->HEIGHT / 10)));
		m_playRectangle->setOrigin(m_playRectangle->getSize() / 2.0f);
		m_playRectangle->setFillColor(sf::Color::Transparent);
		m_playRectangle->setOutlineThickness(static_cast<float>(Application::getOptions()->HEIGHT / 100));
		m_playRectangle->setPosition(static_cast<float>((Application::getOptions()->WIDTH / 6) * 2), static_cast<float>((Application::getOptions()->HEIGHT / 5) + m_playRectangle->getSize().x));
	}
	if (!m_creditRectangle)
	{
		m_creditRectangle = new sf::RectangleShape(sf::Vector2f(static_cast<float>(Application::getOptions()->HEIGHT / 10), static_cast<float>(Application::getOptions()->HEIGHT / 10)));
		m_creditRectangle->setOrigin(m_creditRectangle->getSize() / 2.0f);
		m_creditRectangle->setFillColor(sf::Color::Transparent);
		m_creditRectangle->setOutlineThickness(static_cast<float>(Application::getOptions()->HEIGHT / 100));
		m_creditRectangle->setPosition(static_cast<float>((Application::getOptions()->WIDTH / 6) * 4), static_cast<float>(Application::getOptions()->HEIGHT / 5) + m_creditRectangle->getSize().x);
	}
	if (!m_playText)
	{
		m_playText = new sf::Text("PLAY", Application::getInstance()->getFont(), Application::getOptions()->HEIGHT / 20);
		m_playText->setOrigin(m_playText->getLocalBounds().width / 2, m_playText->getLocalBounds().height / 2);
		m_playText->setPosition(static_cast<float>((Application::getOptions()->WIDTH / 6) * 2), static_cast<float>((Application::getOptions()->HEIGHT / 5)));
	}
	if (!m_creditText)
	{
		m_creditText = new sf::Text("CREDIT", Application::getInstance()->getFont(), Application::getOptions()->HEIGHT / 20);
		m_creditText->setOrigin(m_creditText->getLocalBounds().width / 2, m_creditText->getLocalBounds().height / 2);
		m_creditText->setPosition(static_cast<float>((Application::getOptions()->WIDTH / 6) * 4), static_cast<float>((Application::getOptions()->HEIGHT / 5)));
	}
	if (!m_controlsText)
	{
		m_controlsText = new sf::Text
		(
			"WASD / ARROWS to move\n SPACE / ENTER to select\n\t\t  ESC to quit",
			Application::getInstance()->getFont(),
			Application::getOptions()->HEIGHT / 20
		);
		m_controlsText->setFillColor(sf::Color(30, 30, 30));
		m_controlsText->setOrigin(m_controlsText->getLocalBounds().width / 2, m_controlsText->getLocalBounds().height / 2);
		m_controlsText->setPosition(static_cast<float>(Application::getOptions()->WIDTH / 2), static_cast<float>((Application::getOptions()->HEIGHT / 5)*4));
	}
}

void Game::initLevelSelectionRelatedFields()
{
	float fragment = ((Application::getOptions()->WIDTH / 16) - (Application::getOptions()->WIDTH / 20)); // half the distance that should be between each 2 rectangles
	sf::Vector2f position = sf::Vector2f(fragment*10, 0.0f); // the initial position of the first element
	//std::cout << fragment; // ca sa vezi si tu ce imi da

	for (int j = 0; j < m_levelsIcons.size(); j++) // levels being an std::vector<sf::RectangleShape> with 30 elements
	{
		//levels[j].setOrigin(levels[j].getSize() / 2.0f); // set the origin of each rectangle to the middle
		if (j % 10 == 0) // reset the counter
		{
			position.x = fragment * 5; // reseting the position for the new line;
			position.y += 2*fragment + m_levelsIcons[j].getSize().x; // increasing the position on y axis
		}
		position.x += fragment;
		m_levelsIcons[j].setPosition(position);
		//std::cout << position.x << "  " << position.y << std::endl << std::endl;
		position.x += fragment + m_levelsIcons[j].getSize().x;

		m_levelsIcons[j].setFillColor(colorRamping(j));
	}

	sf::Vector2f initialPosition = m_levelsIcons[Application::getOptions()->MAX_LEVEL].getPosition();
	levelSelector = new LevelSelector(&initialPosition);
	
}

//sf::Color colorRamping(int i, int increase, sf::Color startingColor)
//{
//	int value = i * increase;
//	while (value)
//	{
//		if(startingColor.r <= 244 && startingColor.g == 244 && startingColor.b == 66)
//		{
//			startingColor.r--;
//		}
//		else if (startingColor.r == 244	&& startingColor.g <= 244 && startingColor.b == 66)
//		{	
//			startingColor.g++;
//		}
//		else if (startingColor.r == 244	&& startingColor.g == 66 && startingColor.b	<= 244)
//		{
//			startingColor.b--;
//		}
//		else if (startingColor.r <= 244	&& startingColor.g == 66 && startingColor.b == 244)
//		{
//			startingColor.r++;
//		}
//		else if (startingColor.r == 66 && startingColor.g <= 244 && startingColor.b == 244)
//		{
//			startingColor.g--;
//		}
//		else if (startingColor.r == 66 && startingColor.g == 244 && startingColor.b <= 244)
//		{
//			startingColor.b++;
//		}
//
//		value--;
//	}
//
//	return startingColor;
//}

sf::Color colorRamping(int i, int increase, HsvColor startingColor)
{
	startingColor.h += i * increase;

	if (Application::getOptions()->MAX_LEVEL >= i)
	{
		startingColor.s += 100;
		startingColor.v += 100;
	}

	RgbColor rgbcolor = HsvToRgb(startingColor);


	return sf::Color(rgbcolor.r, rgbcolor.g, rgbcolor.b);
}
