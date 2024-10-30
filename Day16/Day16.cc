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
	std::vector<std::string> openValves;
	unsigned released = 0;
	unsigned timeLeft = 0;
	unsigned releasing = 0;
};

struct ElephantState
{
	std::string room1;
	std::string room2;
	std::vector<std::string> openValves;
	unsigned released = 0;
	unsigned timeLeft1 = 0;
	unsigned timeLeft2 = 0;
	unsigned releasing = 0;
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

uint64_t releasePressure(const std::unordered_map<std::string,Valve> &valves)
{
	uint64_t result = 0;
	
	unsigned maxPressure = 0;
	for(auto it=valves.begin(); it!=valves.end(); it++)
	{
		maxPressure += it->second.pressure;
	}
	
	State state;
	state.room = "AA";
	state.timeLeft = 30;
	std::deque<State> openList;
	openList.push_back(state);
	std::vector<State> closedList;
	
	while(!openList.empty())
	{
		state = openList.front();
		openList.pop_front();
		
		if(state.timeLeft == 0)
		{
			result = state.released;
			break;
		}
		
		closedList.push_back(state);
		
		for(auto &newValve:valves.at(state.room).leadsTo)
		{
			State newState = state;
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

uint64_t withElephant(const std::unordered_map<std::string,Valve> &valves)
{
	uint64_t result = 0;
	
	unsigned maxPressure = 0;
	for(auto it=valves.begin(); it!=valves.end(); it++)
	{
		maxPressure += it->second.pressure;
	}
	
	ElephantState state;
	state.room1 = "AA";
	state.room2 = "AA";
	state.timeLeft1 = 26;
	state.timeLeft2 = 26;
	std::deque<ElephantState> openList;
	openList.push_back(state);
	std::vector<ElephantState> closedList;
	
	while(!openList.empty())
	{
		state = openList.front();
		openList.pop_front();

		if(state.timeLeft1 == 0 && state.timeLeft2 == 0)
		{
			result = state.released;
			break;
		}
		
		closedList.push_back(state);
		bool person = state.timeLeft1 >= state.timeLeft2;
		
		if(person)
		{
			for(auto &newValve:valves.at(state.room1).leadsTo)
			{
				ElephantState newState = state;
				newState.room1 = newValve.first;
				newState.timeLeft1 = (newState.timeLeft1 > newValve.second) ? newState.timeLeft1 - newValve.second : 0;
				if(newState.timeLeft1 > 0 && 
						valves.at(newValve.first).pressure > 0 && 
						std::find_if(newState.openValves.begin(), newState.openValves.end(), [newValve](std::string &oValve){ return newValve.first == oValve; }) == std::end(newState.openValves))
				{
					newState.timeLeft1--;
					newState.released += (valves.at(newValve.first).pressure)*newState.timeLeft1;
					newState.openValves.push_back(newValve.first);
					newState.releasing += valves.at(newValve.first).pressure;
					if(newState.releasing == maxPressure)
					{
						newState.timeLeft1 = 0;
						newState.timeLeft2 = 0;
					}
				}
				auto it = std::find_if(openList.begin(), openList.end(), [newState](ElephantState &oState){ 
					return ((newState.room1 == oState.room1 && newState.room2 == oState.room2) || (newState.room1 == oState.room2 && newState.room2 == oState.room1)) && newState.released == oState.released; });
				if(it != std::end(openList))
				{
					if(it->timeLeft1 + it->timeLeft2 < newState.timeLeft1 + newState.timeLeft2)
					{
						*it = newState;
					}
				}
				else if(std::find_if(closedList.begin(), closedList.end(), [newState](ElephantState &cState){ 
					return ((newState.room1 == cState.room1 && newState.room2 == cState.room2) || (newState.room1 == cState.room2 && newState.room2 == cState.room1)) && newState.releasing == cState.releasing;}) == std::end(closedList))
				{
					openList.push_back(newState);
				}
			}
		}
		
		else
		{
			for(auto &newValve:valves.at(state.room2).leadsTo)
			{
				ElephantState newState = state;
				newState.room2 = newValve.first;
				newState.timeLeft2 = (newState.timeLeft2 > newValve.second) ? newState.timeLeft2 - newValve.second : 0;
				if(newState.timeLeft2 > 0 && 
						valves.at(newValve.first).pressure > 0 && 
						std::find_if(newState.openValves.begin(), newState.openValves.end(), [newValve](std::string &oValve){ return newValve.first == oValve; }) == std::end(newState.openValves))
				{
					newState.timeLeft2--;
					newState.released += (valves.at(newValve.first).pressure)*newState.timeLeft2;
					newState.openValves.push_back(newValve.first);
					newState.releasing += valves.at(newValve.first).pressure;
					if(newState.releasing == maxPressure)
					{
						newState.timeLeft1 = 0;
						newState.timeLeft2 = 0;
					}
				}
				auto it = std::find_if(openList.begin(), openList.end(), [newState](ElephantState &oState){ 
					return ((newState.room1 == oState.room1 && newState.room2 == oState.room2) || (newState.room1 == oState.room2 && newState.room2 == oState.room1)) && newState.releasing == oState.releasing; });
				if(it != std::end(openList) && it->timeLeft1 + it->timeLeft2 < newState.timeLeft1 + newState.timeLeft2)
				{
					*it = newState;
				}
				else if(std::find_if(closedList.begin(), closedList.end(), [newState](ElephantState &cState){ 
					return ((newState.room1 == cState.room1 && newState.room2 == cState.room2) || (newState.room1 == cState.room2 && newState.room2 == cState.room1)) && newState.releasing == cState.releasing;}) == std::end(closedList))
				{
					openList.push_back(newState);
				}
			}
		}
		
		std::sort(openList.begin(), openList.end(), [](ElephantState &s1, ElephantState &s2){ 
			if(s1.timeLeft1 + s1.timeLeft2 == s2.timeLeft1 + s2.timeLeft2) return s1.released > s2.released; else return s1.timeLeft1+s1.timeLeft2 > s2.timeLeft1+s2.timeLeft2; });
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
	
	resultA = releasePressure(valves);
	resultB = withElephant(valves);

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}

