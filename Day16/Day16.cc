#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <utility>

struct State
{
	std::string room;
	std::string prev;
	std::vector<std::string> openValves;
	unsigned released = 0;
	unsigned timeLeft = 0;
	unsigned releasing = 0;
	bool twice = false;
};

struct Valve
{
	unsigned pressure = 0;
	std::vector<std::pair<std::string,unsigned>> leadsTo;
};

void parseInput(std::unordered_map<std::string,Valve> &valves)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			std::string name = line.substr(6,2);
			Valve valve;
			
			size_t pos = line.find_first_of("1234567890");
			size_t endpos = line.find_first_of(";",pos);
			valve.pressure = std::stoi(line.substr(pos,endpos-pos));
			
			pos = endpos+24;
			if(line[pos] == ' ')
			{
				pos++;
			}
			while(endpos != line.size())
			{
				endpos = line.find_first_of(",",pos);
				if(endpos == std::string::npos)
				{
					endpos = line.size();
				}
				valve.leadsTo.emplace_back(line.substr(pos,endpos-pos),1);
				pos = endpos+2;
			}
			valves[name] = valve;
		}
	}
	input.close();
}

void reduceMap(std::unordered_map<std::string,Valve> &valves)
{
	std::unordered_map<std::string,Valve> newValves;
	for(auto it=valves.begin(); it!=valves.end(); it++)
	{
		if(it->second.pressure > 0 || it->first == "AA")
		{
			Valve newValve = it->second;
			newValve.leadsTo.clear();
			std::string name = it->first;
			std::deque<std::pair<std::string,unsigned>> openList;
			std::vector<std::string> closedList;
			openList.push_back(std::make_pair(name,0));
			
			while(!openList.empty())
			{
				auto v = openList.front();
				openList.pop_front();
				closedList.push_back(v.first);
				if(v.first != name && (valves.at(v.first).pressure > 0 || v.first == "AA"))
				{
					newValve.leadsTo.push_back(v);
				}
				else
				{
					for(auto &nV:valves.at(v.first).leadsTo)
					{
						std::pair<std::string,unsigned> newV;
						newV.first = nV.first;
						newV.second = v.second+1;
						
						auto it = std::find_if(openList.begin(), openList.end(), [newV](std::pair<std::string,unsigned> &oV){ return newV.first == oV.first; });
						if(it != std::end(openList))
						{
							if(it->second > newV.second)
							{
								*it = newV;
							}
						}
						else if(newV.first != name && std::find_if(closedList.begin(), closedList.end(), [newV](std::string &cV){ return newV.first == cV;}) == std::end(closedList))
						{
							openList.push_back(newV);
						}
					}
				}
				std::sort(openList.begin(), openList.end(), [](std::pair<std::string,unsigned> &p1, std::pair<std::string,unsigned> &p2){ return p1.second < p2.second;}); 
			}
			
			newValves[name] = newValve;
		}
	}
	
	valves = newValves;
}

uint64_t releasePressure(const std::unordered_map<std::string,Valve> &valves, unsigned time, bool twice)
{
	uint64_t result = 0;
	
	unsigned maxPressure = 0;
	for(auto it=valves.begin(); it!=valves.end(); it++)
	{
		maxPressure += it->second.pressure;
	}
	
	State state;
	state.room = "AA";
	state.timeLeft = time;
	state.twice = twice;
	std::deque<State> openList;
	openList.push_back(state);
	std::vector<State> closedList;
	
	while(!openList.empty())
	{
		state = openList.front();
		openList.pop_front();
		closedList.push_back(state);
		
		if(state.timeLeft == 0)
		{
			if(state.twice)
			{
				state.twice = false;
				state.timeLeft = time;
				state.room = "AA";
				state.prev = "";
			}
			else
			{
				result = state.released;
				break;
			}
		}
		
		for(auto &newValve:valves.at(state.room).leadsTo)
		{
			if(newValve.first == "AA" || (valves.at(state.room).leadsTo.size() > 1 && newValve.first == state.prev))
			{
				continue;
			}
			State newState = state;
			newState.prev = newState.room;
			newState.room = newValve.first;
			newState.timeLeft = (newState.timeLeft > newValve.second) ? newState.timeLeft - newValve.second : 0;
			if(newState.timeLeft > 0 && 
					valves.at(newValve.first).pressure > 0 && 
					std::find_if(newState.openValves.begin(), newState.openValves.end(), [newValve](std::string &oValve){ return newValve.first == oValve; }) == std::end(newState.openValves))
			{
				newState.timeLeft--;
				newState.released += (valves.at(newValve.first).pressure)*newState.timeLeft;
				newState.openValves.push_back(newValve.first);
				newState.releasing += valves.at(newValve.first).pressure;
				if(newState.releasing == maxPressure)
				{
					newState.timeLeft = 0;
				}
			}
			auto it = std::find_if(openList.begin(), openList.end(), [newState](State &oState){ return newState.room == oState.room && newState.released == oState.released; });
			if(it != std::end(openList))
			{
				if(it->timeLeft < newState.timeLeft)
				{
					*it = newState;
				}
			}
			else if(std::find_if(closedList.begin(), closedList.end(), [newState](State &cState){ return newState.room == cState.room && newState.releasing == cState.releasing;}) == std::end(closedList))
			{
				openList.push_back(newState);
			}
		}
		std::sort(openList.begin(), openList.end(), [](State &s1, State &s2){ if(s1.timeLeft == s2.timeLeft) return s1.released > s2.released; else return s1.timeLeft > s2.timeLeft; });
	}
	
	return result;
}


int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::unordered_map<std::string,Valve> valves;

	parseInput(valves);
	reduceMap(valves);
	
	resultA = releasePressure(valves, 30, false);
	resultB = releasePressure(valves, 26, true);

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}

