#include "State_Platform.h"
#include "StateManager.h"

State_Platform::State_Platform(StateManager* stateManager)
: BaseState (stateManager)
, m_board ()
, m_player (3.1f * 48.f, 2.3f * 48.f)
, m_worldCollider ()
{
	sf::RenderWindow* window = m_stateManager->getContext()->m_window->getRenderWindow();
	
	m_view.reset({0.f, 0.f, float(window->getSize().x), float(window->getSize().y)});
}

void State_Platform::onCreate()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->addCallback(StateType::Platform, "Pause", &State_Platform::pause, this);
	eventManager->addCallback(StateType::Platform, "Back_state", &State_Platform::backToMenu, this);
	
	m_playerTexture.loadFromFile("media/textures/Player.png");
	m_player.setTexture(&m_playerTexture);
	
	loadLevel();
}

void State_Platform::onDestroy()
{
	EventManager* eventManager = m_stateManager->getContext()->m_eventManager;
	eventManager->removeCallback(StateType::Platform, "Pause");
	eventManager->removeCallback(StateType::Platform, "Back_state");
}

void State_Platform::activate()
{ }

void State_Platform::deactivate()
{ }

void State_Platform::update(sf::Time deltaTime)
{
	/*
	 * Player movement and collision
	 */
	
	m_player.update(deltaTime);
	
	sf::Vector2f direction;
	if (m_player.getCollider().checkCollision(m_board.getCollider(), direction, 0.f))
	{
		m_player.onCollision(direction);
	}
	
	if (m_player.getCollider().checkCollision(m_worldCollider, direction, 0.f))
	{
		if (direction.y > 0.f) // falling down
		{
			// player dies
			m_player.setPosition(m_board.getSpawn());
		}
	}
	
	updateView();
}

void State_Platform::draw()
{
	Window* window = m_stateManager->getContext()->m_window;
	
	window->getRenderWindow()->setView(m_view);
	
	window->draw(m_board);
	window->draw(m_player);
}

void State_Platform::loadLevel()
{
	m_board.loadFromFile("media/config/levels/Test.save");
	
	/*
	 * World bounds and collider
	 */
	
	sf::Vector2u boardSize = m_board.getSize();
	sf::Vector2f pixelBoardSize (boardSize.x * 48.f, boardSize.y * 48.f);
	
	// left bound
	m_worldBounds.emplace_back(sf::Vector2f (10.f, pixelBoardSize.y + 200.f));
	m_worldBounds.back().setPosition(-10.f, -200.f);
	
	// right bound
	m_worldBounds.emplace_back(sf::Vector2f (10.f, pixelBoardSize.y + 200.f));
	m_worldBounds.back().setPosition(pixelBoardSize.x, -200.f);
	
	// bottom bound
	m_worldBounds.emplace_back(sf::Vector2f (pixelBoardSize.x, 10.f));
	m_worldBounds.back().setPosition(0, pixelBoardSize.y);
	
	m_worldCollider.clean();
	m_worldCollider.pushBodies(m_worldBounds.begin(), m_worldBounds.end());
	
	/*
	 * Position and view
	 */
	
	m_player.setPosition(m_board.getSpawn());
	updateView();
}

void State_Platform::updateView()
{
	sf::Vector2f playerCenter = m_player.getPosition();
	// calculate the real center because the player's origin is its top left corner
	playerCenter.x += 24.f;
	playerCenter.y += 24.f;
	
	sf::Vector2u boardSize = m_board.getSize();
	sf::Vector2f pixelBoardSize (boardSize.x * 48.f, boardSize.y * 48.f);	
	
	sf::Vector2f viewCenter = m_view.getCenter();
	sf::Vector2f viewHalfSize = m_view.getSize() / 2.f;
	
	float leftLimit = viewCenter.x - viewHalfSize.x + 5 * 48.f;
	float rightLimit = viewCenter.x + viewHalfSize.x - 5 * 48.f;
	float topLimit = viewCenter.y - viewHalfSize.y + 4 * 48.f;
	float bottomLimit = viewCenter.y + viewHalfSize.y - 8 * 48.f;
	
	bool leftExcess = (viewCenter.x - viewHalfSize.x <= 0.f);
	bool rightExcess = (viewCenter.x + viewHalfSize.x >= pixelBoardSize.x);
	bool bottomExcess = (viewCenter.y + viewHalfSize.y >= pixelBoardSize.y);
	
	if (!leftExcess && playerCenter.x - 24.f < leftLimit) // view is too on the right
	{
		m_view.move(playerCenter.x - 24.f - leftLimit, 0.f); // move it to the left
		
		viewCenter.x += playerCenter.x - 24.f - leftLimit;
		leftExcess = (viewCenter.x - viewHalfSize.x <= 0.f);
		rightExcess = (viewCenter.x + viewHalfSize.x >= pixelBoardSize.x); // because it cames afterwards
	}
	if (leftExcess)
	{
		m_view.move(viewHalfSize.x - viewCenter.x, 0.f);
	}
	
	if (!rightExcess && playerCenter.x + 24.f > rightLimit) // view is too on the left
	{
		m_view.move(playerCenter.x + 24.f - rightLimit, 0.f); // move it to the right
		
		viewCenter.x += playerCenter.x + 24.f - rightLimit;
		rightExcess = (viewCenter.x + viewHalfSize.x >= pixelBoardSize.x);
	}
	if (rightExcess)
	{
		m_view.move(pixelBoardSize.x - viewCenter.x - viewHalfSize.x, 0.f);
	}
	
	// no top excess
	if (playerCenter.y - 24.f < topLimit) // view is too low
	{
		m_view.move(0.f, playerCenter.y - 24.f - topLimit); // move it up
	}
	
	if (!bottomExcess && playerCenter.y + 24.f > bottomLimit) // view is too high
	{
		m_view.move(0.f, playerCenter.y + 24.f - bottomLimit); // move it down
		
		viewCenter.y += playerCenter.y + 24.f - bottomLimit;
		bottomExcess = (viewCenter.y + viewHalfSize.y >= pixelBoardSize.y);
	}
	if (bottomExcess)
	{
		m_view.move(0.f, pixelBoardSize.y - viewCenter.y - viewHalfSize.y);
	}
}

/*****************
 * Event methods *
 ****************/

void State_Platform::backToMenu(EventDetails* details)
{
	m_stateManager->switchTo(StateType::LevelMenu);
}

void State_Platform::pause(EventDetails* details)
{
	m_stateManager->switchTo(StateType::Pause);
}
