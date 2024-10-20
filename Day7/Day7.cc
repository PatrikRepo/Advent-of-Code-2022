#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


struct File
{
	std::string name;
	unsigned size = 0;
	std::optional<std::vector<File>> files;
	File *parent = 0;
};

void setDirSize(File &dir)
{
	for(auto &file:*dir.files)
	{
		if(file.files)
		{
			setDirSize(file);
		}
		dir.size += file.size;
	}
}	

void parseInput(File &root)
{
	std::string line;
  std::ifstream input("input.txt");

  if(input.is_open())
  {	
  	getline(input,line);
  	root.name = "/";
  	root.files = std::vector<File>();
  	File* filePtr = &root;
		while(getline(input,line))
		{
			if(line[0] == '$')
			{
				if(line[2] == 'c')
				{
					if(line[5] == '.')
					{
						filePtr = filePtr->parent;
					}
					else
					{
						std::string name = line.substr(5);
						filePtr = &(*(std::find_if(filePtr->files->begin(), filePtr->files->end(), [name](File &file){ return name == file.name; })));
					}
				}
			}
			else if(line[0] >= '0' && line[0] <= '9')
			{
				File newFile;
				size_t pos = line.find_first_of(" ");
				newFile.size = std::stoi(line.substr(0,pos));
				newFile.name = line.substr(pos+1);
				filePtr->files->push_back(newFile);
			}
			else
			{
				File newFile;
				size_t pos = line.find_first_of(" ");
				newFile.name = line.substr(pos+1);
				newFile.parent = filePtr;
				newFile.files = std::vector<File>();
				filePtr->files->push_back(newFile);
			}
		}
  }
  
  setDirSize(root);
  
  input.close();
}

uint64_t sumDirSize(const File &directory)
{
	uint64_t result = 0;
	
	if(directory.size <= 100000)
	{
		result += directory.size;
	}
	
	for(auto &dir:*directory.files)
	{
		if(dir.files)
		{
			result += sumDirSize(dir);
		}
	}
	
	return result;
}

uint64_t findSmallest(const File &directory, unsigned target)
{
	uint64_t result = 0;
	
	if(directory.size >= target)
	{
		result = directory.size;
		for(auto &dir:*directory.files)
		{
			if(dir.files)
			{
				unsigned newResult = findSmallest(dir, target);
				if(newResult >= target)
				{
					result = (newResult < result) ? newResult : result;
				}
			}
		}
	}

	return result;
}

uint64_t findSmallest(const File &root)
{
	uint64_t result = 0;
	
	result = findSmallest(root, 30000000 - (70000000 - root.size));
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB;

	File root;
	
  parseInput(root);

	resultA = sumDirSize(root);
 	resultB = findSmallest(root);

  std::cout << "resultA: " << resultA << '\n';
  std::cout << "resultB: " << resultB << std::endl;
  
  return 0;
}
