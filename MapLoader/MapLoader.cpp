#include "MapLoader.h"

#include<fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> getArray(std::string s) {
	char ch;
	std::string temp;
	std::vector<std::string> arrayString;
	int ind{ 0 };
	for (size_t i = 0; i < s.length(); i++) {
		ch = s.at(i);
		if (ch != ',') {
			temp += ch;
		}
		else {
			temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
			arrayString.push_back(temp);
			ind++;
			temp = "";
		}
	}
	temp.erase(std::remove_if(temp.begin(), temp.end(), ::isspace), temp.end());
	arrayString.push_back(temp);
	ind++;
	temp = "";
	return arrayString;
}

//MapLoader::~MapLoader() {
//
//}

bool MapLoader::fileOpener(std::ifstream& inFile)
{
	inFile.open(*(this->directory));
	return inFile.good();
}

std::string MapLoader::getDirectory()
{
	return *(this->directory);
}

Map* MapLoader::fileLoader(std::ifstream& inFile)
{
	Map* world = Map::getInstance();
	//Map* world = new Map();

	bool record = false;
	std::vector<std::string> splitted;
	std::string name, line,tempString,oldContinent;
	Continent* tempContinent = new Continent ("",NULL);
	Country* tempCountry = new Country ("", NULL);
	oldContinent = " ";
	while (std::getline(inFile, line)) {
		if (line.find("Territories") != std::string::npos || record) {
			record = true;
			if (line.empty()|| line.find("Territories") != std::string::npos)
				continue;
			else {
				splitted = getArray(line);
				for (size_t i = 0; i < splitted.size(); i++) {

					if (i == 0)
						tempString = splitted[i];
					else if (i == 1) {
						if (oldContinent.compare(splitted[i]) != 0) {
							oldContinent = splitted[i];
							tempContinent = world->addContinent(splitted[i]);
							if (tempString.find("#") != std::string::npos) {
								tempCountry = tempContinent->addCountry(tempString.substr(1));
								world->setStart(tempCountry);
							}
							else
								tempCountry = tempContinent->addCountry(tempString);
						}
						else {
							if (tempString.find("#") != std::string::npos) {
								tempCountry = tempContinent->addCountry(tempString.substr(1));
								world->setStart(tempCountry);
							}
							else
								tempCountry = tempContinent->addCountry(tempString);
						}
					}
					else if( i > 1){

						if (splitted[i].find("*") != std::string::npos) {
							world->addSeaBorder(tempContinent, tempCountry, world->findCountry(splitted[i].substr(1)));
						}
						else {
							if (world->findCountry(splitted[i]) != NULL || world->findCountry(splitted[i].substr(1)) != NULL) {
								world->addLandBorder(tempContinent, tempCountry, splitted[i]);
							}
						}
						
					}
					
				}
			}
		}
	}
	return world;
}

MapLoader::MapLoader(std::string directory)
{
	this->directory = new std::string(directory);
}
