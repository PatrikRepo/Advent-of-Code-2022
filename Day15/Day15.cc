#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

struct Sensor
{
	int64_t sX = 0;
	int64_t sY = 0;
	int64_t bX = 0;
	int64_t bY = 0;
};

void parseInput(std::vector<Sensor> &sensors)
{
	std::string line;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			Sensor sensor;
			size_t pos = line.find_first_of("-1234567890");
			size_t endpos = line.find_first_of(",",pos);
			sensor.sX = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("-1234567890", endpos);
			endpos = line.find_first_of(":", pos);
			sensor.sY = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("-1234567890",endpos);
			endpos = line.find_first_of(",",pos);
			sensor.bX = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("-1234567890", endpos);
			sensor.bY = std::stoi(line.substr(pos,endpos));
			
			sensors.push_back(sensor);
		}
	}
	input.close();
}

uint64_t noBeacons(const std::vector<Sensor> &sensors)
{
	uint64_t result = 0;
	
	std::vector<std::pair<int64_t,int64_t>> noBeacons;
	int64_t row = 2000000;
	
	for(auto &sensor:sensors)
	{
		int64_t dist = abs(sensor.bX - sensor.sX) + abs(sensor.bY - sensor.sY);
		int64_t space = 0;
		if(sensor.sY < row)
		{
			space = sensor.sY + dist - row;
		}
		else
		{
			space = dist + row - sensor.sY;
		}
		
		if(space >= 0)
		{
			noBeacons.emplace_back(sensor.sX - space, sensor.sX + space);
		}
	}
	
	std::sort(noBeacons.begin(), noBeacons.end(), [](std::pair<int64_t,int64_t> &p1, std::pair<int64_t,int64_t> &p2){ if(p1.first == p2.first) return p1.second > p2.second; else return p1.first < p2.first; });
	

	
	for(unsigned i=0; i<noBeacons.size()-1; i++)
	{
		for(unsigned j=i+1; j<noBeacons.size(); j++)
		{
			if(noBeacons[j].second <= noBeacons[i].second)
			{
				noBeacons.erase(noBeacons.begin() + j);
				j--;
			}
			else if(noBeacons[j].first <= noBeacons[i].second)
			{
				noBeacons[j].first = noBeacons[i].second + 1;
			}
		}
	}
	
	for(auto &pair:noBeacons)
	{
		result += pair.second + 1 - pair.first;
	}
	
	std::unordered_map<int64_t, unsigned> cache;
	for(auto &sensor:sensors)
	{
		if(sensor.bY == row)
		{
			cache[sensor.bX + sensor.bY] = 1;
		}
	}
	
	result -= cache.size();
	
	return result;
}

uint64_t findBeacon(const std::vector<Sensor> &sensors)
{
	uint64_t result = 0;

	bool done = false;
	
	for(int64_t i=0; i<=4000000; i++)
	{
		for(int64_t j=0; j<=4000000; j++)
		{
			done = true;
			for(auto &sensor:sensors)
			{
				int64_t dist = abs(sensor.bX - sensor.sX) + abs(sensor.bY - sensor.sY);
				int64_t space = 0;
				if(sensor.sY < i)
				{
					space = sensor.sY + dist - i;
				}
				else
				{
					space = dist + i - sensor.sY;
				}
				
				if(space >= 0)
				{
					if(sensor.sX <= j && sensor.sX + space >= j)
					{
						done = false;
					}
					else if(sensor.sX > j && j + space >= sensor.sX)
					{
						done = false;
					}
				}
				if(!done)
				{					
					j = sensor.sX + space;
					break;
				}
			}
			
			if(done)
			{
				result = 4000000*j;
				result += i;
				break;
			}
		}
		if(done)
		{
			break;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<Sensor> sensors;

	parseInput(sensors);
	
	resultA = noBeacons(sensors);
	resultB = findBeacon(sensors);

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}

