#include "Hand.h"

Hand::Hand() {
	myCards = new std::vector<Card*>;
}

bool amin::isValidPosition(int position) {
	return (position >= 1) && (position <= 6);
}

void Hand::addCard(Card* card) {
	myCards->push_back(card);
}

Hand::~Hand() {
	for (size_t i = 0; i < myCards->size();i++) {
		delete myCards->at(i);
		myCards->at(i) = NULL;
	}
	delete myCards;
	myCards = NULL;
}

void Hand::show() {
	std::cout << "the number of cards in hand is: " << myCards->size()<<"\n";
	for (size_t i = 0; i < myCards->size(); i++)
		std::cout << myCards->at(i)->getAction() << " , " << myCards->at(i)->getGoods() << std::endl;
}

std::vector<Card*>* Hand::getMyCards()
{
	return myCards;
}

void Hand::exchange(Deck* deck_,int deckPosition) {
	Card* cardFromDeck = deck_->draw(deckPosition);
	myCards->push_back(cardFromDeck);
}

