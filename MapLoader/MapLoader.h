#ifndef MAPLOADER_H
#define MAPLOADER_H
#include "Map.h"
#include<fstream>
#include <iostream>
#include <string>
//#include <boost/algorithm/string.hpp>
#include <vector>
class MapLoader
{
public:
	std::string getDirectory();
	Map* fileLoader(std::ifstream& inFile);
	bool fileOpener(std::ifstream& inFile);
	MapLoader(std::string directory);
private:
	std::string* directory;
};
#endif