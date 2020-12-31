#ifndef HUMAN_H
#define HUMAN_H
#include "PlayerAction.h"
class Human : public PlayerAction
{
public:

	Human();
	void placeNewArmies(std::string color, std::vector<Country*>* owned, Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace);
	void moveOverLand(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving);
	bool Ignore();
	void moveOverSea(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving);
	void buildCity(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr);
	void destroyArmy(std::string color, std::vector<Country*>* owned, Map* map, std::string* countryStr, std::string* enemyColor);
	bool selectCard(std::string color, int index, int& coins, Hand* hand, std::vector<Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer, std::string* message);
	void doAction(std::string color, Map* map, std::vector<Country*>* owned, std::string actionString, std::string* changedCountry, std::string* changedPlayer);
	bool possibleAction(std::string actionString, Map* map, std::string color, std::vector<Country*>* owned);
	int askUserForCard(std::string color, int& coins);
	int getCardCost(int choice, std::string color, int& coins);
};
#endif HUMAN_H
