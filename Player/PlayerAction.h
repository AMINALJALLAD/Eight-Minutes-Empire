#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Deck.h"
#include "Map.h"
#include "Hand.h"
#include "GameObservers.h"

class PlayerAction
{
public:	
	void MoveArmies(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str);

	bool isValidArmyPlace(std::string color, Map* world, std::string countryStr, Country* wanted);

	bool isValidmovingOverLand(Map* world, std::string origin_str, std::string destination_str, std::string color);

	bool isValidmovingOverSea(Map* world, std::string origin_str, std::string destination_str, std::string color);
	
	virtual void placeNewArmies(std::string color, std::vector<Country*>* owned, Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace) = 0;
		
	virtual void moveOverLand(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving) = 0;
	
	virtual bool Ignore() = 0;
		
	virtual void moveOverSea(std::string color, std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving) = 0;
		
	virtual void buildCity(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr) = 0;
	
	bool isPossiblebuildCity(std::string color, Map* world, Country* wanted);

	bool isPossibleDestroyArmy(Map* world, Country* wanted, std::string enemyColor, int& index);

	void payCoin(int& coins, int payment);
	
	virtual void destroyArmy(std::string color, std::vector<Country*>* owned, Map* map, std::string* countryStr, std::string* enemyColor) = 0;
	
	virtual bool selectCard(std::string color, int index, int& coins, Hand* hand, std::vector<Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer, std::string* message) = 0;
};
#endif PLAYERACTION_H
