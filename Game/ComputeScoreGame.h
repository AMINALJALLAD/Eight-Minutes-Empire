#ifndef COMPUTESCOREGAME_H
#define COMPUTESCOREGAME_H
#include "MainLoop.h"

class ComputeScoreGame : public MainLoop
{
public:
	ComputeScoreGame();
	~ComputeScoreGame();
	void computeScores();
	void getNumOfPoints(Map* board); // for both countries and continents
	void printScores();
	int getCardPoints(std::vector<Card*>* cards);
	int getGoodsPoints();
	int getIndextOfArray(char fisrtChar);
	void whoDominantCountry();
	int getIndexOfMaxValur(int* ptr);
	void whoDominantConinent();
	void startOver(int* ptr);  //set all values of the array to zero
	void intializeColorArray();
	void printInt(int* p);
	void printChar(char* p);
	void whichColorDominientCountry(std::vector<std::string>* armies);
	void whoWins();
	//void barGraph();
	//void print(int* p);
	/*void update();
	void whoDominantCountry(Country* country);
	void whoDominantConinent(Continent* continent);
	void barGraph();*/
private:
	int* temp;   // for puposes inside the methods
	int* tempOfConuntriesPoints;   // for trace who gets the coninent dominant
	int numOfPlayers;
	int* playersScores;
	char* arrayOfChar;
	int* pointsOfGoods;
	std::vector<std::string*>* colorOfPlayers;
	int* pointsOfCountries; // an array of points of each player for how many countries that he has 
	int* pointsOfContinent;  // an array of points of each player for how many continents that he has 
	std::vector<std::vector<std::string>*>* playersOwned;
};
#endif COMPUTESCORE_H
