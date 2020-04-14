#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "Window.h"

struct SharedContext
{
	SharedContext()
	: m_window (nullptr)
	, m_eventManager (nullptr)
	{ }
	
	Window* m_window;
	EventManager* m_eventManager;
};

#endif // SHAREDCONTEXT_H
