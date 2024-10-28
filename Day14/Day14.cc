#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

void parseInput(std::vector<std::array<unsigned, 4>> &scanData, unsigned &scanBoundary)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{

			size_t pos = 0;
			size_t endpos = line.find_first_of(",");
			unsigned oldX = std::stoi(line.substr(0,endpos));

			pos = endpos + 1;
			endpos = line.find_first_of(" ",pos);
			unsigned oldY = std::stoi(line.substr(pos,endpos-pos));

			while(endpos != line.size())
			{	
				pos = endpos + 4;
				endpos = line.find_first_of(",",pos);
				unsigned newX = std::stoi(line.substr(pos,endpos-pos));
				
				pos = endpos + 1;
				endpos = line.find_first_of(" ",pos);
				if(endpos == std::string::npos)
				{
					endpos = line.size();
				}
				unsigned newY = std::stoi(line.substr(pos,endpos-pos));
				
				std::array<unsigned, 4> data;
				if(oldX == newX)
				{
					data[0] = 0;
					data[1] = newX;
					data[2] = oldY;
					data[3] = newY;
				}
				else
				{
					data[0] = 1;
					data[1] = newY;
					data[2] = oldX;
					data[3] = newX;
				}
				scanData.push_back(data);
				
				scanBoundary = (scanBoundary < std::max(oldY,newY)) ? std::max(oldY,newY) : scanBoundary;
				
				oldX = newX;
				oldY = newY;
			}
		}
	}
	input.close();
}

void drawMap(const std::vector<std::array<unsigned, 4>> &scanData, unsigned scanBoundary, std::vector<std::string> &map)
{
	unsigned minX = 340;
	unsigned maxX = 661;
	unsigned xRange = maxX - minX;
	unsigned minY = 0;
	unsigned maxY = scanBoundary + 3;
	unsigned yRange = maxY - minY;

	std::string line;
	line.reserve(xRange);
	map.reserve(yRange);

	for(unsigned i=0; i<xRange; i++)
	{
		line += '.';
	}
	for(unsigned i=0; i<yRange; i++)
	{
		map.push_back(line);
	}
	
	for(auto data : scanData)
	{
		if(data[0] == 0)
		{
			for(unsigned i=std::min(data[2],data[3]); i<=std::max(data[2],data[3]); i++)
			{
				map[i-minY][data[1]-minX] = '#';
			}
		}
		else
		{
			for(unsigned i=std::min(data[2],data[3]); i<=std::max(data[2],data[3]); i++)
			{
				map[data[1]-minY][i-minX] = '#';
			}
		}
	}
	
	map[0][500-minX] = '|';

}

uint64_t fillWithSand(std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	std::pair<unsigned, unsigned> sand = {0,0};
	unsigned source = map[0].find_first_of("|");

	bool done = false;
	
	while(!done)
	{	
		done = true;
		sand.first = source;
		sand.second = 0;
		
		while(sand.second < map.size()-1)
		{
			if(map[sand.second+1][sand.first] == '.')
			{
				sand.second++;
			}
			else if(map[sand.second+1][sand.first-1] == '.')
			{
				sand.second++;
				sand.first--;
			}
			else if(map[sand.second+1][sand.first+1] == '.')
			{
				sand.second++;
				sand.first++;
			}
			else
			{
				map[sand.second][sand.first] = 'X';
				if(sand.second != 0 || sand.first != source)
				{
					done = false;
				}
				break;
			}
		}
	}
	
	for(std::string &line : map)
	{
		for(char &element : line)
		{
			if(element == 'X')
			{
				result++;
			}
		}
	}
	
	return result;
}

uint64_t fillWithMuchSand(std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	for(auto &c:map.back())
	{
		c = '#';
	}
	
	result = fillWithSand(map);
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::array<unsigned, 4>> scanData;
	unsigned scanBoundary = 0;
	std::vector<std::string> map;

	parseInput(scanData, scanBoundary);

	drawMap(scanData, scanBoundary, map);
	
	resultA = fillWithSand(map);
	resultB = fillWithMuchSand(map);

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}

