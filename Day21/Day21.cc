#include <iostream>
#include <fstream>
#include <unordered_map>
#include <variant>

struct Monkey
{
	std::string monkey1;
	std::string monkey2;
	char op = 0;
};

void parseInput(std::unordered_map<std::string, std::variant<uint64_t, Monkey>> &monkeys)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
			std::string name = line.substr(0,4);
			size_t pos = line.find_first_of("1234567890");
			if(pos != std::string::npos)
			{
				monkeys[name] = std::stoi(line.substr(pos));
			}
			else
			{
				Monkey monkey;
				monkey.monkey1 = line.substr(6,4);
				monkey.op = line[11];
				monkey.monkey2 = line.substr(13);
				monkeys[name] = monkey;
			}
  	}
  }
  input.close();
}

uint64_t monkeyNumber(const std::unordered_map<std::string, std::variant<uint64_t, Monkey>> &monkeys, const std::string &monkey)
{
	uint64_t result = 0;
	
	auto var = monkeys.at(monkey);
	if(std::holds_alternative<uint64_t>(var))
	{
		result = std::get<uint64_t>(var);
	}
	else
	{
		uint64_t monkey1 = monkeyNumber(monkeys, std::get<Monkey>(var).monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, std::get<Monkey>(var).monkey2);

		switch(std::get<Monkey>(var).op)
		{
			case '+':
			{
				result = monkey1 + monkey2;
				break;
			}
			case '-':
			{
				result = monkey1 - monkey2;
				break;
			}
			case '*':
			{
				result = monkey1 * monkey2;
				break;
			}
			case '/':
			{
				result = monkey1 / monkey2;
				break;
			}
		}
	}
	
	return result;
}

uint64_t calculateRoot(const std::unordered_map<std::string, std::variant<uint64_t, Monkey>> &monkeys)
{
	uint64_t result = 0;
	
	result = monkeyNumber(monkeys, "root");
	
	return result;
}

uint64_t rootCompare(std::unordered_map<std::string, std::variant<uint64_t, Monkey>> &monkeys)
{
	uint64_t result = 0;
	
	Monkey root = std::get<Monkey>(monkeys.at("root"));
	
	for(uint64_t i=0; i<= 10000000000000; i+= 1000000000000)
	{
		monkeys["humn"] = i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result = i - 1000000000000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 1000000000000; i+= 100000000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 100000000000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 100000000000; i+= 10000000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 10000000000;
			break;
		}
	}

	for(uint64_t i=0; i<= 10000000000; i+= 1000000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 1000000000;
			break;
		}
	}

	for(uint64_t i=0; i<= 1000000000; i+= 100000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 100000000;
			break;
		}
	}

	for(uint64_t i=0; i<= 100000000; i+= 10000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 10000000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 10000000; i+= 1000000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 1000000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 1000000; i+= 100000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 100000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 100000; i+= 10000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 10000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 10000; i+= 1000)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 1000;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 1000; i+= 100)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 < monkey2)
		{
			result += i - 100;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 100; i+= 10)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 <= monkey2)
		{
			result += i - 10;
			break;
		}
	}
	
	for(uint64_t i=0; i<= 10; i++)
	{
		monkeys["humn"] = result + i;
		uint64_t monkey1 = monkeyNumber(monkeys, root.monkey1);
		uint64_t monkey2 = monkeyNumber(monkeys, root.monkey2);
		if(monkey1 == monkey2)
		{
			result += i;
			break;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::unordered_map<std::string, std::variant<uint64_t, Monkey>> monkeys;
	
  parseInput(monkeys);

	resultA = calculateRoot(monkeys);
 	resultB = rootCompare(monkeys);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
