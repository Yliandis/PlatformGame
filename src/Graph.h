#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <cmath>

enum class Level;

class Node : public sf::Drawable, public sf::Transformable
{
	public:
		
		Node(Level, const sf::Texture&);
		
		Level getLevel() const;
		
	private:
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;
		
	private:
		
		Level m_level;
		sf::Sprite m_sprite;
};

class Graph : public sf::Drawable, public sf::Transformable
{
	public:
		
		Graph() = default;
		Graph(const sf::Texture&);
		
		void setTexture(const sf::Texture&);
		
		void addNode(Node&, float, float);
		void makePath(Level, Level);
		void calculatePaths();
		
		std::vector<Level> moveTo(Level, Level);
		sf::Vector2f getLevelPos(Level);
		
	private:
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
		
		std::vector<Node> m_nodes;
		
		std::vector<std::pair<Node*, Node*>> m_paths;
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> m_pathPositions;
		
		sf::Texture m_pathTexture;
};

#endif // GRAPH_H
