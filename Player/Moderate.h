#ifndef MODERATE_H
#define MODERATE_H
#include "PlayerAction.h"
class Moderate : public PlayerAction
{
public:
	Moderate();
	void placeNewArmies(std::string color, std::vector<Country*>* owned, Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace);
	void moveOverLand(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving);
	bool Ignore();
	void moveOverSea(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving);
	void buildCity(std::string color, std::vector<Country*>* owned, Map* world, std::string countryStr);
	void destroyArmy(std::string color, std::vector<Country*>* owned, Map* map, std::string* countryStr, std::string* enemyColor);
	bool selectCard(std::string color, int index, int& coins, Hand* hand, std::vector<Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer, std::string* message);
	//bool selectCard(std::string color, int index, int& coins, Hand* hand, std::vector<Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer);
	void doAction(std::string color, Map* map, std::vector<Country*>* owned, std::string actionString, std::string* changedCountry, std::string* changedPlayer);
	bool possibleAction(std::string actionString, Map* map, std::vector<Country*>* owned, std::string color);
	bool hasBuild(Deck* deck, int& index);
	bool hasDestroy(Deck* deck, int& index);
	bool hasMoveSea(Deck* deck, int& index);
	bool hasMoveLand(Deck* deck, int& index);
	bool hasplace(Deck* deck, int& index);
	int getCardCost(int choice);
	bool contains(std::vector<std::string>* someVector, std::string value);
	bool someCardPlayable(Deck* deck, int& coins, Map* map, std::vector<Country*>* owned, std::string color);
	std::vector<Card*>* getCardPlayable(Deck* deck, int& coins, Map* map, std::vector<Country*>* owned, std::string color);
	int getIndex(std::vector<Card*>* boardCards, Card* card);
};
#endif MODERATE_H
