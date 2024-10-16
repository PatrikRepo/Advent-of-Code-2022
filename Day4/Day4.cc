#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void parseInput(std::vector<std::array<unsigned,4>> &pairs)
{
	std::string line;
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
			size_t pos = 0;
			size_t endpos = line.find_first_of("-");
			std::array<unsigned,4> pair;
			
			pair[0] = std::stoi(line.substr(0,endpos));
			
			pos = endpos+1;
			endpos = line.find_first_of(",",pos);
			pair[1] = std::stoi(line.substr(pos,endpos-pos));
			
			pos = endpos+1;
			endpos = line.find_first_of("-",pos);
			pair[2] = std::stoi(line.substr(pos,endpos-pos));
			
			pos = endpos+1;
			pair[3] = std::stoi(line.substr(pos));
			
			pairs.push_back(pair);
  	}
  }
  input.close();
}

uint64_t findOverlaps(const std::vector<std::array<unsigned,4>> &pairs)
{
	uint64_t result = 0;
	
	for(auto &pair:pairs)
	{
		if((pair[0] <= pair[2] && pair[1] >= pair[3]) || (pair[2] <= pair[0] && pair[3] >= pair[1]))
		{
			result++;
		}
	}
	
	return result;
}

uint64_t findAllOverlaps(const std::vector<std::array<unsigned,4>> &pairs)
{
	uint64_t result = 0;
	
	unsigned nonOverlaps = 0;
	
	for(auto &pair:pairs)
	{
		if(pair[1] < pair[2] || pair[3] < pair[0])
		{
			nonOverlaps++;
		}
	}
	
	result = pairs.size()-nonOverlaps;
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::array<unsigned,4>> pairs;
	
  parseInput(pairs);

	resultA = findOverlaps(pairs);
 	resultB = findAllOverlaps(pairs);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
