#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_MainMenu::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::MainMenu, "Mouse_left", &State_MainMenu::mouseLeft, this);
	
	m_backgroundTexture.loadFromFile("media/textures/Background1.png");
	m_titleTexture.loadFromFile("media/textures/Title.png");
	m_buttonTexture.loadFromFile("media/textures/Button.png");
	m_font.loadFromFile("media/fonts/Seagram.ttf");
	
	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();
	
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_titleSprite.setTexture(m_titleTexture);
	m_titleSprite.setOrigin(m_titleTexture.getSize().x / 2.f, m_titleTexture.getSize().y / 2.f);
	m_titleSprite.setPosition(windowSize.x / 2.f, 162.f);
	
	m_buttonText[0].setString("Play");
	m_buttonText[1].setString("Settings");
	m_buttonText[2].setString("Credits");
	
	for (unsigned i = 0 ; i < 3 ; ++i)
	{
		m_buttonSprite[i].setTexture(m_buttonTexture);
		m_buttonSprite[i].setOrigin(m_buttonTexture.getSize().x / 2.f, m_buttonTexture.getSize().y / 2.f);
		m_buttonSprite[i].setPosition(windowSize.x / 2.f, 361.f + 100.f * i);
		
		m_buttonText[i].setFont(m_font);
		m_buttonText[i].setFillColor(sf::Color::Black);
		m_buttonText[i].setCharacterSize(30);
		sf::FloatRect textRect = m_buttonText[i].getLocalBounds();
		m_buttonText[i].setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
		m_buttonText[i].setPosition(m_buttonSprite[i].getPosition());
	}
}

void State_MainMenu::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::MainMenu, "Mouse_left");
}

void State_MainMenu::activate()
{
	if (m_stateManager->hasState(StateType::LevelMenu) && m_buttonText[0].getString() == "Play")
	{
		m_buttonText[0].setString("Resume");
		sf::FloatRect textRect = m_buttonText[0].getLocalBounds();
		m_buttonText[0].setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	}
}
		
void State_MainMenu::deactivate()
{ }

void State_MainMenu::update(sf::Time)
{ }

void State_MainMenu::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->draw(m_backgroundSprite);
	window->draw(m_titleSprite);
	for (unsigned i = 0 ; i < 3 ; ++i)
	{
		window->draw(m_buttonSprite[i]);
		window->draw(m_buttonText[i]);
	}
}

/*****************
 * Event methods *
 ****************/

void State_MainMenu::mouseLeft(EventDetails* details)
{
	sf::Vector2i pos = details->m_mouse;
	
	float halfX = m_buttonTexture.getSize().x / 2.f;
	float halfY = m_buttonTexture.getSize().y / 2.f;
	
	for (unsigned i = 0 ; i < 3 ; ++i)
	{
		sf::Vector2f buttonPos = m_buttonSprite[i].getPosition();
		
		if (pos.x >= buttonPos.x - halfX && pos.x <= buttonPos.x + halfX && pos.y >= buttonPos.y - halfY && pos.y <= buttonPos.y + halfY)
		{
			if (i == 0)
			{
				m_stateManager->switchTo(StateType::LevelMenu);
			}
			else if (i == 1)
			{
				m_stateManager->switchTo(StateType::Settings);
			}
			else if (i == 2)
			{
				m_stateManager->switchTo(StateType::Credits);
			}
		}
	}
}
