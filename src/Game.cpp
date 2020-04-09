#include "Game.h"

Game::Game()
: m_window ()
{ }

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	m_window.processEvents();
}

void Game::update()
{
	m_window.update();
}

void Game::render()
{
	m_window.beginDraw();
	m_window.endDraw();
}
