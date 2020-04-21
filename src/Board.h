#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Collider.h"

enum class Block
{
	Air = 0,
	Dirt,
	BlockCount
};

std::string getTextureName(Block);

class Board : public sf::Drawable
{
	public:
		
		Board();
		~Board();
		
		void clean();
		void loadFromFile(const std::string&);
		
		sf::Vector2u getSize() const;
		sf::Vector2f getSpawn() const;
		
		Collider& getCollider();
		
	private:
		
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		
	private:
	
	std::vector<std::vector<Block>> m_board;
	
	sf::Vector2u m_spawnPoint;
	
	std::map<Block, sf::Texture*> m_textures;
	std::vector<sf::RectangleShape> m_blocks;
	Collider m_collider;
};

#endif // BOARD_H
