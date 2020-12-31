#include "StartUp.h"

StartUp::StartUp():GamePlay()
{
	initializeDeck();
	initializeArmies();
	initializeBids();
	Player* winner = findBidwinner(*this->gameStart->getPlayers());
	declareBidWinner(winner);
	int index = 0;
	while (gameStart->getPlayers()->at(index)->getColor().compare(winner->getColor()) != 0)
		index++;
	this->gameStart->getPlayers()->erase(this->gameStart->getPlayers()->begin() + index);
	this->gameStart->getPlayers()->insert(this->gameStart->getPlayers()->begin() , winner);
}

void StartUp::declareBidWinner(Player* winner) {
	for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
		std::cout << "The "<< gameStart->getPlayers()->at(i)->getColor()<<" player bidded the amount of: " 
			<< gameStart->getPlayers()->at(i)->getBid()->getBid() << std::endl;
	}
	std::cout << "\nThe winner of the Bid is " << winner->getColor() << "; The points have been deducted from him\n\n";
	winner->payCoin(winner->getBid()->getBid());
}

void StartUp::initializeDeck() {
	//this->gameStart->getDeck()->show2();
	this->gameStart->getDeck()->shuffle();
	//this->gameStart->getDeck()->show2();
	this->gameStart->getDeck()->initBoardCards();
}

void StartUp::initializeArmies() {
	for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
		gameStart->getPlayers()->at(i)->placeNewArmies2(gameStart->getMap(), gameStart->getMap()->getStart()->getName(), 3, true);
	}
	if (this->gameStart->getNoPlayers() == 2) {
		Player* fake = new Player("fake", 99, new Greedy());
		for (int i = 0; i <10 ; i++) {
			fake->placeNewArmies(gameStart->getMap(), gameStart->getMap()->getRandom(), true);
		}
	}
}


void StartUp::initializeBids() {
	for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
		gameStart->getPlayers()->at(i)->setBid();
	}
}

Player* StartUp::findBidwinner(std::vector<Player*> players) {
	int max = gameStart->getPlayers()->at(0)->getBid()->getBid();
	std::vector<Player*> maxbids;
	for (size_t i = 1; i < players.size(); i++) {
		if (max < players[i]->getBid()->getBid())
			max = players[i]->getBid()->getBid();
	}
	for (size_t i = 0; i < players.size(); i++) {
		if (max == players[i]->getBid()->getBid())
			maxbids.push_back(players[i]);
	}
	if (maxbids.size() < 2)
		return maxbids[0];
	else {
		Player* youngest = maxbids[0];
		int minage = maxbids[0]->getAge();
		std::cout << "there's a tie in the bids between " << maxbids.size() <<" players;therefore, the youngest" <<
			"Player wins!" << std::endl;
		for (size_t i = 1; i < maxbids.size(); i++) {
			if (minage > maxbids[i]->getBid()->getBid())
				youngest = maxbids[i];
		}
		return youngest;
	}
}


