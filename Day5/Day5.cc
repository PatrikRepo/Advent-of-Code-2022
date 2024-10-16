#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>

struct Instruction
{
	unsigned amount = 0;
	unsigned from = 0;
	unsigned to = 0;
};

void parseInput(std::array<std::stack<char>,9> &stacks, std::vector<Instruction> &instructions)
{
	std::string line;
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	unsigned i=8;
  	std::array<std::vector<unsigned>,9> crates;
  	while(i>0)
  	{
  		i--;
  		getline(input,line);
  		for(unsigned j=1; j<line.size(); j+=4)
  		{
  			if(line[j] != ' ')
  			{
  				crates[j/4].push_back(line[j]);
  			}
  		}
  	}
  	for(unsigned j=0; j<9; j++)
  	{
  		while(!crates[j].empty())
  		{
  			stacks[j].push(crates[j].back());
  			crates[j].pop_back();
  		}
  	}
  	
		getline(input,line);
		getline(input,line);
		
  	while(getline(input,line))
  	{
  		Instruction instruction;
			size_t pos = line.find_first_of("1234567890");
			size_t endpos = line.find_first_of(" ", pos);
			instruction.amount = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("1234567890",endpos);
			instruction.from = line[pos] - '0';
			
			instruction.to = line.back() - '0';
			
			instructions.push_back(instruction);
  	}
  }
  input.close();
}

std::string moveCrates(std::array<std::stack<char>,9> stacks, const std::vector<Instruction> &instructions)
{
	std::string result;
	
	for(auto &instruction:instructions)
	{
		for(unsigned i=0; i<instruction.amount; i++)
		{
			stacks[instruction.to-1].push(stacks[instruction.from-1].top());
			stacks[instruction.from-1].pop();
		}
	}
	
	for(auto &stack:stacks)
	{
		result += stack.top();
	}
	
	return result;
}

std::string cratemover9001(std::array<std::stack<char>,9> &stacks, const std::vector<Instruction> &instructions)
{
	std::string result;
	
	for(auto &instruction:instructions)
	{
		std::stack<char> crates;
		for(unsigned i=0; i<instruction.amount; i++)
		{
			crates.push(stacks[instruction.from-1].top());
			stacks[instruction.from-1].pop();
		}
		
		while(!crates.empty())
		{
			stacks[instruction.to-1].push(crates.top());
			crates.pop();
		}
	}
	
	for(auto &stack:stacks)
	{
		result += stack.top();
	}
	
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;

	std::array<std::stack<char>,9> stacks;
	std::vector<Instruction> instructions;
	
  parseInput(stacks, instructions);

	resultA = moveCrates(stacks, instructions);
 	resultB = cratemover9001(stacks, instructions);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
