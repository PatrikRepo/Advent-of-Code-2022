#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
 		while(getline(input,line))
  	{
  		numbers.push_back(line);
  	}
  }
  input.close();
}
	
std::string findSnafu(const std::vector<std::string> &numbers)
{
	std::string result;
	
	int64_t sum = 0;
	
	for(auto &num:numbers)
	{
		int64_t base = 1;
		for(unsigned i=num.size()-1; i+1>0; i--)
		{
			switch(num[i])
			{
				case '2':
				{
					sum += 2*base;
					break;
				}
				case '1':
				{
					sum += base;
					break;
				}
				case '-':
				{
					sum -= base;
					break;
				}
				case '=':
				{
					sum -= 2*base;
					break;
				}
			}
			base *= 5;
		}
	}
	
	uint64_t largest = 5;
	while(sum/(largest*5) > 0)
	{
		largest *= 5;
	}	
	
	while(largest > 0)
	{
		result += std::to_string(sum/largest);
		sum %= largest;
		largest /= 5;
	}
	
	for(unsigned i=result.size()-1; i+1>0; i--)
	{
		if(result[i] >= '3')
		{
			if(result[i] == '3')
			{
				result[i] = '=';
			}
			else
			{
				result[i] = '-';
			}
			if(i == 0)
			{
				result.insert(result.begin(), '1');
			}
			else
			{
				result[i-1]++;
			}
		}
	}
	
	return result;
}	

int main()
{
	std::string result;

	std::vector<std::string> numbers; 
	
  parseInput(numbers);

	result = findSnafu(numbers);

  std::cout << "result: " << result << std::endl;
  
  return 0;
}
