#include "LevelBase.h"
#include "Application.h" 

int LevelBase::s_totalLevelCount = 100;

LevelBase::LevelBase()
	:	m_levelContainer(nullptr)
{
	m_levelContainer = new sf::RectangleShape(sf::Vector2f(Application::getOptions()->WIDTH*0.8f, Application::getOptions()->HEIGHT*0.8f));
	m_levelContainer->setFillColor(sf::Color(30.0f, 30.0f, 30.0f));
	m_levelContainer->setOrigin(m_levelContainer->getSize() / 2.0f);
}


LevelBase::~LevelBase()
{
	delete m_levelContainer;
}

void LevelBase::draw(sf::RenderWindow * window)
{
}

void LevelBase::update()
{

}
