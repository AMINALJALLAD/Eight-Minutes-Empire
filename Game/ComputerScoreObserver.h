#ifndef COMPUTESCOREOBSERVER_H
#define COMPUTESCOREOBSERVER_H
#include "GameObservers.h"
#include "GameStart.h"

class ComputeScoreObserver : public Observer
{
public:
	ComputeScoreObserver();
	ComputeScoreObserver(GameStart* gameStart);
	~ComputeScoreObserver();
	void computeScores();
	void IntializeAgain();
	void getNumOfPoints(Map* board); // for both countries and continents
	void printScores();
	int getCardPoints(std::vector<Card*>* cards);
	int getGoodsPoints();
	int getIndextOfArray(char fisrtChar);
	void whichColorDominientCountry(std::vector<std::string>* armies);
	void whoDominantCountry(Country* country);
	int getIndexOfMaxValur(int* ptr);
	void whoDominantConinent(Continent* continent);
	void startOver(int* ptr);  //set all values of the array to zero
	void intializeColorArray();
	void printInt(int* p);
	void printChar(char* p);
	void whoWins();
	int findMinimum();
	void minimumPlayerPossession(int ind);
	void Update(std::string message); // Update(std::string message)
	void barGraph();
	//bool isFirstTime();
	//void setFirstTime(bool time);
	//void print(int* p);

private:
	//bool firstTime;
	GameStart* gameStart;
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
