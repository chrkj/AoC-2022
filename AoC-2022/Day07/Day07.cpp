#include "Day07.h"
#include <Utils/Utils.h>

#define INPUT "Day07/1.IN"
#define MAX_SIZE 100000
#define TOTAL_DISK_SPACE 70000000
#define DISK_SPACE_NEEDED 30000000

struct Node
{
	int64_t size;
	std::string name;
	Node* parent;
	std::vector<std::shared_ptr<Node>> children;
	
	Node(std::string name, int64_t size, Node* parent)
		: name(name), size(size), parent(parent) 
	{}
};

void updateDirSizes(Node* currentNode, int64_t size)
{
	while (currentNode->parent != nullptr)
	{
		currentNode->size += size;
		currentNode = currentNode->parent;
	}
	currentNode->size += size;
}

inline std::vector<std::shared_ptr<Node>> createDirs()
{
	std::ifstream input(INPUT);

	std::shared_ptr<Node> rootNode = std::make_shared<Node>( "/", 0, nullptr );
	Node* currentNode = rootNode.get();
	std::vector<std::shared_ptr<Node>> directories;
	directories.push_back(rootNode);

	std::string currentLine;
	getline(input, currentLine); // Skip first line (already setup)
	while (getline(input, currentLine))
	{
		switch (currentLine[0])
		{
		case '$':
			if (currentLine[2] == 'c')
			{
				std::string dir = currentLine.substr(5);
				if (dir == "..")
				{
					currentNode = currentNode->parent;
				}
				else
				{
					auto loc = std::find_if(
						currentNode->children.begin(),
						currentNode->children.end(),
						[&dir](const std::shared_ptr<Node> obj) {return obj->name == dir; });

					if (loc != currentNode->children.end())
						currentNode = loc->get();
				}
			}
			break;
		default:
			// Add File or Folder to current Node
			std::vector<std::string> data = Utils::split_string(currentLine, ' ');
			if (data[0] == "dir")
			{
				auto dir = std::make_shared<Node>(data[1], 0, currentNode);
				currentNode->children.push_back(dir);
				directories.push_back(dir);
			}
			else
			{
				currentNode->children.push_back(std::make_shared<Node>(data[1], std::stoi(data[0]), currentNode));
				updateDirSizes(currentNode, std::stoi(data[0]));
			}
			break;
		}
	}
	return directories;
}

void Day07::part1()
{
	ScopedTimer timer;

	int64_t sum = 0;
	for (auto dir : createDirs())
	{
		if (dir->size < MAX_SIZE) 
			sum += dir->size;
	}
	printf("Sum: %d", sum);
}

void Day07::part2()
{
	ScopedTimer timer;

	auto dirs = createDirs();
	int64_t spaceToBeFreed = DISK_SPACE_NEEDED - (TOTAL_DISK_SPACE - dirs[0]->size);

	int64_t sizeOfDirToDelete = TOTAL_DISK_SPACE;
	for (auto dir : dirs)
	{
		int64_t dirSize = dir->size;
		if (dirSize >= spaceToBeFreed && dirSize < sizeOfDirToDelete)
			sizeOfDirToDelete = dirSize;
	}
	printf("Size of dir to delete: %d", sizeOfDirToDelete);
}