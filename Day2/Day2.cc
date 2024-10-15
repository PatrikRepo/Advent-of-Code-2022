#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<std::pair<char,char>> &instructions)
{
	std::string line;
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
			instructions.push_back(std::make_pair(line[0],line[2]));
  	}
  }
  input.close();
}

uint64_t followGuide(const std::vector<std::pair<char,char>> &instructions)
{
	uint64_t result = 0;
	
	for(auto &instruction:instructions)
	{
		if(instruction.first + 1 == instruction.second - 'X' + 'A' || instruction.first - 2 == instruction.second - 'X' + 'A')
		{
			result += 6;
		}
		else if(instruction.first == instruction.second - 'X' + 'A')
		{
			result += 3;
		}
		
		result += instruction.second - 'X' + 1;
	}
	
	return result;
}

uint64_t realInstructions(std::vector<std::pair<char,char>> &instructions)
{
	uint64_t result = 0;
	
	for(auto &instruction:instructions)
	{
		if(instruction.second == 'X')
		{
			instruction.second = instruction.first - 1 + 'X' - 'A';
			instruction.second = (instruction.second < 'X') ? 'Z' : instruction.second;
		}
		else if(instruction.second == 'Y')
		{
			instruction.second = instruction.first + 'X' - 'A';
		}
		else
		{
			instruction.second = instruction.first + 1 + 'X' - 'A';
			instruction.second = (instruction.second > 'Z') ? 'X' : instruction.second;
		}
	}
	
	result = followGuide(instructions);
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::pair<char,char>> instructions;
	
  parseInput(instructions);

	resultA = followGuide(instructions);
 	resultB = realInstructions(instructions);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
