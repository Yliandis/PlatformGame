#include "Graph.h"

Node::Node(Level level, const sf::Texture& texture)
: m_level (level)
, m_sprite (texture)
{
	m_sprite.setOrigin(texture.getSize().x / 2.f, 12);
}

Level Node::getLevel() const
{
	return m_level;
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	target.draw(m_sprite, states);
}

/*********
 * Graph *
 ********/

Graph::Graph(const sf::Texture& pathTexture)
: m_pathTexture (pathTexture)
{ }

void Graph::setTexture(const sf::Texture& pathTexture)
{
	m_pathTexture = pathTexture;
}

void Graph::addNode(Node& newNode, float xPos, float yPos)
{
	for (const auto& node : m_nodes)
	{
		if (node.getLevel() == newNode.getLevel())
		{
			throw std::logic_error ("Graph::addNode() - Level already added");
		}
	}
	
	newNode.setPosition(xPos, yPos);
	
	m_nodes.push_back(newNode);
}

void Graph::makePath(Level level1, Level level2)
{
	auto hasLevel1 = [level1] (const Node& node) { return (node.getLevel() == level1); };
	auto hasLevel2 = [level2] (const Node& node) { return (node.getLevel() == level2); };
	
	auto found1 = std::find_if(m_nodes.begin(), m_nodes.end(), hasLevel1);
	auto found2 = std::find_if(m_nodes.begin(), m_nodes.end(), hasLevel2);
	
	if (found1 == m_nodes.end() || found2 == m_nodes.end())
	{
		throw std::logic_error ("Graph::makePath() - Levels not found");
	}
	
	auto verify1 = std::find(m_paths.begin(), m_paths.end(), std::make_pair(&*found1, &*found2));
	auto verify2 = std::find(m_paths.begin(), m_paths.end(), std::make_pair(&*found2, &*found1));
	
	if (verify1 != m_paths.end() || verify2 != m_paths.end())
	{
		throw std::logic_error ("Graph::makePath() - Path already added");
	}
	
	m_paths.emplace_back(&*found1, &*found2);
}

void Graph::calculatePaths()
{
	for (unsigned i = 0 ; i < m_pathPositions.size() ; ++i)
	{
		m_pathPositions.pop_back();
	}
	
	for (const auto& path : m_paths)
	{
		Node& node1 = *path.first;
		Node& node2 = *path.second;
		
		sf::Vector2f pos1 = node1.getPosition();
		sf::Vector2f pos2 = node2.getPosition();
		sf::Vector2f diff = pos2 - pos1;
		
		// calculation of the ellipse radius length
		if (diff.x != 0.f)
		{
			float x = sqrt(61504 / (64 + 961 * pow(diff.y / diff.x, 2)));
			if (diff.x < 0.f)
			{
				x = -x;
			}
			float y = diff.y / diff.x * x;
			
			pos1.x += x;
			pos1.y += y;
			pos2.x -= x;
			pos2.y -= y;
		}
		else
		{
			if (diff.y >= 0.f)
			{
				pos1.y += 8.f;
				pos2.y -= 8.f;
			}
			else
			{
				pos1.y -= 8.f;
				pos2.y += 8.f;
			}
		}
		
		m_pathPositions.emplace_back(pos1, pos2);
	}
}

std::vector<Level> Graph::moveTo(Level start, Level goal)
{
	/*std::vector<Level> closedList;
	std::priority_queue<sf::Vector2f> openList;
	openList.push_back(getLevelPos(start));
	
	while (!openList.empty())
	{
		sf::Vector2f u = openList.pop_back();
		
		if (u == getLevelPos(goal))
		{
			// reconstituer le chemin
			break;
		}
		
		for (voisin v de u)
		{
			if (!
		}
	}*/
	
	return std::vector<Level> ();
}

sf::Vector2f Graph::getLevelPos(Level level)
{
	auto hasLevel = [level] (const Node& node) { return (node.getLevel() == level); };
	auto found = std::find_if(m_nodes.begin(), m_nodes.end(), hasLevel);
	
	if (found == m_nodes.end())
	{
		throw std::logic_error ("Graph::getLevelPos() - Level not found");
	}
	
	return getPosition() + found->getPosition();
}

/*******************
 * Private methods *
 ******************/

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	states.transform *= getTransform();
	
	for (const auto& node : m_nodes)
	{
		target.draw(node, states);
	}
	
	sf::Sprite pathSprite (m_pathTexture);
	pathSprite.setOrigin(m_pathTexture.getSize().x / 2, m_pathTexture.getSize().y / 2);
	
	float pathTextureLength = sqrt(pow(m_pathTexture.getSize().x, 2) + pow(m_pathTexture.getSize().y, 2));
	float padding = 10.f; // TODO modify the padding to be related on the path angle and to respect perspective
	float pathLength = pathTextureLength + padding;
	
	for (const auto& path : m_pathPositions)
	{
		float xLength = path.second.x - path.first.x;
		float yLength = path.second.y - path.first.y;
		float length = sqrt(pow(xLength, 2) + pow(yLength, 2));
		
		unsigned nb = length / pathLength;
		float marge = (length - nb * pathLength) / 2.f;
		
		for (unsigned i = 0 ; i < nb ; ++i)
		{
			pathSprite.setPosition(path.first + (marge + pathLength * (i + 0.5f)) / length * (path.second - path.first));
			target.draw(pathSprite, states);
		}
	}
}
