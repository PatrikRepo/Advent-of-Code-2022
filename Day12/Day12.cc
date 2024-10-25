#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

struct Node
{
	unsigned x = 0;
	unsigned y = 0;
	unsigned steps = 0;
};

struct OrderNodes
{
	bool operator()(const Node &node1, const Node &node2){ return node1.steps < node2.steps; }
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
};

uint64_t traverseMap(const std::vector<std::string> &map, const Node &startNode)
{
	uint64_t result = UINT64_MAX;
	
	std::deque<Node> openList;
	openList.push_back(startNode);
	
	std::vector<Node> closedList;
	
	while(!openList.empty())
	{
		Node node = openList.front();
		openList.pop_front();

		if(map[node.y][node.x] == 'E')
		{
			result = node.steps;
			break;
		}
		closedList.push_back(node);
		
		std::vector<Node> newNodes;
		newNodes.reserve(4);
		
		if(node.y > 0)
		{
			char newHeight = map[node.y-1][node.x];
			if(newHeight == 'S' || newHeight == 'E')
			{
				newHeight = 'z';
			}
			
			char oldHeight = map[node.y][node.x];
			if(oldHeight == 'S')
			{
				oldHeight = 'z';
			}
			
			if(oldHeight + 1 >= newHeight)
			{
				Node newNode = node;
				newNode.y--;
				newNode.steps++;
				
				newNodes.push_back(newNode);
			}
		}
		
		if(node.x+1 < map[0].size())
		{
			char newHeight = map[node.y][node.x+1];
			if(newHeight == 'S' || newHeight == 'E')
			{
				newHeight = 'z';
			}
			
			char oldHeight = map[node.y][node.x];
			if(newHeight == 'S')
			{
				oldHeight = 'z';
			}
			
			if(oldHeight + 1 >= newHeight)
			{
				Node newNode = node;
				newNode.x++;
				newNode.steps++;
				
				newNodes.push_back(newNode);
			}
		}
		
		if(node.y+1 < map.size())
		{
			char newHeight = map[node.y+1][node.x];
			if(newHeight == 'S' || newHeight == 'E')
			{
				newHeight = 'z';
			}
			
			char oldHeight = map[node.y][node.x];
			if(newHeight == 'S')
			{
				oldHeight = 'z';
			}
			
			if(oldHeight + 1 >= newHeight)
			{
				Node newNode = node;
				newNode.y++;
				newNode.steps++;
				
				newNodes.push_back(newNode);
			}
		}
		
		if(node.x > 0)
		{
			char newHeight = map[node.y][node.x-1];
			if(newHeight == 'S' || newHeight == 'E')
			{
				newHeight = 'z';
			}
			
			char oldHeight = map[node.y][node.x];
			if(newHeight == 'S')
			{
				oldHeight = 'z';
			}
			
			if(oldHeight + 1 >= newHeight)
			{
				Node newNode = node;
				newNode.x--;
				newNode.steps++;
				
				newNodes.push_back(newNode);
			}
		}

		for(auto &newNode:newNodes)
		{
			auto it = std::find_if(openList.begin(), openList.end(), [newNode](Node oNode){ return newNode.x == oNode.x && newNode.y == oNode.y; });
			if(it != std::end(openList))
			{
				it->steps = (it->steps <= newNode.steps) ? it->steps : newNode.steps;
			}
			else
			{
				if(std::find_if(closedList.begin(), closedList.end(), [newNode](Node cNode){ return newNode.x == cNode.x && newNode.y == cNode.y; }) == std::end(closedList))
				{
					openList.push_back(newNode);
				}
			}
		}
		
		std::sort(openList.begin(), openList.end(), OrderNodes());
	}
	
	return result;
}

uint64_t traverseMap(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	for(unsigned i=0; i<map.size(); i++)
	{
		bool done = false;
		for(unsigned j=0; j<map[0].size(); j++)
		{
			if(map[i][j] == 'S')
			{
				done = true;
				Node startNode;
				startNode.x = j;
				startNode.y = i;
				result = traverseMap(map, startNode);
				break;
			}
		}
		if(done)
		{
			break;
		}
	}
	
	return result;
}

uint64_t newStartPoint(const std::vector<std::string> &map)
{
	uint64_t result = UINT64_MAX;
	
	for(unsigned i=0; i<map.size(); i++)
	{
		for(unsigned j=0; j<map[0].size(); j++)
		{
			if(map[i][j] == 'a')
			{
				Node startNode;
				startNode.x = j;
				startNode.y = i;
				uint64_t newResult = traverseMap(map, startNode);
				result = (newResult < result) ? newResult : result;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::string> map;
	
  parseInput(map);

	resultA = traverseMap(map);
 	resultB = newStartPoint(map);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;

  
  return 0;
}
