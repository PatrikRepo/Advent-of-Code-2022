#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>

struct Resources
{
	unsigned ore = 0;
	unsigned clay = 0;
	unsigned obsidian = 0;
};	

struct Bots
{
	unsigned oreBots = 0;
	unsigned clayBots = 0;
	unsigned obsidianBots = 0;
	unsigned geodeBots = 0;
};

void parseInput(std::vector<std::array<unsigned,6>> &blueprints)
{
	std::string line;
	
  std::ifstream input("input.txt");
  if(input.is_open())
  {	
  	while(getline(input,line))
  	{
  		std::array<unsigned,6> blueprint;
  		size_t pos = line.find_first_of("1234567890", 15);
  		size_t endpos = line.find_first_of(" ",pos);
  		blueprint[0] = std::stoi(line.substr(pos,endpos-pos));
  		
  		pos = line.find_first_of("1234567890", endpos);
  		endpos = line.find_first_of(" ",pos);
  		blueprint[1] = std::stoi(line.substr(pos,endpos-pos));
  		
  		pos = line.find_first_of("1234567890", endpos);
  		endpos = line.find_first_of(" ",pos);
  		blueprint[2] = std::stoi(line.substr(pos,endpos-pos));
  		
  		pos = line.find_first_of("1234567890", endpos);
  		endpos = line.find_first_of(" ",pos);
  		blueprint[3] = std::stoi(line.substr(pos,endpos-pos));

  		pos = line.find_first_of("1234567890", endpos);
  		endpos = line.find_first_of(" ",pos);
  		blueprint[4] = std::stoi(line.substr(pos,endpos-pos));

  		pos = line.find_first_of("1234567890", endpos);
  		endpos = line.find_first_of(" ",pos);
  		blueprint[5] = std::stoi(line.substr(pos,endpos-pos));
  		
  		blueprints.push_back(blueprint);
  	}
  }
  input.close();
}

uint64_t getKey(unsigned timeLeft, const Resources &resources, const Bots &bots)
{
	return timeLeft + (resources.clay*100) + (bots.oreBots*10000) + (bots.clayBots*1000000) + (bots.obsidianBots*100000000) + (bots.geodeBots*10000000000);
}

uint64_t breakGeodes(const std::array<unsigned,6> &blueprint, unsigned timeLeft, Resources resources, Bots bots, std::unordered_map<uint64_t,uint64_t> &cache)
{
	uint64_t result = 0;

	timeLeft--;
	result += bots.geodeBots;
	
	
	if(timeLeft>0)
	{
		uint64_t maxResult = 0;
		
		if(blueprint[4] <= resources.ore && blueprint[5] <= resources.obsidian)
		{
			Bots newBots = bots;
			newBots.geodeBots++;
			Resources newResources = resources;
			newResources.ore -= blueprint[4];
			newResources.obsidian -= blueprint[5];
			newResources.ore += bots.oreBots;
			newResources.clay += bots.clayBots;
			newResources.obsidian += bots.obsidianBots;
			
			if(cache.count(getKey(timeLeft, newResources, newBots)) == 0)
			{
				cache[getKey(timeLeft, newResources, newBots)] = breakGeodes(blueprint, timeLeft, newResources, newBots, cache);
			}
			uint64_t tempResult = cache.at(getKey(timeLeft, newResources, newBots));
			maxResult = (maxResult < tempResult) ? tempResult : maxResult;
		}

		if(blueprint[2] <= resources.ore && blueprint[3] <= resources.clay)
		{
			Bots newBots = bots;
			newBots.obsidianBots++;
			Resources newResources = resources;
			newResources.ore -= blueprint[2];
			newResources.clay -= blueprint[3];
			newResources.ore += bots.oreBots;
			newResources.clay += bots.clayBots;
			newResources.obsidian += bots.obsidianBots;
			
			if(cache.count(getKey(timeLeft, newResources, newBots)) == 0)
			{
				cache[getKey(timeLeft, newResources, newBots)] = breakGeodes(blueprint, timeLeft, newResources, newBots, cache);
			}
			uint64_t tempResult = cache.at(getKey(timeLeft, newResources, newBots));
			maxResult = (maxResult < tempResult) ? tempResult : maxResult;
		}		

		if(blueprint[1] <= resources.ore)
		{
			Bots newBots = bots;
			newBots.clayBots++;
			Resources newResources = resources;
			newResources.ore -= blueprint[1];
			newResources.ore += bots.oreBots;
			newResources.clay += bots.clayBots;
			newResources.obsidian += bots.obsidianBots;
			
			if(cache.count(getKey(timeLeft, newResources, newBots)) == 0)
			{
				cache[getKey(timeLeft, newResources, newBots)] = breakGeodes(blueprint, timeLeft, newResources, newBots, cache);
			}
			uint64_t tempResult = cache.at(getKey(timeLeft, newResources, newBots));
			maxResult = (maxResult < tempResult) ? tempResult : maxResult;
		}

		if(blueprint[0] <= resources.ore)
		{
			Bots newBots = bots;
			newBots.oreBots++;
			Resources newResources = resources;
			newResources.ore -= blueprint[0];
			newResources.ore += bots.oreBots;
			newResources.clay += bots.clayBots;
			newResources.obsidian += bots.obsidianBots;
			
			if(cache.count(getKey(timeLeft, newResources, newBots)) == 0)
			{
				cache[getKey(timeLeft, newResources, newBots)] = breakGeodes(blueprint, timeLeft, newResources, newBots, cache);
			}
			uint64_t tempResult = cache.at(getKey(timeLeft, newResources, newBots));
			maxResult = (maxResult < tempResult) ? tempResult : maxResult;
		}

		resources.ore += bots.oreBots;
		resources.clay += bots.clayBots;
		resources.obsidian += bots.obsidianBots;

		if(cache.count(getKey(timeLeft, resources, bots)) == 0)
		{
			cache[getKey(timeLeft, resources, bots)] = breakGeodes(blueprint, timeLeft, resources, bots, cache);
		}
		uint64_t tempResult = cache.at(getKey(timeLeft, resources, bots));
		maxResult = (maxResult < tempResult) ? tempResult : maxResult;
		
		result += maxResult;
	}	
	
	return result;
}

uint64_t breakGeodes(const std::vector<std::array<unsigned,6>> &blueprints)
{
	uint64_t result = 0;
	
	for(unsigned i=0; i<blueprints.size(); i++)
	{
		std::unordered_map<uint64_t,uint64_t> cache;
		Bots bots;
		bots.oreBots = 1;
		uint64_t newResult = breakGeodes(blueprints[i], 24, Resources(), bots, cache);
		result += (i+1)*newResult;
	}
	
	return result;
}

uint64_t moreGeodes(const std::vector<std::array<unsigned,6>> &blueprints)
{
	uint64_t result = 1;
	
	for(unsigned i=0; i<3; i++)
	{
		std::unordered_map<uint64_t,uint64_t> cache;
		Bots bots;
		bots.oreBots = 1;
		result *=  breakGeodes(blueprints[i], 32, Resources(), bots, cache);
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::array<unsigned,6>> blueprints;
	
  parseInput(blueprints);

	resultA = breakGeodes(blueprints);
 	resultB = moreGeodes(blueprints);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
