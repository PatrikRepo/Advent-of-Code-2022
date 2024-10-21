#include <iostream>
#include <fstream>
#include <vector>

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

uint64_t findTrees(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	for(unsigned i=1; i<map.size()-1; i++)
	{
		for(unsigned j=1; j<map[0].size()-1; j++)
		{
			bool seen = true;
			
			for(unsigned k=0; k<j; k++)
			{
				if(map[i][k] >= map[i][j])
				{
					seen = false;
					break;
				}
			}
			if(seen)
			{
				result++;
				continue;
			}
			
			seen = true;
			for(unsigned k=0; k<i; k++)
			{
				if(map[k][j] >= map[i][j])
				{
					seen = false;
					break;
				}
			}
			if(seen)
			{
				result++;
				continue;
			}
			
			seen = true;
			for(unsigned k=j+1; k<map[0].size(); k++)
			{
				if(map[i][k] >= map[i][j])
				{
					seen = false;
					break;
				}
			}
			if(seen)
			{
				result++;
				continue;
			}
			
			seen = true;
			for(unsigned k=i+1; k<map.size(); k++)
			{
				if(map[k][j] >= map[i][j])
				{
					seen = false;
					break;
				}
			}
			if(seen)
			{
				result++;
				continue;
			}
		}
	}
	
	result += (2*map.size()) + (2*map[0].size()) - 4;
	
	return result;
}

uint64_t bestView(const std::vector<std::string> &map)
{
	uint64_t result = 0;
	
	for(unsigned i=1; i<map.size()-1; i++)
	{
		for(unsigned j=1; j<map.size()-1; j++)
		{
			unsigned newResult = 1;
			unsigned dist = 0;
			for(unsigned k=j-1; k+1>0; k--)
			{
				dist++;
				if(map[i][k] >= map[i][j])
				{
					break;
				}
			}
			newResult *= dist;

			dist = 0;
			for(unsigned k=i-1; k+1>0; k--)
			{
				dist++;
				if(map[k][j] >= map[i][j])
				{
					break;
				}
			}
			newResult *= dist;
			
			dist = 0;
			for(unsigned k=j+1; k<map[0].size(); k++)
			{
				dist++;
				if(map[i][k] >= map[i][j])
				{
					break;
				}
			}
			newResult *= dist;

			dist = 0;
			for(unsigned k=i+1; k<map.size(); k++)
			{
				dist++;
				if(map[k][j] >= map[i][j])
				{
					break;
				}
			}
			newResult *= dist;
			
			result = (newResult > result) ? newResult : result;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> map;
	
  parseInput(map);

	resultA = findTrees(map);
 	resultB = bestView(map);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
