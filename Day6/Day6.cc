#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>

void parseInput(std::string &data)
{
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
		getline(input,data);
  }
  input.close();
}

uint64_t findMarker(const std::string &data, unsigned count)
{
	uint64_t result = 0;
	
	std::deque<char> chars;
	
	for(unsigned i=0; i<count-1; i++)
	{
		chars.push_back(data[i]);
	}
	
	for(unsigned i=count-1; i<data.size(); i++)
	{
		chars.push_back(data[i]);
		
		auto unique = chars;
		std::sort(unique.begin(), unique.end());
		auto last = std::unique(unique.begin(), unique.end());
		if(last - unique.begin() == count)
		{
			result = i+1;
			break;
		}
		
		chars.pop_front();
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB;

	std::string data;
	
  parseInput(data);

	resultA = findMarker(data, 4);
 	resultB = findMarker(data, 14);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
