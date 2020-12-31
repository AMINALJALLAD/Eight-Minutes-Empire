#ifndef STARTUP_H
#define STARTUP_H

#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "MapLoader.h"
#include "GamePlay.h"

class StartUp : public GamePlay {
public:

	StartUp();
	void declareBidWinner(Player* winner);
	Player* findBidwinner(std::vector<Player*> players);
	void initializeDeck();
	void initializeArmies();
	void initializeBids();


private:
	//std::vector <Card*> *boardCards;
};
#endif

