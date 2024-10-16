#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

void parseInput(std::vector<std::string> &rucksacks)
{
	std::string line;
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
			rucksacks.push_back(line);
  	}
  }
  input.close();
}

unsigned getPriority(char c)
{
	unsigned result = 0;
	
	if(c >= 'a' && c <= 'z')
	{
		result = c - 'a' + 1;
	}
	else
	{
		result = c - 'A' + 27;
	}
	
	return result;
}

uint64_t findDuplicates(const std::vector<std::string> &rucksacks)
{
	uint64_t result = 0;
	
	for(auto &rucksack:rucksacks)
	{
		std::unordered_map<char,unsigned> cache;
		for(unsigned i=0; i<rucksack.size()/2; i++)
		{
			cache[rucksack[i]] = 1;
		}
		for(unsigned i=rucksack.size()/2; i<rucksack.size(); i++)
		{
			if(cache.count(rucksack[i]))
			{
				result += getPriority(rucksack[i]);
				break;
			}
		}
	}	
	
	return result;
}

uint64_t findBadges(const std::vector<std::string> &rucksacks)
{
	uint64_t result = 0;
	
	for(unsigned i=0; i<rucksacks.size(); i+=3)
	{
		std::array<unsigned,52> cache{0};
		for(unsigned j=0; j<rucksacks[i].size(); j++)
		{
			cache[getPriority(rucksacks[i][j])-1] = 1;
		}
		for(unsigned j=0; j<rucksacks[i+1].size(); j++)
		{
			if(cache[getPriority(rucksacks[i+1][j])-1] == 1)
			{
				cache[getPriority(rucksacks[i+1][j])-1] = 2;
			}
		}
		for(unsigned j=0; j<rucksacks[i+2].size(); j++)
		{
			if(cache[getPriority(rucksacks[i+2][j])-1] == 2)
			{
				result += getPriority(rucksacks[i+2][j]);
				break;
			}
		}
	}	
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> rucksacks;
	
  parseInput(rucksacks);

	resultA = findDuplicates(rucksacks);
 	resultB = findBadges(rucksacks);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
