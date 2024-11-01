#include <iostream>
#include <fstream>
#include <unordered_map>
#include <array>

struct Cube
{
	unsigned x = 0;
	unsigned y = 0;
	unsigned z = 0;
	unsigned sides = 6;
};

unsigned getKey(unsigned x, unsigned y, unsigned z)
{
	return x + (100*y) + (10000*z);
}

void parseInput(std::unordered_map<unsigned, Cube> &cubes)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
  		Cube cube;
  		size_t pos = line.find_first_of(",");
  		cube.x = std::stoi(line.substr(0,pos));
  		pos++;
  		size_t endpos = line.find_first_of(",",pos);
  		cube.y = std::stoi(line.substr(pos,endpos-pos));
  		pos = endpos+1;
  		cube.z = std::stoi(line.substr(pos));
  		unsigned key = getKey(cube.x, cube.y, cube.z);
  		cubes[key] = cube;
  	}
  }
  input.close();
}

uint64_t findSurfaceArea(std::unordered_map<unsigned, Cube> &cubes)
{
	uint64_t result = 0;
	
	for(auto it=cubes.begin(); it!=cubes.end(); it++)
	{
		unsigned key = getKey(it->second.x+1, it->second.y, it->second.z);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		key = getKey(it->second.x-1, it->second.y, it->second.z);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		key = getKey(it->second.x, it->second.y+1, it->second.z);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		key = getKey(it->second.x, it->second.y-1, it->second.z);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		key = getKey(it->second.x, it->second.y, it->second.z+1);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		key = getKey(it->second.x, it->second.y, it->second.z-1);
		if(cubes.count(key))
		{
			it->second.sides--;
		}
		result += it->second.sides;
	}
	
	return result;
}

uint64_t countOuterArea(std::array<std::array<std::array<char,22>,22>,22> &map, unsigned x, unsigned y, unsigned z)
{
	uint64_t result = 0;
	
	map[z][y][x] = 'X';
	
	if(x>0)
	{
		if(map[z][y][x-1] == '#')
		{
			result++;
		}
		else if(map[z][y][x-1] == '.')
		{
			result += countOuterArea(map, x-1, y, z);
		}
	}
	if(x<21)
	{
		if(map[z][y][x+1] == '#')
		{
			result++;
		}
		else if(map[z][y][x+1] == '.')
		{
			result += countOuterArea(map, x+1, y, z);
		}
	}
	if(y>0)
	{
		if(map[z][y-1][x] == '#')
		{
			result++;
		}
		else if(map[z][y-1][x] == '.')
		{
			result += countOuterArea(map, x, y-1, z);
		}
	}
	if(y<21)
	{
		if(map[z][y+1][x] == '#')
		{
			result++;
		}
		else if(map[z][y+1][x] == '.')
		{
			result += countOuterArea(map, x, y+1, z);
		}
	}
	if(z>0)
	{
		if(map[z-1][y][x] == '#')
		{
			result++;
		}
		else if(map[z-1][y][x] == '.')
		{
			result += countOuterArea(map, x, y, z-1);
		}
	}
	if(z<21)
	{
		if(map[z+1][y][x] == '#')
		{
			result++;
		}
		else if(map[z+1][y][x] == '.')
		{
			result += countOuterArea(map, x, y, z+1);
		}
	}
	
	return result;
}

uint64_t findOuterArea(std::unordered_map<unsigned, Cube> &cubes)
{
	uint64_t result = 0;
	
	std::array<std::array<std::array<char,22>,22>,22> map;
	
	for(unsigned i=0; i<22; i++)
	{
		for(unsigned j=0; j<22; j++)
		{
			for(unsigned k=0; k<22; k++)
			{
				if(i>0 && j>0 && k>0 && cubes.count(getKey(k-1,j-1,i-1)) == 1)
				{
					map[i][j][k] = '#';
				}
				else
				{
					map[i][j][k] = '.';
				}
			}
		}
	}
	
	result = countOuterArea(map, 0, 0, 0);
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::unordered_map<unsigned, Cube> cubes;
	
  parseInput(cubes);

	resultA = findSurfaceArea(cubes);
 	resultB = findOuterArea(cubes);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
