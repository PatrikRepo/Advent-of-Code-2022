#include <iostream>
#include <fstream>
#include <vector>
#include <array>

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
	
uint64_t coverGround(std::vector<std::string> map)
{
	uint64_t result = 0;
	
	for(auto &line:map)
	{
		line = ".........." + line + "..........";
	}
	
	std::string eLine;
	
	for(unsigned i=0; i<map[0].size(); i++)
	{
		eLine += '.';
	}
	
	for(unsigned i=0; i<10; i++)
	{
		map.insert(map.begin(), eLine);
		map.push_back(eLine);
	}
	
	for(unsigned count=0; count<10; count++)
	{
		auto newMap = map;
		
		for(unsigned i=0; i<map.size(); i++)
		{
			for(unsigned j=0; j<map[i].size(); j++)
			{
				if(map[i][j] != '.')
				{
					if(map[i-1][j-1] == '.' && map[i-1][j] == '.' && map[i-1][j+1] == '.' && map[i][j-1] == '.' && map[i][j+1] == '.' && map[i+1][j-1] == '.' && map[i+1][j] == '.' && map[i+1][j+1] == '.')
					{	
						continue;
					}
					for(unsigned k=0; k<4; k++)
					{
						switch((count+k)%4)
						{
							case 0:
							{
								if(map[i-1][j-1] == '.' && map[i-1][j] == '.' && map[i-1][j+1] == '.')
								{
									k = 4;
									if(newMap[i-1][j] == '.')
									{
										newMap[i][j] = '.';
										newMap[i-1][j] = 'U';
									}
									else
									{
										if(newMap[i-1][j] == 'R')
										{
											newMap[i-1][j-1] = '#';
										}
										else if(newMap[i-1][j] == 'D')
										{
											newMap[i-2][j] = '#';
										}
										else if(newMap[i-1][j] == 'L')
										{
											newMap[i-1][i+1] = '#';
										}
										newMap[i-1][j] = 'C';
									}
								}
								break;
							}
							case 1:
							{
								if(map[i+1][j-1] == '.' && map[i+1][j] == '.' && map[i+1][j+1] == '.')
								{
									k = 4;
									if(newMap[i+1][j] == '.')
									{
										newMap[i][j] = '.';
										newMap[i+1][j] = 'D';
									}
									else
									{
										if(newMap[i+1][j] == 'R')
										{
											newMap[i+1][j-1] = '#';
										}
										else if(newMap[i+1][j] == 'U')
										{
											newMap[i+2][j] = '#';
										}
										else if(newMap[i+1][j] == 'L')
										{
											newMap[i+1][i+1] = '#';
										}
										newMap[i+1][j] = 'C';
									}
								}
								break;
							}
							case 2:
							{
								if(map[i-1][j-1] == '.' && map[i][j-1] == '.' && map[i+1][j-1] == '.')
								{
									k = 4;
									if(newMap[i][j-1] == '.')
									{
										newMap[i][j] = '.';
										newMap[i][j-1] = 'L';
									}
									else
									{
										if(newMap[i][j-1] == 'R')
										{
											newMap[i][j-2] = '#';
										}
										else if(newMap[i][j-1] == 'D')
										{
											newMap[i-1][j-1] = '#';
										}
										else if(newMap[i][j-1] == 'U')
										{
											newMap[i+1][i-1] = '#';
										}
										newMap[i][j-1] = 'C';
									}
								}
								break;
							}
							case 3:
							{
								if(map[i-1][j+1] == '.' && map[i][j+1] == '.' && map[i+1][j+1] == '.')
								{
									k = 4;
									if(newMap[i][j+1] == '.')
									{
										newMap[i][j] = '.';
										newMap[i][j+1] = 'R';
									}
									else
									{
										if(newMap[i][j+1] == 'L')
										{
											newMap[i][j+2] = '#';
										}
										else if(newMap[i][j+1] == 'D')
										{
											newMap[i-1][j+1] = '#';
										}
										else if(newMap[i][j+1] == 'U')
										{
											newMap[i+1][i+1] = '#';
										}
										newMap[i][j+1] = 'C';
									}
								}
								break;
							}
						}
					}
				}
			}
		}
		
		for(auto &line:newMap)
		{
			for(auto &c:line)
			{
				if(c == 'C')
				{
					c = '.';
				}
				else if(c != '.')
				{
					c = '#';
				}
			}	
		}
		
		map = newMap;
	}
	
	unsigned northBorder = 0;
	unsigned southBorder = 0;
	unsigned westBorder = 0;
	unsigned eastBorder = 0;
	
	for(unsigned i=0; i<map.size(); i++)
	{
		bool found = false;
		for(auto &c:map[i])
		{
			if(c == '#')
			{
				found = true;
				northBorder = i;
				break;
			}
		}
		if(found)
		{
			break;
		}
	}

	for(unsigned i=map.size()-1; i+1 > 0; i--)
	{
		bool found = false;
		for(auto &c:map[i])
		{
			if(c == '#')
			{
				found = true;
				southBorder = i;
				break;
			}
		}
		if(found)
		{
			break;
		}
	}
	
	for(unsigned i=0; i<map[0].size(); i++)
	{
		bool found = false;
		for(unsigned j=0; j<map.size(); j++)
		{
			if(map[j][i] == '#')
			{
				found = true;
				westBorder = i;
				break;
			}
		}
		if(found)
		{
			break;
		}
	}

	for(unsigned i=map[0].size()-1; i+1 > 0; i--)
	{
		bool found = false;
		for(unsigned j=0; j<map.size(); j++)
		{
			if(map[j][i] == '#')
			{
				found = true;
				eastBorder = i;
				break;
			}
		}
		if(found)
		{
			break;
		}
	}
	
	for(unsigned i=northBorder; i<=southBorder; i++)
	{
		for(unsigned j=westBorder; j<=eastBorder; j++)
		{
			if(map[i][j] == '.')
			{
				result++;
			}
		}
	}
	
	return result;
}

