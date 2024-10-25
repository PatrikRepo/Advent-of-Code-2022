#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

void parseInput(std::vector<std::pair<std::string,std::string>> &pairs)
{
	std::string line;
  std::ifstream input("input.txt");

  if(input.is_open())
  {	
		while(getline(input,line))
		{
			std::string first = line;
			getline(input,line);
			std::string second = line;
			pairs.emplace_back(first, second);
			getline(input,line);
		}
  }
  
  input.close();
};

std::pair<bool,bool> comparePackets(const std::string &packet1, const std::string &packet2)
{
	std::pair<bool,bool> result;
	bool done = false;
	
	size_t pos1 = 1;
	size_t pos2 = 1;
	
	while(!done)
	{
		if(pos1 >= packet1.size() || packet1[pos1] == ']')
		{
			if(pos2 < packet2.size() && packet2[pos2] != ']')
			{
				done = true;
			}
			result.second = true;
			break;
		}
		if(pos2 >= packet2.size() || packet2[pos2] == ']')
		{
			done = true;
			result.second = false;
			break;
		}
		if(packet1[pos1] != '[' && packet2[pos2] != '[')
		{
			size_t endpos = packet1.find_first_of(",]",pos1);
			unsigned num1 = std::stoi(packet1.substr(pos1,endpos-pos1));
			pos1 = endpos+1;
			endpos = packet2.find_first_of(",]",pos2);
			unsigned num2 = std::stoi(packet2.substr(pos2,endpos-pos2));
			pos2 = endpos+1;
			if(num1 < num2)
			{	
				done = true;
				result.second = true;
				break;
			}
			else if(num1 > num2)
			{
				done = true;
				result.second = false;
				break;
			}
		}
		else
		{
			std::string newPacket1;
			if(packet1[pos1] != '[')
			{
				size_t endpos = packet1.find_first_of(",]",pos1);
				newPacket1 = "[" + packet1.substr(pos1,endpos-pos1) + "]";
				pos1 = endpos+1;
			}
			else
			{
				unsigned count = 1;
				size_t findPos = pos1;
				while(count > 0)
				{
					findPos = packet1.find_first_of("[]",findPos+1);
					if(packet1[findPos] == '[')
					{
						count++;
					}
					else
					{
						count--;
					}
				}
				newPacket1 = packet1.substr(pos1, findPos + 1 - pos1);
				pos1 = findPos+2;
			}

			std::string newPacket2;
			if(packet2[pos2] != '[')
			{
				size_t endpos = packet2.find_first_of(",]",pos2);
				newPacket2 = "[" + packet2.substr(pos2,endpos-pos2) + "]";
				pos2 = endpos+1;
			}
			else
			{
				unsigned count = 1;
				size_t findPos = pos2;
				while(count > 0)
				{
					findPos = packet2.find_first_of("[]",findPos+1);
					if(packet2[findPos] == '[')
					{
						count++;
					}
					else
					{
						count--;
					}
				}
				newPacket2 = packet2.substr(pos2, findPos + 1 - pos2);
				pos2 = findPos+2;
			}
			
			auto newResult = comparePackets(newPacket1, newPacket2);
			done = newResult.first;
			if(done)
			{
				result.second = newResult.second;
				break;
			}
		}
	}
	
	result.first = done;
	
	return result;
}

uint64_t checkOrder(const std::vector<std::pair<std::string,std::string>> &pairs)
{
	uint64_t result = 0;
	
	unsigned index = 1;
	
	for(auto &pair:pairs)
	{
		if(comparePackets(pair.first,pair.second).second)
		{
			result += index;
		}
		index++;
	}
	
	return result;
}

uint64_t sortPackets(const std::vector<std::pair<std::string,std::string>> &pairs)
{
	uint64_t result = 1;
	
	std::vector<std::string> packets;
	
	for(auto &pair:pairs)
	{
		packets.push_back(pair.first);
		packets.push_back(pair.second);
	}	
	std::string div1 = "[[2]]";
	std::string div2 = "[[6]]";
	
	packets.push_back(div1);
	packets.push_back(div2);
	
	std::sort(packets.begin(), packets.end(), [](std::string &packet1, std::string &packet2){ return comparePackets(packet1,packet2).second; });
	
	unsigned count = 1;
	for(auto &packet:packets)
	{
		if(packet == div1 || packet == div2)
		{
			result *= count;
			if(result != count)
			{
				break;
			}
		}
		count++;
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::pair<std::string,std::string>> pairs;
	
  parseInput(pairs);

	resultA = checkOrder(pairs);
 	resultB = sortPackets(pairs);
 	
  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;

  
  return 0;
}
