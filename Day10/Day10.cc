#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <array>

void parseInput(std::vector<std::pair<bool,int>> &instructions)
{
	std::string line;
  std::ifstream input("input.txt");

  if(input.is_open())
  {	
		while(getline(input,line))
		{
			bool add = (line[0] == 'a') ? true : false;
			int val = 0;
			if(add)
			{
				size_t pos = line.find_first_of("-1234567890");
				val = std::stoi(line.substr(pos));
			}
			instructions.emplace_back(add,val);
		}
  }
  
  input.close();
}

uint64_t sumSignal(const std::vector<std::pair<bool,int>> &instructions)
{
	uint64_t result = 0;
	
	unsigned cycle = 0;
	unsigned reg = 1;
	unsigned counter = 20;
	
	for(auto &instruction:instructions)
	{
		cycle++;
		counter++;
		if(counter == 40)
		{
			result += cycle*reg;
			counter = 0;
		}
		if(instruction.first)
		{
			cycle++;
			counter++;
			if(counter == 40)
			{
				result += cycle*reg;
				counter = 0;
			}
			reg += instruction.second;
		}
		if(cycle >= 220)
		{
			break;
		}
	}
	
	return result;
}

void drawScreen(const std::vector<std::pair<bool,int>> &instructions)
{
	unsigned reg = 1;
	
	unsigned x = 0;
	unsigned y = 0;
	std::array<std::array<char,40>,6> screen;
	
	for(auto &instruction:instructions)
	{
		
		if(abs(reg-x) <= 1)
		{
			screen[y][x] = '#';
		}
		else
		{
			screen[y][x] = ' ';
		}
		x++;
		if(x == 40)
		{
			x = 0;
			if(y == 5)
			{
				break;
			}
			y++;
		}
		
		if(instruction.first)
		{
			if(abs(reg-x) <= 1)
			{
				screen[y][x] = '#';
			}
			else
			{
				screen[y][x] = ' ';
			}
			x++;
			if(x == 40)
			{
				x = 0;
				if(y == 5)
				{
					break;
				}
				y++;
			}
			reg += instruction.second;
		}
	}
	
	for(auto &line:screen)
	{
		for(auto c:line)
		{
			std::cout << c;
		}
		std::cout << '\n';
	}
}

int main()
{
	uint64_t resultA = 0;

	std::vector<std::pair<bool,int>> instructions;
	
  parseInput(instructions);

	resultA = sumSignal(instructions);
	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << '\n';
 	drawScreen(instructions);
  
  return 0;
}
