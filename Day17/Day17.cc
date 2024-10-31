#include <iostream>
#include <fstream>
#include <vector>
#include <array>

void parseInput(std::string &jets)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,jets);
	}
	input.close();
}

void blockFall(const std::string &jets, unsigned &index, std::vector<std::array<char,7>> &chamber, unsigned i, uint64_t &height)
{
	unsigned offset = 2;
	unsigned maxOffset = 0;
	std::array<char,7> layer = {'.','.','.','.','.','.','.'};
	
	switch(i%5)
	{
		case 0:
		{
			maxOffset = 3;
			break;
		}
		case 1:
		case 2:
		{
			maxOffset = 4;
			break;
		}
		case 3:
		{
			maxOffset = 6;
			break;
		}
		case 4:
		{
			maxOffset = 5;
			break;
		}
	}
	for(unsigned j=0; j<4; j++)
	{
		if(jets[index] == '>')
		{
			offset = (offset < maxOffset) ? offset+1 : offset;
		}
		else
		{
			offset = (offset > 0) ? offset-1 : offset;
		}
		index = (index+1)%jets.size();
	}
	
	unsigned currentHeight = height+1;
	bool landed = false;
	
	while(!landed)
	{
		switch(i%5)
		{
			case 0:
			{
				for(unsigned j=0; j<4; j++)
				{
					if(chamber[currentHeight-1][offset+j] != '.')
					{
						landed = true;
						break;
					}
				}
				if(landed)
				{
					for(unsigned j=0; j<4; j++)
					{
						chamber[currentHeight][offset+j] = '#';
					}
					height = (height < currentHeight) ? currentHeight : height;
					while(chamber.size() < height+6)
					{
						chamber.push_back(layer);
					}
				}
				else
				{
					currentHeight--;
					
					if(jets[index] == '<' && offset > 0 && chamber[currentHeight][offset-1] == '.')
					{
						offset--;
					}
					else if(jets[index] == '>' && offset < maxOffset && chamber[currentHeight][offset+4] == '.')
					{
						offset++;
					}
					index = (index+1)%jets.size();
				}
				break;
			}
			case 1:
			{
				if(chamber[currentHeight][offset] != '.' || chamber[currentHeight-1][offset+1] != '.' || chamber[currentHeight][offset+2] != '.')
				{
					landed = true;
				}
				if(landed)
				{
					chamber[currentHeight][offset+1] = '#';
					for(unsigned j=0; j<3; j++)
					{
						chamber[currentHeight+1][offset+j] = '#';
					}
					chamber[currentHeight+2][offset+1] = '#';
					height = (height < currentHeight+2) ? currentHeight+2 : height;
					while(chamber.size() < height+6)
					{
						chamber.push_back(layer);
					}
				}
				else
				{
					currentHeight--;

					if(jets[index] == '<' && offset > 0 && chamber[currentHeight][offset] == '.' && chamber[currentHeight+1][offset-1] == '.' && chamber[currentHeight+2][offset] == '.')
					{
						offset--;
					}
					else if(jets[index] == '>' && offset < maxOffset && chamber[currentHeight][offset+2] == '.' && chamber[currentHeight+1][offset+3] == '.' && chamber[currentHeight+2][offset+2] == '.')
					{
						offset++;
					}
					index = (index+1)%jets.size();
				}
				break;
			}
			case 2:
			{
				if(chamber[currentHeight-1][offset] != '.' || chamber[currentHeight-1][offset+1] != '.' || chamber[currentHeight-1][offset+2] != '.')
				{
					landed = true;
				}
				if(landed)
				{
					for(unsigned j=0; j<3; j++)
					{
						chamber[currentHeight][offset+j] = '#';
					}
					chamber[currentHeight+1][offset+2] = '#';
					chamber[currentHeight+2][offset+2] = '#';
					height = (height < currentHeight+2) ? currentHeight+2 : height;
					while(chamber.size() < height+7)
					{
						chamber.push_back(layer);
					}
				}
				else
				{
					currentHeight--;
					
					if(jets[index] == '<' && offset > 0 && chamber[currentHeight][offset-1] == '.' && chamber[currentHeight+1][offset+1] == '.' && chamber[currentHeight+2][offset+1] == '.')
					{
						offset--;
					}
					else if(jets[index] == '>' && offset < maxOffset && chamber[currentHeight][offset+3] == '.' && chamber[currentHeight+1][offset+3] == '.' && chamber[currentHeight+2][offset+3] == '.')
					{
						offset++;
					}
					index = (index+1)%jets.size();
				}
				break;
			}
			case 3:
			{
				if(chamber[currentHeight-1][offset] != '.')
				{
					landed = true;
				}
				if(landed)
				{
					for(unsigned j=0; j<4; j++)
					{
						chamber[currentHeight+j][offset] = '#';
					}
					height = (height < currentHeight+3) ? currentHeight+3 : height;
					while(chamber.size() < height+5)
					{
						chamber.push_back(layer);
					}
				}
				else
				{
					currentHeight--;
					
					if(jets[index] == '<' && offset > 0 && 
						chamber[currentHeight][offset-1] == '.' && 
						chamber[currentHeight+1][offset-1] == '.' && 
						chamber[currentHeight+2][offset-1] == '.' && 
						chamber[currentHeight+3][offset-1] == '.')
					{
						offset--;
					}
					else if(jets[index] == '>' && 
						offset < maxOffset && chamber[currentHeight][offset+1] == '.' && 
						chamber[currentHeight+1][offset+1] == '.' && 
						chamber[currentHeight+2][offset+1] == '.' && 
						chamber[currentHeight+3][offset+1] == '.')
					{
						offset++;
					}
					index = (index+1)%jets.size();
				}
				break;
			}
			case 4:
			{
				if(chamber[currentHeight-1][offset] != '.' || chamber[currentHeight-1][offset+1] != '.')
				{
					landed = true;
				}
				if(landed)
				{
					for(unsigned j=0; j<2; j++)
					{
						for(unsigned k=0; k<2; k++)
						{
							chamber[currentHeight+j][offset+k] = '#';
						}
					}
					height = (height < currentHeight+1) ? currentHeight+1 : height;
					while(chamber.size() < height+4)
					{
						chamber.push_back(layer);
					}
				}
				else
				{
					currentHeight--;
					
					if(jets[index] == '<' && offset > 0 && chamber[currentHeight][offset-1] == '.' && chamber[currentHeight+1][offset-1] == '.')
					{
						offset--;
					}
					else if(jets[index] == '>' && offset < maxOffset && chamber[currentHeight][offset+2] == '.' && chamber[currentHeight+1][offset+2] == '.')
					{
						offset++;
					}
					index = (index+1)%jets.size();
				}
				break;
			}
		}
	}
}

