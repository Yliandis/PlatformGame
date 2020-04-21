#include "Board.h"

std::string getTextureName(Block block)
{
	switch (block)
	{
		case Block::Dirt:
			return "media/textures/Dirt.png";
		
		default:
			return "";
	}
}

Board::Board()
: m_collider (Style::Separated)
{
	m_textures.emplace(Block::Air, nullptr);
	
	for (unsigned i = 1 ; i < unsigned(Block::BlockCount) ; ++i)
	{
		Block block = Block(i);
		sf::Texture* texture = new sf::Texture ();
		
		if (!texture->loadFromFile(getTextureName(block)))
		{
			throw std::runtime_error ("Board::Board() - Failed to load " + getTextureName(block));
		}
		
		m_textures.emplace(block, texture);
	}
}

Board::~Board()
{
	for (auto& it : m_textures)
	{
		if (it.second)
			delete it.second;
		it.second = nullptr;
	}
}

void Board::clean()
{
	m_board.resize(0);
	m_blocks.resize(0);
	m_collider.clean();
}

void Board::loadFromFile(const std::string& filename)
{
	clean();
	
	std::ifstream file;
	file.open(filename);
	if (!file.is_open())
	{
		throw std::runtime_error ("Board::loadFromFile() - Failed to load " + filename);
	}
	
	// reading board size
	std::string firstLine;
	std::getline(file, firstLine);
	std::stringstream sFirstLine (firstLine);
	
	unsigned sizeX;
	unsigned sizeY;
	sFirstLine >> sizeX >> sizeY;
	
	// resizing m_board vector
	for (unsigned i = 0 ; i < sizeX ; ++i)
	{
		m_board.push_back(std::vector<Block> ());
		
		for (unsigned j = 0 ; j < sizeY ; ++j)
		{
			m_board[i].push_back(Block::Air);
		}
	}
	
	// reading all blocks
	for (unsigned j = 0 ; j < sizeY ; ++j)
	{
		std::string line;
		std::getline(file, line);
		std::stringstream sline (line);
		
		for (unsigned i = 0 ; i < sizeX ; ++i)
		{
			unsigned blockNum;
			sline >> blockNum;
			
			m_board[i][j] = Block(blockNum);
			
			for (auto it : m_textures)
			{
				if (!it.second)
				{
					continue;
				}
				
				if (it.first == m_board[i][j])
				{
					m_blocks.emplace_back(sf::Vector2f (48.f, 48.f));
					m_blocks.back().setTexture(it.second);
					m_blocks.back().setPosition(i * 48.f, j * 48.f);
				}
			}
		}
	}
	
	// player spawn position
	file >> m_spawnPoint.x >> m_spawnPoint.y;
	
	file.close();
	
	m_collider.pushBodies(m_blocks.begin(), m_blocks.end());
}

sf::Vector2u Board::getSize() const
{
	if (m_board.empty())
	{
		return sf::Vector2u (0u, 0u);
	}
	else
	{
		return sf::Vector2u (m_board.size(), m_board[0].size());
	}
		
}

sf::Vector2f Board::getSpawn() const
{
	return {m_spawnPoint.x * 48.f, m_spawnPoint.y * 48.f};
}

Collider& Board::getCollider()
{
	return m_collider;
}

/*******************
 * Private methods *
 ******************/

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& block : m_blocks)
	{
		target.draw(block, states);
	}
}
