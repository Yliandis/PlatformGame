#include "Game.h"

Game::Game()
: m_window ({816u, 624u}, "PlatformGame")
, m_stateManager (&m_context)
{
	m_context.m_window = &m_window;
	m_context.m_eventManager = m_window.getEventManager();
	
	m_stateManager.switchTo(StateType::Intro);
}

void Game::run()
{
	sf::Time updateTime = sf::seconds(1.f / 60.f); // 60 fps
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	
	while (m_window.isOpen())
	{
		processEvents();
		
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > updateTime)
		{
			timeSinceLastUpdate -= updateTime;
			update(updateTime);
		}
		
		render();
		lateUpdate();
	}
}

void Game::processEvents()
{
	m_window.processEvents();
}

void Game::update(sf::Time deltaTime)
{
	m_stateManager.update(deltaTime);
	m_window.update();
}

void Game::render()
{
	m_window.beginDraw();
	m_stateManager.draw();
	m_window.endDraw();
}

void Game::lateUpdate()
{
	m_stateManager.processRequests();
}