uint64_t blockFall(const std::string &jets)
{
	uint64_t result = 0;
	
	uint64_t height = 0;
	unsigned index = 0;
	
	std::vector<std::array<char,7>> chamber;
	chamber.reserve(4000);
	chamber.push_back({'-','-','-','-','-','-','-'});
	std::array<char,7> layer = {'.','.','.','.','.','.','.'};
	for(unsigned i=0; i<4; i++)
	{
		chamber.push_back(layer);
	}
	
	for(unsigned i=0; i<2022; i++)
	{
		blockFall(jets, index, chamber, i, height);
	}
	
	result = height;
	
	return result;
}

uint64_t manyBlocks(const std::string &jets)
{
	uint64_t result = 0;
	
	uint64_t height = 0;
	unsigned index = 0;
	
	std::vector<std::array<char,7>> chamber;
	chamber.reserve(4000);
	chamber.push_back({'-','-','-','-','-','-','-'});
	std::array<char,7> layer = {'.','.','.','.','.','.','.'};
	for(unsigned i=0; i<4; i++)
	{
		chamber.push_back(layer);
	}
	
	std::vector<std::vector<unsigned>> cache;
	std::vector<unsigned> line;
	unsigned lastIndex = 0;
	bool loopFound = false;
	uint64_t loopStart = 0;
	uint64_t loopStartHeight = 0;
	uint64_t loopSize = 0;
	uint64_t loopHeight = 0;
	
	bool done = false;
	
	for(uint64_t i=0; i<1000000000000; i++)
	{
		if(index < lastIndex)
		{
			bool found = false;
			for(auto &cLine:cache)
			{
				if(cLine.size() == line.size())
				{
					found = true;
					for(unsigned i=0; i<line.size(); i++)
					{
						if(line[i] != cLine[i])
						{
							found = false;
							break;
						}
					}
					if(found)
					{
						if(!loopFound)
						{
							loopFound = true;
							loopStart = i;
							loopStartHeight = height;
							cache.clear();
							break;
						}
						else
						{
							loopSize = i - loopStart;
							loopHeight = height - loopStartHeight;
							done = true;
							break;
						}
					}
				}
			}
			cache.push_back(line);
			line.clear();	
		}
		else
		{
			line.push_back(index);
		}
		if(done)
		{
			break;
		}
		lastIndex = index;
		
		blockFall(jets, index, chamber, i, height);
	}
	
	uint64_t loops = (1000000000000-loopStart)/loopSize;
	uint64_t loopsDone = loopStart + (loops*loopSize);
	uint64_t left = 1000000000000 - loopsDone;
	
	for(uint64_t i=(loopsDone%5); i<left+(loopsDone%5); i++)
	{
		blockFall(jets, index, chamber, i, height);
	}
	height += (loops-1)*loopHeight;
	
	result = height;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::string jets;

	parseInput(jets);
	
	resultA = blockFall(jets);
	resultB = manyBlocks(jets);

	std::cout << "result A: " << resultA << '\n';
	std::cout << "result B: " << resultB << std::endl;
	return 0;
}

