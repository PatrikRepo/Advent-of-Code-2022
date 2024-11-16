#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <utility>

struct Node
{
	unsigned x = 0;
	unsigned y = 0;
	int steps = 0;
};

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
 		while(getline(input,line))
  	{
  		map.push_back(line);
  	}
  }
  input.close();
}
	
void updateMap(std::vector<std::string> &map)
{
	auto newMap = map;
	
	for(unsigned i=1; i<map.size()-1; i++)
	{
		for(unsigned j=1; j<map[0].size()-1; j++)
		{
			if(map[i][j] == '.')
			{
				continue;
			}
			if(map[i][j] >= 8)
			{
				map[i][j] = (map[i][j] == 8) ? '.' : map[i][j] - 8;
				newMap[i][j] = (newMap[i][j] == 8) ? '.' : newMap[i][j] - 8;
				
				unsigned newX = (j>1) ? j-1 : map[0].size()-2;
				if(newMap[i][newX] == '.')
				{
					newMap[i][newX] = 8;
				}
				else
				{
					newMap[i][newX] += 8;
				}
			}
			if(map[i][j] >= 4)
			{
				map[i][j] = (map[i][j] == 4) ? '.' : map[i][j] - 4;
				newMap[i][j] = (newMap[i][j] == 4) ? '.' : newMap[i][j] - 4;
				
				unsigned newY = (i+1 < map.size()) ? i+1 : 1;
				if(newMap[newY][j] == '.')
				{
					newMap[newY][j] = 4;
				}
				else
				{
					newMap[newY][j] += 4;
				}
			}
			if(map[i][j] >= 2)
			{
				map[i][j] = (map[i][j] == 2) ? '.' : map[i][j] - 2;
				newMap[i][j] = (newMap[i][j] == 2) ? '.' : newMap[i][j] - 2;
				
				unsigned newX = (j+1 < map[0].size()) ? j+1 : 1;
				if(newMap[i][newX] == '.')
				{
					newMap[i][newX] = 2;
				}
				else
				{
					newMap[i][newX] += 2;
				}
			}
			if(map[i][j] == 1)
			{
				map[i][j] = '.';
				newMap[i][j] = '.';
				
				unsigned newY = (i>0) ? i-1 : map.size()-2;
				if(newMap[newY][j] == '.')
				{
					newMap[newY][j] = 1;
				}
				else
				{
					newMap[newY][j] += 1;
				}
			}
		}
	}
	
	map = newMap;
}

