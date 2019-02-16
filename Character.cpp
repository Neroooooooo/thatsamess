#include "Character.h"
#include "Application.h"


Character::Character()
	:	m_velocity(0.0f),
		m_velocityCoeficient(300)
{
	m_sprite = new sf::RectangleShape(sf::Vector2f(Application::getOptions()->WIDTH / 32.0f, Application::getOptions()->HEIGHT / 18.0f));
	m_sprite->setOrigin(m_sprite->getSize() / 2.0f);
	m_sprite->setPosition(Application::getOptions()->WIDTH / 2, Application::getOptions()->HEIGHT / 2);
}


Character::~Character()
{
}

void Character::pollEvents()
{
			
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) &&
		m_sprite->getPosition().x >= 0.0f + m_sprite->getSize().x / 2
		)
	{
		m_sprite->move(-m_velocity, 0.0f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) &&
		m_sprite->getPosition().x <= Application::getOptions()->WIDTH - m_sprite->getSize().x / 2
		)
	{
		m_sprite->move(m_velocity, 0.0f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) &&
		m_sprite->getPosition().y >= 0.0f + m_sprite->getSize().y / 2
		)
	{
		m_sprite->move(0.0f, -m_velocity);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) &&
		m_sprite->getPosition().y <= Application::getOptions()->HEIGHT - m_sprite->getSize().y / 2
		)
	{
		m_sprite->move(0.0f, m_velocity);
	}
}

void Character::update()
{
	m_velocity = Application::getInstance()->getDeltaTime().asSeconds() * m_velocityCoeficient;
}

void Character::draw(sf::RenderWindow * window)
{
	window->draw(*m_sprite);
}

sf::RectangleShape * Character::getSprite() const
{
	return m_sprite;
}
