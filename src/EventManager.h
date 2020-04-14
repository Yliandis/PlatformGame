#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include <stdexcept>

enum class EventType
{
	Closed = sf::Event::Closed,
	Resized = sf::Event::Resized,
	LostFocus = sf::Event::LostFocus,
	GainedFocus = sf::Event::GainedFocus,
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	
	Keyboard = sf::Event::Count + 1,
	Mouse
};

struct EventInfo
{
	EventInfo()
	: m_code (0)
	{ }
	
	EventInfo(int code)
	: m_code (code)
	{ }
	
	union
	{
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails
{
	EventDetails(std::string bindName)
	: m_name (bindName)
	{
		reset();
	}
	
	void reset()
	{
		m_size = {0u, 0u};
		m_mouse = {0, 0};
		m_keyCode = -1;
	}
	
	std::string m_name;
	
	sf::Vector2u m_size;
	sf::Vector2i m_mouse;
	int m_keyCode;
};

struct Binding
{
	Binding (std::string name)
	: m_name (name)
	, m_details (name)
	, m_count (0)
	{ }
	
	void bindEvent(EventType type, EventInfo info = EventInfo())
	{
		m_events.emplace_back(type, info);
	}
	
	std::string m_name;
	
	Events m_events;
	EventDetails m_details;
	
	unsigned m_count;
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager
{
	public:
		
		EventManager();
		~EventManager();
		
		bool addBinding(Binding*);
		bool removeBinding(const std::string&);
		
		template <typename T>
		bool addCallback(StateType, const std::string&, void(T::*)(EventDetails*), T*);
		bool removeCallback(StateType, const std::string&);
		
		void setCurrentState(StateType);
		void setFocus(bool);
		
		void handleEvent(sf::Event);
		void update();
		
		sf::Vector2i getMousePos(sf::RenderWindow* = nullptr);
		
	private:
		
		void loadBindings();
		
	private:
		
		Bindings m_bindings;
		Callbacks m_callbacks;
		StateType m_currentState;
		
		bool m_hasFocus;
};

template <typename T>
bool EventManager::addCallback(StateType state, const std::string& name, void(T::*func)(EventDetails*), T* instance)
{
	auto it = m_callbacks.emplace(state, CallbackContainer ()).first;
	auto temp = std::bind(func, instance, std::placeholders::_1);
	return it->second.emplace(name, temp).second;
}

#endif // EVENTMANAGER_H
