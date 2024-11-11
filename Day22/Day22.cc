#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &map, std::string &path)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
 		getline(input,line);
  	while(line != "")
  	{
			map.push_back(line);
			getline(input,line);
  	}
		getline(input,path);
  }
  input.close();
}

enum Orientation
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};
	
uint64_t traverseMap(const std::vector<std::string> &map, const std::string &path)
{
	uint64_t result = 0;
	
	size_t x = map[0].find_first_of(".");
	size_t y = 0;
	unsigned orientation = Orientation::RIGHT;
	
	for(unsigned i=0; i<path.size(); i++)
	{
		size_t endpos = path.find_first_of("RL",i);
		if(endpos == std::string::npos)
		{
			endpos = path.size();
		}
		
		unsigned steps = std::stoi(path.substr(i,endpos-i));
		
		switch(orientation)
		{
			case Orientation::RIGHT:
			{
				while(steps > 0)
				{
					if(x == map[y].size()-1)
					{
						size_t pos = map[y].find_first_not_of(" ");
						if(map[y][pos] == '#')
						{
							break;
						}
						else
						{
							x = pos;
						}
					}
					else if(map[y][x+1] == '#')
					{
						break;
					}
					else
					{
						x++;
					}
					steps--;
				}
				break;
			}
			case Orientation::DOWN:
			{
				while(steps > 0)
				{
					if(y == map.size()-1 || x >= map[y+1].size() || map[y+1][x] == ' ')
					{
						bool wrap = false;
						for(unsigned j=0; j<map.size(); j++)
						{
							if(map[j][x] == ' ')
							{
								continue;
							}
							if(map[j][x] == '.')
							{
								wrap = true;
								y = j;
							}
							break;
						}
						if(!wrap)
						{
							break;
						}
					}
					else if(map[y+1][x] == '#')
					{
						break;
					}
					else
					{
						y++;
					}
					steps--;
				}
				break;
			}
			case Orientation::LEFT:
			{
				while(steps > 0)
				{
					if(x == 0 || map[y][x-1] == ' ')
					{
						size_t pos = map[y].size()-1;
						if(map[y][pos] == '#')
						{
							break;
						}
						else
						{
							x = pos;
						}
					}
					else if(map[y][x-1] == '#')
					{
						break;
					}
					else
					{
						x--;
					}
					steps--;
				}
				break;
			}
			case Orientation::UP:
			{
				while(steps > 0)
				{
					if(y == 0 || x >= map[y-1].size() || map[y-1][x] == ' ')
					{
						bool wrap = false;
						for(unsigned j=map.size()-1; j>0; j--)
						{
							if(x >= map[j].size())
							{
								continue;
							}
							if(map[j][x] == '.')
							{
								wrap = true;
								y = j;
							}
							break;
						}
						if(!wrap)
						{
							break;
						}
					}
					else if(map[y-1][x] == '#')
					{
						break;
					}
					else
					{
						y--;
					}
					steps--;
				}
				break;
			}
		}
		
		i=endpos;
		
		if(i != path.size())
		{
			if(path[i] == 'R')
			{	
				orientation = (orientation+1)%4;
			}
			else
			{
				orientation = (orientation+3)%4;
			}
		}
	}	
	
	result = ((y+1)*1000) + ((x+1)*4) + orientation;
	
	return result;
}