uint64_t avoidBlizzards(Node &startNode, unsigned endX, unsigned endY, std::vector<std::string> &northMap, std::vector<std::string> &eastMap, std::vector<std::string> &southMap, std::vector<std::string> &westMap)
{
	uint64_t result = 0;
	
	auto oldNorth = northMap;
	auto oldEast = eastMap;
	auto oldSouth = southMap;
	auto oldWest = westMap;

	std::deque<Node> openList;
	openList.push_back(startNode);
	int lastStep = -1;
	
	while(!openList.empty())
	{
		Node node = openList.front();
		openList.pop_front();
		if(node.x == endX && node.y == endY)
		{
			result = node.steps;
			startNode = node;
			if(node.steps == lastStep)
			{
				northMap = oldNorth;
				eastMap = oldEast;
				southMap = oldSouth;
				westMap = oldWest;
			}
			break;
		}

		if(lastStep < node.steps)
		{
			auto newNorth = northMap;
			auto newEast = eastMap;
			auto newSouth = southMap;
			auto newWest = westMap;
			for(unsigned i=1; i<northMap.size()-1; i++)
			{
				for(unsigned j=1; j<northMap[0].size()-1; j++)
				{
					newNorth[(i>1) ? i-1 : northMap.size()-2][j] = northMap[i][j];
					newEast[i][(j+1<eastMap[0].size()-1) ? j+1 : 1] = eastMap[i][j];
					newSouth[(i+1<southMap.size()-1) ? i+1 : 1][j] = southMap[i][j];
					newWest[i][(j>1) ? j-1 : westMap[0].size()-2] = westMap[i][j];
				}
			}
			oldNorth = northMap;
			oldEast = eastMap;
			oldSouth = southMap;
			oldWest = westMap;
			
			northMap = newNorth;
			eastMap = newEast;
			southMap = newSouth;
			westMap = newWest;
			lastStep = node.steps;
		}
		
		std::vector<Node> newNodes;
		
		if(northMap[node.y][node.x] == '.' && eastMap[node.y][node.x] == '.' && southMap[node.y][node.x] == '.' && westMap[node.y][node.x] == '.')
		{
			Node newNode = node;
			newNode.steps++;
			newNodes.push_back(std::move(newNode));
		}
		if(node.y > 0 && northMap[node.y-1][node.x] == '.' && eastMap[node.y-1][node.x] == '.' && southMap[node.y-1][node.x] == '.' && westMap[node.y-1][node.x] == '.')
		{
			Node newNode = node;
			newNode.y--;
			newNode.steps++;
			newNodes.push_back(std::move(newNode));
		}
		if(northMap[node.y][node.x+1] == '.' && eastMap[node.y][node.x+1] == '.' && southMap[node.y][node.x+1] == '.' && westMap[node.y][node.x+1] == '.')
		{
			Node newNode = node;
			newNode.x++;
			newNode.steps++;
			newNodes.push_back(std::move(newNode));
		}
		if(node.y+1 < northMap.size() && northMap[node.y+1][node.x] == '.' && eastMap[node.y+1][node.x] == '.' && southMap[node.y+1][node.x] == '.' && westMap[node.y+1][node.x] == '.')
		{
			Node newNode = node;
			newNode.y++;
			newNode.steps++;
			newNodes.push_back(std::move(newNode));
		}
		if(northMap[node.y][node.x-1] == '.' && eastMap[node.y][node.x-1] == '.' && southMap[node.y][node.x-1] == '.' && westMap[node.y][node.x-1] == '.')
		{
			Node newNode = node;
			newNode.x--;
			newNode.steps++;
			newNodes.push_back(std::move(newNode));
		}
		
		for(auto &newNode:newNodes)
		{
			if(std::find_if(openList.begin(), openList.end(), [newNode](Node &oNode){ return newNode.x == oNode.x && newNode.y == oNode.y && newNode.steps == oNode.steps; }) == std::end(openList))
			{
				openList.push_back(newNode);
			}
		}
	}

	return result;
}

std::pair<uint64_t,uint64_t> avoidBlizzards(const std::vector<std::string> &map)
{
	std::pair<uint64_t,uint64_t> result = {0,0};
	
	auto northMap = map;
	auto eastMap = map;
	auto southMap = map;
	auto westMap = map;
	
	for(unsigned i=1; i<map.size()-1; i++)
	{
		for(unsigned j=1; j<map[0].size()-1; j++)
		{
			switch (map[i][j])
			{
				case '^':
				{
					eastMap[i][j] = '.';
					southMap[i][j] = '.';
					westMap[i][j] = '.';
					break;
				}
				case '>':
				{
					northMap[i][j] = '.';
					southMap[i][j] = '.';
					westMap[i][j] = '.';
					break;
				}
				case 'v':
				{
					northMap[i][j] = '.';
					eastMap[i][j] = '.';
					westMap[i][j] = '.';
					break;
				}
				case '<':
				{
					northMap[i][j] = '.';
					eastMap[i][j] = '.';
					southMap[i][j] = '.';
					break;
				}
			}
		}	
	}
	
	Node node;
	node.x = 1;
	
	result.first = avoidBlizzards(node, map[0].size()-2, map.size()-1, northMap, eastMap, southMap, westMap);
	avoidBlizzards(node, 1, 0, northMap, eastMap, southMap, westMap);
	result.second = avoidBlizzards(node, map[0].size()-2, map.size()-1, northMap, eastMap, southMap, westMap);
	
	return result;
}

int main()
{
	std::pair<uint64_t,uint64_t> result;

	std::vector<std::string> map; 
	
  parseInput(map);

	result = avoidBlizzards(map);

  std::cout << "resultA: " << result.first << '\n';
  std::cout << "resultB: " << result.second << std::endl;
  
  return 0;
}
