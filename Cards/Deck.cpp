#include "Deck.h"
#include <ctime>
#include "..\Player\Player.h"
Deck::Deck() {
	mainDeck = new std::vector<Card*>;
	boardCards = new std::vector<Card*>;
	mainDeck->push_back(new Card(std::string("crystal"),		std::string("place 2 armies")));
	mainDeck->push_back(new Card(std::string("crystal"),		std::string("place 2 armies")));
	mainDeck->push_back(new Card(std::string("crystal"),		std::string("place 2 armies")));
	mainDeck->push_back(new Card(std::string("crystal"),		std::string("place 1 army")));
	mainDeck->push_back(new Card(std::string("crystal"),		std::string("moveLand 2 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("moveSea 2 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("moveSea 2 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("moveSea 3 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("moveLand 2 armies")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("place 3 armies | building_city    |")));
	mainDeck->push_back(new Card(std::string("stone"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("moveLand 5 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("moveLand 4 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("building_city")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("destory 1 army & building_city &")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("building_city")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("moveLand 4 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("place 4 armies | moveLand 2 armies |")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("moveSea 3 armies")));
	mainDeck->push_back(new Card(std::string("carrot"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("carrot_double"),	std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("moveLand 3 armies")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("place 2 armies | moveLand 3 armies |")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("destory 1 army & building_city &")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("moveLand 6 armies")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("moveLand 3 armies")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("moveSea 4 armies")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("building_city")));
	mainDeck->push_back(new Card(std::string("tree"),			std::string("moveSea 3 armies")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("place 3 armies")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("moveLand 3 armies")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("building_city")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("place 3 armies | moveLand 3 armies |")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("moveLand 4 armies")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("place 3 armies | moveLand 4 armies |")));
	mainDeck->push_back(new Card(std::string("bridge"),			std::string("moveLand 5 armies")));
	mainDeck->push_back(new Card(std::string("bridge_double"),	std::string("moveLand 4 armies")));
	mainDeck->push_back(new Card(std::string("wild"),			std::string("moveSea 2 armies")));
	mainDeck->push_back(new Card(std::string("wild"),			std::string("moveSea 2 armies")));
	mainDeck->push_back(new Card(std::string("wild"),			std::string("place 2 armies")));
}

Deck::~Deck() {
	for (size_t i = 0; i < mainDeck->size();i++) {
		delete mainDeck->at(i);
		mainDeck = NULL;
	}
	delete mainDeck;
	mainDeck = NULL;
}


 void Deck::addCard(Card* card) {
	mainDeck->push_back(card);
}

 std::vector <Card*>* Deck::getBoardCards() {
	 return this->boardCards;
 }

 Card* Deck::draw(int i) {  
	Card* temp = (boardCards->at(i));
	this->boardCards->erase(this->boardCards->begin()+i);
	this->boardCards->push_back(mainDeck->at(0));
	this->mainDeck->erase(mainDeck->begin());
	return temp;
}


 void Deck::initBoardCards() {

	 for (int i = 0; i < 6; i++) {
		 this->boardCards->push_back(mainDeck->at(0));
		 this->mainDeck->erase(mainDeck->begin());
	 }
 }


 void Deck::shuffle()
 {
	 int tempInt2 = static_cast<int> (this->mainDeck->size()); 
	 std::vector<Card*>* temp = new std::vector < Card*>;
	 std::srand((unsigned int)std::time(0));
	 for (size_t i = 0; i < tempInt2; i++) {
		 int tempInt = static_cast<int> (this->mainDeck->size());
		 int iSecret = rand() % tempInt;
		 temp->push_back(mainDeck->at(iSecret));
		 mainDeck->erase(mainDeck->begin() + iSecret);
	 }
	 this->mainDeck = temp;
	 temp = NULL;
 }


 Card* Deck::isPossibleDrawCard(int indexChosen) { // in order to chech if it is possible to draw according to the action
	 return boardCards->at(indexChosen - 1);
 }

 void Deck::show() {
	 int arr[6] = {0,1,1,2,2,3};
	 for (size_t i = 0; i < this->boardCards->size(); i++) {
		 std::cout << i+1 << "- " << boardCards->at(i)->getGoods() << " " <<
			 (boardCards->at(i))->getAction() << "(cost: "<<arr[i]<<" Coins)"<<std::endl;
	 }
	 std::cout << "*********************************\n";
 }

 void Deck::show2() {
	 for (size_t i = 0; i < this->mainDeck->size(); i++) {
		 std::cout << mainDeck->at(i)->getGoods() << " " <<
			 (mainDeck->at(i))->getAction() << std::endl;
	 }
	 std::cout << "*********************************\n";
 }
