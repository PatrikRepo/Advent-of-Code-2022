#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>

struct Direction
{
	char orientation = 0;
	unsigned steps = 0;
};

void parseInput(std::vector<Direction> &directions)
{
	std::string line;
  std::ifstream input("input.txt");

  if(input.is_open())
  {	
		while(getline(input,line))
		{
			Direction direction;
			direction.orientation = line[0];
			direction.steps = std::stoi(line.substr(2));
			directions.push_back(direction);
		}
  }
  
  input.close();
}

uint64_t moveTail(const std::vector<Direction> &directions)
{
	uint64_t result = 0;
	
	std::array<std::array<unsigned,245>,278> map{0};
	
	size_t headX = 44;
	size_t headY = 263;
	size_t tailX = 44;
	size_t tailY = 263;
	
	map[tailY][tailX] = 1;
	
	for(auto &direction:directions)
	{
		for(unsigned i=0; i<direction.steps; i++)
		{
			switch(direction.orientation)
			{
				case 'U':
				{
					headY--;
					if(tailY - 2 == headY)
					{
						tailY = headY+1;
						tailX = headX;
					}
					break;
				}
				case 'R':
				{
					headX++;
					if(tailX + 2 == headX)
					{
						tailX = headX-1;
						tailY = headY;
					}
					break;
				}
				case 'D':
				{
					headY++;
					if(tailY + 2 == headY)
					{
						tailY = headY-1;
						tailX = headX;
					}
					break;
				}
				case 'L':
				{
					headX--;
					if(tailX - 2 == headX)
					{
						tailX = headX+1;
						tailY = headY;
					}
					break;
				}
			}
			map[tailY][tailX] = 1;
		}
	}
	
	for(auto &line:map)
	{
		for(auto i:line)
		{
			if(i>0)
			{	
				result++;
			}
		}
	}
	
	return result;
}

uint64_t manyKnots(const std::vector<Direction> &directions)
{
	uint64_t result = 0;
	
	std::array<std::array<unsigned,245>,278> map{0};
	
	std::array<std::pair<int,int>, 10> knots;
	
	for(auto &knot:knots)
	{
		knot = std::make_pair(44,263);
	}
	
	for(auto &direction:directions)
	{
		for(unsigned i=0; i<direction.steps; i++)
		{
			switch(direction.orientation)
			{
				case 'U':
				{
					knots[0].second--;
					break;
				}
				case 'R':
				{
					knots[0].first++;
					break;
				}
				case 'D':
				{
					knots[0].second++;
					break;
				}
				case 'L':
				{
					knots[0].first--;
					break;
				}
			}
			
			for(unsigned j=0; j<knots.size()-1; j++)
			{
				if(knots[j].first + 2 == knots[j+1].first)
				{
					knots[j+1].first--;
					if(knots[j].second < knots[j+1].second)
					{
						knots[j+1].second--;
					}
					else if(knots[j].second > knots[j+1].second)
					{
						knots[j+1].second++;
					}
				}
				else if(knots[j].second - 2 == knots[j+1].second)
				{
					knots[j+1].second++;
					if(knots[j].first < knots[j+1].first)
					{
						knots[j+1].first--;
					}
					else if(knots[j].first > knots[j+1].first)
					{
						knots[j+1].first++;
					}
				}
				else if(knots[j].first - 2 == knots[j+1].first)
				{
					knots[j+1].first++;
					if(knots[j].second < knots[j+1].second)
					{
						knots[j+1].second--;
					}
					else if(knots[j].second > knots[j+1].second)
					{
						knots[j+1].second++;
					}
				}
				else if(knots[j].second + 2 == knots[j+1].second)
				{
					knots[j+1].second--;
					if(knots[j].first < knots[j+1].first)
					{
						knots[j+1].first--;
					}
					else if(knots[j].first > knots[j+1].first)
					{
						knots[j+1].first++;
					}
				}
			}
			
			map[knots[9].second][knots[9].first] = 1;
		}
		
	}
	
	for(auto &line:map)
	{
		for(auto i:line)
		{
			if(i>0)
			{	
				result++;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<Direction> directions;
	
  parseInput(directions);

	resultA = moveTail(directions);
 	resultB = manyKnots(directions);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
