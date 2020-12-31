#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
	public:
		Deck();
		void show();
		void show2();
		~Deck();
		void addCard(Card* card_);
		std::vector<Card*>* getBoardCards();
		Card* draw(int i);
		void initBoardCards();
		void shuffle();
		Card* isPossibleDrawCard(int indexChosen);
	private:
		std::vector<Card*>* mainDeck;
		std::vector<Card*>* boardCards;

};
#endif

