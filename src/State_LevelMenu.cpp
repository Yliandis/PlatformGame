#include "State_LevelMenu.h"
#include "StateManager.h"

State_LevelMenu::State_LevelMenu(StateManager* stateManager)
: BaseState (stateManager)
{ }

void State_LevelMenu::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::LevelMenu, "Back_state", &State_LevelMenu::backToMenu, this);
	eventManager->addCallback(StateType::LevelMenu, "Mouse_left", &State_LevelMenu::mouseClick, this);
	
	m_pathTexture.loadFromFile("media/textures/Path.png");
	m_levelTexture.loadFromFile("media/textures/LevelGrass.png");
	
	sf::Vector2u windowSize = m_stateManager->getContext()->m_window->getRenderWindow()->getSize();
	m_graph.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_graph.setTexture(m_pathTexture);
	
	// TODO a load function to read nodes in a file
	Node node (Level::Egypte, m_levelTexture);
	m_graph.addNode(node, 0, 0);
	Node node2 (Level::Future, m_levelTexture);
	m_graph.addNode(node2, 0, 210);
	Node node3 (Level::Steampunk, m_levelTexture);
	m_graph.addNode(node3, 300, 150);
	Node node4 (Level::ImperialJapan, m_levelTexture);
	m_graph.addNode(node4, -100, -200);
	Node node5 (Level::Cthulhu, m_levelTexture);
	m_graph.addNode(node5, 150, -175);
	Node node6 (Level::MiddleAge, m_levelTexture);
	m_graph.addNode(node6, -250, 50);
	
	m_graph.makePath(Level::Egypte, Level::Future);
	m_graph.makePath(Level::Egypte, Level::Steampunk);
	m_graph.makePath(Level::Future, Level::Steampunk);
	m_graph.makePath(Level::ImperialJapan, Level::Egypte);
	m_graph.makePath(Level::ImperialJapan, Level::Cthulhu);
	m_graph.makePath(Level::MiddleAge, Level::Egypte);
	
	m_graph.calculatePaths();
}

void State_LevelMenu::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::LevelMenu, "Back_state");
	eventManager->removeCallback(StateType::LevelMenu, "Mouse_left");
}

void State_LevelMenu::activate() {}
void State_LevelMenu::deactivate() {}

void State_LevelMenu::update(sf::Time) {}

void State_LevelMenu::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->draw(m_graph);
}

/*****************
 * Event methods *
 ****************/

void State_LevelMenu::backToMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::MainMenu);
}

void State_LevelMenu::mouseClick(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Platform);
	// TODO move character on the right level before switch to the good level (m_currentLevel in sharedContext ?)
}
