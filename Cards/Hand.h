#ifndef HAND_H
#define HAND_H

#include "Deck.h"

class Hand {
public:
	Hand();
	~Hand();
	void exchange(Deck* deck_, int deckPosition);
	void addCard(Card* card);
	void show();  
	std::vector<Card*>* getMyCards();

private:
	std::vector<Card*>* myCards;
};
namespace amin{
	bool isValidPosition(int position);
	int getCost(int ind);
	int slectPosition();
}
#endif

