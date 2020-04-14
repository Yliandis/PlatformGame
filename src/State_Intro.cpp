#include "State_Intro.h"
#include "StateManager.h"

State_Intro::State_Intro(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Intro::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Intro, "Intro_continue", &State_Intro::passIntro, this);
	
	m_timePassed = 0.f;
	
	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();
	
	m_introTexture.loadFromFile("media/textures/Title.png");
	m_font.loadFromFile("media/fonts/Arial.ttf");
	
	m_introSprite.setTexture(m_introTexture);
	m_text.setFont(m_font);
	
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.f, m_introTexture.getSize().y / 2.f);
	m_introSprite.setPosition(windowSize.x / 2.f, 0.f);
	
	m_text.setString("Press enter to continue");
	m_text.setCharacterSize(15);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	m_text.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void State_Intro::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Intro, "Intro_continue");
	eventManager->removeCallback(StateType::Intro, "Pause");
}

void State_Intro::activate() {}
void State_Intro::deactivate() {}

void State_Intro::update(sf::Time deltaTime)
{
	if (m_timePassed < 2.f)
	{
		sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();
		float increment = (windowSize.y - m_text.getLocalBounds().height - m_introTexture.getSize().y) / 4.f;
		m_timePassed += deltaTime.asSeconds();
		m_introSprite.setPosition(m_introSprite.getPosition().x, m_introSprite.getPosition().y + (increment * deltaTime.asSeconds()));
	}
}

void State_Intro::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->draw(m_introSprite);
	if (m_timePassed >= 2.f)
	{
		window->draw(m_text);
	}
}

/*****************
 * Event methods *
 ****************/

void State_Intro::passIntro(EventDetails* details)
{
	if (m_timePassed >= 2.f)
	{
		m_stateManager->switchTo(StateType::MainMenu);
		m_stateManager->remove(StateType::Intro);
	}
}
