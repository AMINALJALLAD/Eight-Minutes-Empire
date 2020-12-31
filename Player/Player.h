#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Deck.h"
#include "BidingFacility.h"
#include "Hand.h"
#include "PlayerAction.h"
#include "Greedy.h"
#include "Moderate.h"
#include "Human.h"
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include "GameObservers.h"

class Player :public Subject {

public:
	Player (std::string color, int age, PlayerAction* strategy);
	void setStrategy(PlayerAction* strategy);
	Player();
	void payCoin(int payment);
	void buyCard(Deck* deck);
	BidingFacility* getBid();
	Hand* getHand();
	std::string getColor();
	int getCubes();
	int getDiscs();
	void setCoin(int* bank); 
	int getCoin(); 
	int getAge();
	//bool selectCard(int index, Map* map, Deck* deck);
	bool selectCard(int index, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer);
	bool isValidBid(int bidCoin);
	void setBid(); 
	void printPlayer();
	void placeNewArmies(Map* map, std::string name, bool old);
	void placeNewArmies2(Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace);
	PlayerAction* strategy;
	std::vector<Country*>* getOwned();
	bool isPossibuyCard(int avaiableCoins, int cardCost);


private:
	std::string* color;
	int* cubes;
	int* discs;
	int* coins;
	Hand* myHand;
	BidingFacility* tools;
	std::vector <Country*>* owned;
	int* age; 
	static int noPlayers;
};

#endif // !PLAYER_H