uint64_t traverseCube(const std::vector<std::string> &map, const std::string &path)
{
	uint64_t result = 0;
	
	size_t x = map[0].find_first_of(".");
	size_t y = 0;
	unsigned orientation = Orientation::RIGHT;
	
	for(unsigned i=0; i<path.size(); i++)
	{
		size_t endpos = path.find_first_of("RL",i);
		if(endpos == std::string::npos)
		{
			endpos = path.size();
		}
		
		int steps = std::stoi(path.substr(i,endpos-i));
		
		while(steps > 0)
		{
			switch(orientation)
			{
				case Orientation::RIGHT:
				{
					if(x == map[y].size()-1)
					{
						size_t newY = 0;
						size_t newX = 0; 
						unsigned newOrientation = 0;
						
						if(y<50)
						{
							newY = 149-y;
							newX = 99;
							newOrientation = Orientation::LEFT;
						}
						else if(y<100)
						{
							newY = 49;
							newX = y+50;
							newOrientation = Orientation::UP;
						}
						else if(y<150)
						{
							newY = 149-y;
							newX = 149;
							newOrientation = Orientation::LEFT;
						}
						else
						{
							newY = 149;
							newX = y-100;
							newOrientation = Orientation::UP;
						}
						
						if(map[newY][newX] == '#')
						{
							steps = 0;
							break;
						}
						else
						{
							y = newY;
							x = newX;
							orientation = newOrientation;
						}
					}
					else if(map[y][x+1] == '#')
					{
						steps = 0;
						break;
					}
					else
					{
						x++;
					}
					steps--;
						
					break;
				}
				case Orientation::DOWN:
				{
					if(y == map.size()-1 || x >= map[y+1].size() || map[y+1][x] == ' ')
					{
						size_t newY = 0;
						size_t newX = 0; 
						unsigned newOrientation = 0;
						
						if(x<50)
						{
							newY = 0;
							newX = x+100;
							newOrientation = Orientation::DOWN;
						}
						else if(x<100)
						{
							newY = x+100;
							newX = 49;
							newOrientation = Orientation::LEFT;
						}
						else
						{
							newY = x-50;
							newX = 99;
							newOrientation = Orientation::LEFT;
						}
						
						if(map[newY][newX] == '#')
						{
							steps = 0;
							break;
						}
						else
						{
							y = newY;
							x = newX;
							orientation = newOrientation;
						}
					}
					else if(map[y+1][x] == '#')
					{
						steps = 0;
						break;
					}
					else
					{
						y++;
					}
					steps--;

					break;
				}
				case Orientation::LEFT:
				{
					if(x == 0 || map[y][x-1] == ' ')
					{
						size_t newY = 0;
						size_t newX = 0; 
						unsigned newOrientation = 0;
						
						if(y<50)
						{
							newY = 149-y;
							newX = 0;
							newOrientation = Orientation::RIGHT;
						}
						else if(y<100)
						{
							newY = 100;
							newX = y-50;
							newOrientation = Orientation::DOWN;
						}
						else if(y<150)
						{
							newY = 149-y;
							newX = 50;
							newOrientation = Orientation::RIGHT;
						}
						else
						{
							newY = 0;
							newX = y-100;
							newOrientation = Orientation::DOWN;
						}
						
						if(map[newY][newX] == '#')
						{
							steps = 0;
							break;
						}
						else
						{
							y = newY;
							x = newX;
							orientation = newOrientation;
						}
					}
					else if(map[y][x-1] == '#')
					{
						steps = 0;
						break;
					}
					else
					{
						x--;
					}
					steps--;

					break;
				}
				case Orientation::UP:
				{
					if(y == 0 || x >= map[y-1].size() || map[y-1][x] == ' ')
					{
						size_t newY = 0;
						size_t newX = 0; 
						unsigned newOrientation = 0;
						
						if(x<50)
						{
							newY = x+50;
							newX = 50;
							newOrientation = Orientation::RIGHT;
						}
						else if(x<100)
						{
							newY = x+100;
							newX = 0;
							newOrientation = Orientation::RIGHT;
						}
						else
						{
							newY = 199;
							newX = x-100;
							newOrientation = Orientation::UP;
						}
						
						if(map[newY][newX] == '#')
						{
							steps = 0;
							break;
						}
						else
						{
							y = newY;
							x = newX;
							orientation = newOrientation;
						}
					}
					else if(map[y-1][x] == '#')
					{
						steps = 0;
						break;
					}
					else
					{
						y--;
					}
					steps--;

					break;
				}
			}
		}
		
		i=endpos;
		
		if(i != path.size())
		{
			if(path[i] == 'R')
			{	
				orientation = (orientation+1)%4;
			}
			else
			{
				orientation = (orientation+3)%4;
			}
		}
	}	
	
	result = ((y+1)*1000) + ((x+1)*4) + orientation;
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> map; 
	std::string path;
	
  parseInput(map, path);

	resultA = traverseMap(map, path);
 	resultB = traverseCube(map, path);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
