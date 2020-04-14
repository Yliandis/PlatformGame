#include "EventManager.h"

EventManager::EventManager()
: m_currentState (StateType (0))
, m_hasFocus (true)
{
	loadBindings();
}

EventManager::~EventManager()
{
	for (auto& b_it : m_bindings)
	{
		delete b_it.second;
		b_it.second = nullptr;
	}
}

bool EventManager::addBinding(Binding* bind)
{
	std::string name = bind->m_name;
	auto found = m_bindings.find(name);
	if (found != m_bindings.end())
	{
		return false;
	}
	
	return m_bindings.emplace(name, bind).second;
}

bool EventManager::removeBinding(const std::string& name)
{
	auto found = m_bindings.find(name);
	if (found == m_bindings.end())
	{
		return false;
	}
	
	m_bindings.erase(found);
	return true;
}

bool EventManager::removeCallback(StateType state, const std::string& name)
{
	auto found = m_callbacks.find(state);
	if (found == m_callbacks.end())
	{
		return false;
	}
	auto found2 = found->second.find(name);
	if (found2 == found->second.end())
	{
		return false;
	}
	
	found->second.erase(name);
	return true;
}

void EventManager::setCurrentState(StateType state)
{
	m_currentState = state;
}

void EventManager::setFocus(bool focus)
{
	m_hasFocus = focus;
}

void EventManager::handleEvent(sf::Event event)
{
	for (auto& b_it : m_bindings)
	{
		Binding* bind = b_it.second;
		
		for (auto& e_it : bind->m_events)
		{
			EventType type = EventType(event.type);
			
			if (type != e_it.first)
			{
				continue;
			}
			
			switch (type)
			{
				case EventType::KeyDown:
				case EventType::KeyUp:
					if (event.key.code == e_it.second.m_code)
					{
						if (bind->m_details.m_keyCode == -1)
						{
							bind->m_details.m_keyCode = e_it.second.m_code;
						}
						++(bind->m_count);
					}
					break;
				
				case EventType::MButtonDown:
				case EventType::MButtonUp:
					if (event.mouseButton.button == e_it.second.m_code)
					{
						bind->m_details.m_mouse.x = event.mouseButton.x;
						bind->m_details.m_mouse.y = event.mouseButton.y;
						if (bind->m_details.m_keyCode == -1)
						{
							bind->m_details.m_keyCode = e_it.second.m_code;
						}
						++(bind->m_count);
					}
					break;
				
				case EventType::Resized:
					bind->m_details.m_size.x = event.size.width;
					bind->m_details.m_size.y = event.size.height;
					++(bind->m_count);
					break;
				
				default:
					++(bind->m_count);
					break;
			}
		}
	}
}

void EventManager::update()
{
	if (!m_hasFocus)
	{
		return;
	}
	
	for (auto& b_it : m_bindings)
	{
		Binding* bind = b_it.second;
		
		for (auto& e_it : bind->m_events)
		{
			switch (e_it.first)
			{
				case EventType::Keyboard:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_it.second.m_code)))
					{
						if (bind->m_details.m_keyCode == -1)
						{
							bind->m_details.m_keyCode = e_it.second.m_code;
						}
						++(bind->m_count);
					}
					break;
				
				case EventType::Mouse:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_it.second.m_code)))
					{
						if (bind->m_details.m_keyCode == -1)
						{
							bind->m_details.m_keyCode = e_it.second.m_code;
						}
						++(bind->m_count);
					}
					break;
				
				default:
					break;
			}
		}
		
		if (bind->m_count == bind->m_events.size())
		{
			auto stateCallbacks = m_callbacks.find(m_currentState);
			auto otherCallbacks = m_callbacks.find(StateType (0));
			
			if (stateCallbacks != m_callbacks.end())
			{
				auto found = stateCallbacks->second.find(bind->m_name);
				if (found != stateCallbacks->second.end())
				{
					found->second(&bind->m_details);
				}
			}
			
			if (otherCallbacks != m_callbacks.end())
			{
				auto found = otherCallbacks->second.find(bind->m_name);
				if (found != otherCallbacks->second.end())
				{
					found->second(&bind->m_details);
				}
			}
		}
		
		bind->m_count = 0;
		bind->m_details.reset();
	}
}

sf::Vector2i EventManager::getMousePos(sf::RenderWindow* window)
{
	if (window)
	{
		return sf::Mouse::getPosition(*window);
	}
	else
	{
		return sf::Mouse::getPosition();
	}
}

void EventManager::loadBindings()
{
	std::string delimiter = ":";
	
	std::ifstream file;
	file.open("media/config/keys.cfg");
	if (!file.is_open())
	{
		throw std::runtime_error ("EventManager::loadBindings() - Failed to load 'media/config/keys.cfg'");
	}
	
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream sline (line);
		
		std::string name;
		sline >> name;
		Binding* bind = new Binding (name);
		
		while (!sline.eof())
		{
			std::string event;
			sline >> event;
			
			std::size_t delim = event.find(delimiter);
			if (delim == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			
			int type = std::stoi(event.substr(0, delim));
			int info = std::stoi(event.substr(delim + delimiter.size()));
			
			bind->m_events.emplace_back(EventType(type), EventInfo(info));
		}
		
		if (!addBinding(bind))
		{
			delete bind;
			bind = nullptr;
		}
	}
	
	file.close();
}
