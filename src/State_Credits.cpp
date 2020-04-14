#include "State_Credits.h"
#include "StateManager.h"

State_Credits::State_Credits(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_Credits::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Credits, "Back_state", &State_Credits::backToMenu, this);
}

void State_Credits::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Credits, "Back_state");
}

void State_Credits::activate() {}
void State_Credits::deactivate() {}

void State_Credits::update(sf::Time) {}
void State_Credits::draw() {}

/*****************
 * Event methods *
 ****************/

void State_Credits::backToMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::MainMenu);
	m_stateManager->remove(StateType::Credits);
}
