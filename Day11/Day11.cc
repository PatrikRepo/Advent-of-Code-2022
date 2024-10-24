#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <deque>

struct Monkey
{
	std::deque<uint64_t> items;
	int val = 0;
	bool square = false;
	char op = 0;
	unsigned test = 0;
	std::pair<unsigned,unsigned> tossTo;
	uint64_t count = 0;
};

void parseInput(std::vector<Monkey> &monkeys)
{
	std::string line;
  std::ifstream input("input.txt");

  if(input.is_open())
  {	
		while(getline(input,line))
		{
			Monkey monkey;
			getline(input,line);
			size_t pos = line.find_first_of("1234567890");
			while(pos != std::string::npos)
			{
				size_t endpos = line.find_first_of(",", pos);
				endpos = (endpos == std::string::npos) ? line.size() : endpos;
				monkey.items.push_back(std::stoi(line.substr(pos,endpos-pos)));
				pos = line.find_first_of("1234567890",endpos);
			}
			
			getline(input,line);
			pos = line.find_first_of("+*");
			monkey.op = line[pos];
			pos = line.find_first_of("1234567890", pos);
			if(pos == std::string::npos)
			{
				monkey.square = true;
			}
			else
			{
				monkey.val = std::stoi(line.substr(pos));
			}
			
			getline(input,line);
			pos = line.find_first_of("1234567890");
			monkey.test = std::stoi(line.substr(pos));
			
			getline(input,line);
			pos = line.find_first_of("1234567890");
			monkey.tossTo.first = std::stoi(line.substr(pos));
			
			getline(input,line);
			pos = line.find_first_of("1234567890");
			monkey.tossTo.second = std::stoi(line.substr(pos));
			
			getline(input,line);
			monkeys.push_back(monkey);
		}
  }
  
  input.close();
}

uint64_t findMonkeys(std::vector<Monkey> monkeys)
{
	uint64_t result = 0;
	
	for(unsigned i=0; i<20; i++)
	{
		for(auto &monkey:monkeys)
		{
			while(!monkey.items.empty())
			{
				monkey.count++;
				uint64_t item = monkey.items.front();
				monkey.items.pop_front();
				uint64_t val = 0;
				if(monkey.square)
				{
					val = item;
				}
				else
				{
					val = monkey.val;
				}
				
				if(monkey.op == '+')
				{
					item += val;
				}
				else
				{
					item *= val;
				}
				item /= 3;
				unsigned newMonkey = (item % monkey.test == 0) ? monkey.tossTo.first : monkey.tossTo.second;
				monkeys[newMonkey].items.push_back(item);
			}
		}
	}
	
	unsigned first = 0;
	unsigned second = 0;
	
	for(auto &monkey:monkeys)
	{
		if(monkey.count > first)
		{
			second = first;
			first = monkey.count;
		}
		else if(monkey.count > second)
		{
			second = monkey.count;
		}
	}
	result = first*second;
	
	return result;
}

uint64_t bigWorry(std::vector<Monkey> &monkeys)
{
	uint64_t result = 0;
	
	for(unsigned i=0; i<10000; i++)
	{
		for(auto &monkey:monkeys)
		{
			while(!monkey.items.empty())
			{
				monkey.count++;
				uint64_t item = monkey.items.front();
				monkey.items.pop_front();
				uint64_t val = 0;
				if(monkey.square)
				{
					val = item;
				}
				else
				{
					val = monkey.val;
				}
				
				if(monkey.op == '+')
				{
					item += val;
				}
				else
				{
					item *= val;
				}

				//Product of all test numbers which are all primes: 2*3*5*7*11*13*17*19 = 9699690
				item %= 9699690;
				item += 9699690;
				unsigned newMonkey = (item % monkey.test == 0) ? monkey.tossTo.first : monkey.tossTo.second;
				monkeys[newMonkey].items.push_back(item);
			}
		}
	}
	
	uint64_t first = 0;
	uint64_t second = 0;
	
	for(auto &monkey:monkeys)
	{
		if(monkey.count > first)
		{
			second = first;
			first = monkey.count;
		}
		else if(monkey.count > second)
		{
			second = monkey.count;
		}
	}
	result = first*second;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<Monkey> monkeys;
	
  parseInput(monkeys);

	resultA = findMonkeys(monkeys);
 	resultB = bigWorry(monkeys);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;

  
  return 0;
}
