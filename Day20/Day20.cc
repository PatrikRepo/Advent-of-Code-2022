#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>

void parseInput(std::vector<int64_t> &numbers)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
  		numbers.push_back(std::stoll(line));
  	}
  }
  input.close();
}

int64_t mix(const std::list<std::pair<unsigned,int64_t>> &numbers, unsigned loops)
{
	int64_t result = 0;
	
	auto mixedNumbers = numbers;
	
	for(unsigned i=0; i<loops; i++)
	{
		for(auto &number:numbers)
		{
			int64_t steps = llabs(number.second);
			steps %= (mixedNumbers.size()-1);
			
			int offset = 0;
			auto it = mixedNumbers.begin();
			while(it->first != number.first)
			{
				offset++;
				std::advance(it,1);
			}
			
			int newPos = 0;
			if(number.second > 0)
			{
				newPos = (offset+steps)%(mixedNumbers.size());
			} 
			else
			{
				newPos = (offset-steps);
				newPos = (newPos < 0) ? newPos + mixedNumbers.size() : newPos;
			}
			if(newPos < offset && number.second > 0)
			{
				newPos++;
			}
			else if(newPos > offset && number.second < 0)
			{
				newPos--;
			}
			if(offset < newPos)
			{
				it = mixedNumbers.erase(it);
				it =std::next(it,newPos-offset);
				mixedNumbers.insert(it, number);
			}
			else if(newPos < offset)
			{
				it = mixedNumbers.erase(it);
				it = std::prev(it,offset-newPos);
				mixedNumbers.insert(it, number);
			}
		}
	}

	unsigned offset = 0;
	auto it = mixedNumbers.begin();
	while(it->second != 0)
	{
		offset++;
		std::advance(it,1);
	}
	
	unsigned pos1 = (offset+1000)%mixedNumbers.size();
	unsigned pos2 = (offset+2000)%mixedNumbers.size();
	unsigned pos3 = (offset+3000)%mixedNumbers.size();
	
	it = mixedNumbers.begin();
	std::advance(it,pos1);
	result += it->second;
	
	it = mixedNumbers.begin();
	std::advance(it,pos2);
	result += it->second;

	it = mixedNumbers.begin();
	std::advance(it,pos3);
	result += it->second;	

	return result;
}

int64_t decrypt(const std::vector<int64_t> &numbers)
{
	int64_t result = 0;
	
	std::list<std::pair<unsigned,int64_t>> numbersList;
	unsigned i = 0;
	for(auto number:numbers)
	{
		numbersList.emplace_back(i,number);
		i++;
	}

	result = mix(numbersList, 1);

	return result;
}

int64_t realDecrypt(const std::vector<int64_t> &numbers)
{
	int64_t result = 0;
	
	const int64_t decryptKey = 811589153;
	
	std::list<std::pair<unsigned,int64_t>> numbersList;
	unsigned i = 0;
	for(auto number:numbers)
	{
		numbersList.emplace_back(i,number*decryptKey);
		i++;
	}

	result = mix(numbersList, 10);
	
	return result;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;

	std::vector<int64_t> numbers;
	
  parseInput(numbers);

	resultA = decrypt(numbers);
 	resultB = realDecrypt(numbers);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
