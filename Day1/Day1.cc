#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::vector<unsigned>> &elves)
{
	std::string line;
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	std::vector<unsigned> elf;
  	while(getline(input,line))
  	{
			if(line != "")
			{
				elf.push_back(std::stoi(line));
			}
			else
			{
				elves.push_back(elf);
				elf.clear();
			}
  	}
  	elves.push_back(elf);
  }
  input.close();
}

uint64_t carriesMost(const std::vector<std::vector<unsigned>> &elves)
{
	uint64_t result = 0;
	
	for(auto &elf:elves)
	{
		unsigned tempResult = 0;
		
		for(auto &food:elf)
		{
			tempResult += food;
		}
		
		result = (result < tempResult) ? tempResult : result;
	}
	
	return result;
}

uint64_t topThree(const std::vector<std::vector<unsigned>> &elves)
{
	uint64_t result = 0;
	
	unsigned first = 0;
	unsigned second = 0;
	unsigned third = 0;
	
	for(auto &elf:elves)
	{
		unsigned tempResult = 0;
		
		for(auto &food:elf)
		{
			tempResult += food;
		}
		
		if(tempResult > first)
		{
			third = second;
			second = first;
			first = tempResult;
		}
		else if(tempResult > second)
		{
			third = second;
			second = tempResult;
		}
		else if(tempResult > third)
		{
			third = tempResult;
		}
	}
	
	result = first + second + third;
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::vector<unsigned>> elves;
	
  parseInput(elves);

	resultA = carriesMost(elves);
 	resultB = topThree(elves);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