uint64_t elvesStop(const std::vector<std::string> &vMap)
{
	uint64_t result = 0;
	
	std::array<std::array<char,250>,250> map;
	for(auto &line:map)
	{
		for(auto &c:line)
		{
			c = '.';
		}
	}
	
	for(unsigned i=0; i<vMap.size(); i++)
	{
		for(unsigned j=0; j<vMap[0].size(); j++)
		{
			map[i+120][j+120] = vMap[i][j];
		}
	}
	
	unsigned goal = 0;
	
	for(auto &line:map)
	{
		for(auto &c:line)
		{
			if(c == '#')
			{
				goal++;
			}
		}
	}
	
	bool done = false;
	uint64_t count = 0;
	
	while(!done)
	{
		unsigned notMoving = 0;
		
		auto newMap = map;
		
		for(unsigned i=0; i<map.size(); i++)
		{
			for(unsigned j=0; j<map[i].size(); j++)
			{
				if(map[i][j] != '.')
				{
					if(map[i-1][j-1] == '.' && map[i-1][j] == '.' && map[i-1][j+1] == '.' && map[i][j-1] == '.' && map[i][j+1] == '.' && map[i+1][j-1] == '.' && map[i+1][j] == '.' && map[i+1][j+1] == '.')
					{	
						notMoving++;
						
						if(notMoving == goal)
						{
							result = count+1;
							done = true;
							break;
						}
						continue;
					}
					for(unsigned k=0; k<4; k++)
					{
						switch((count+k)%4)
						{
							case 0:
							{
								if(map[i-1][j-1] == '.' && map[i-1][j] == '.' && map[i-1][j+1] == '.')
								{
									k = 4;
									if(newMap[i-1][j] == '.')
									{
										newMap[i][j] = '.';
										newMap[i-1][j] = 'U';
									}
									else
									{
										if(newMap[i-1][j] == 'R')
										{
											newMap[i-1][j-1] = '#';
										}
										else if(newMap[i-1][j] == 'D')
										{
											newMap[i-2][j] = '#';
										}
										else if(newMap[i-1][j] == 'L')
										{
											newMap[i-1][i+1] = '#';
										}
										newMap[i-1][j] = 'C';
									}
								}
								break;
							}
							case 1:
							{
								if(map[i+1][j-1] == '.' && map[i+1][j] == '.' && map[i+1][j+1] == '.')
								{
									k = 4;
									if(newMap[i+1][j] == '.')
									{
										newMap[i][j] = '.';
										newMap[i+1][j] = 'D';
									}
									else
									{
										if(newMap[i+1][j] == 'R')
										{
											newMap[i+1][j-1] = '#';
										}
										else if(newMap[i+1][j] == 'U')
										{
											newMap[i+2][j] = '#';
										}
										else if(newMap[i+1][j] == 'L')
										{
											newMap[i+1][i+1] = '#';
										}
										newMap[i+1][j] = 'C';
									}
								}
								break;
							}
							case 2:
							{
								if(map[i-1][j-1] == '.' && map[i][j-1] == '.' && map[i+1][j-1] == '.')
								{
									k = 4;
									if(newMap[i][j-1] == '.')
									{
										newMap[i][j] = '.';
										newMap[i][j-1] = 'L';
									}
									else
									{
										if(newMap[i][j-1] == 'R')
										{
											newMap[i][j-2] = '#';
										}
										else if(newMap[i][j-1] == 'D')
										{
											newMap[i-1][j-1] = '#';
										}
										else if(newMap[i][j-1] == 'U')
										{
											newMap[i+1][i-1] = '#';
										}
										newMap[i][j-1] = 'C';
									}
								}
								break;
							}
							case 3:
							{
								if(map[i-1][j+1] == '.' && map[i][j+1] == '.' && map[i+1][j+1] == '.')
								{
									k = 4;
									if(newMap[i][j+1] == '.')
									{
										newMap[i][j] = '.';
										newMap[i][j+1] = 'R';
									}
									else
									{
										if(newMap[i][j+1] == 'L')
										{
											newMap[i][j+2] = '#';
										}
										else if(newMap[i][j+1] == 'D')
										{
											newMap[i-1][j+1] = '#';
										}
										else if(newMap[i][j+1] == 'U')
										{
											newMap[i+1][i+1] = '#';
										}
										newMap[i][j+1] = 'C';
									}
								}
								break;
							}
						}
					}
				}
			}
		}
		
		for(auto &line:newMap)
		{
			for(auto &c:line)
			{
				if(c == 'C')
				{
					c = '.';
				}
				else if(c != '.')
				{
					c = '#';
				}
			}	
		}
		
		map = newMap;
		count++;
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> map; 
	
  parseInput(map);

	resultA = coverGround(map);
 	resultB = elvesStop(map);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
