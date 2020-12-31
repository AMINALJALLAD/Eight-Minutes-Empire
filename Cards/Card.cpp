#include "Card.h"

	Card::Card(std::string good_, std::string action_) {
		goods = new std::string(good_);
		action = new std::string(action_);
	}

	Card::Card() {
		goods = new std::string("No goods yet");
		action = new std::string("No Action yet");
	}

	Card::~Card() {
		delete  goods;
		delete action;
		goods = NULL;
		action = NULL;
	}

	std::string Card::getGoods() {
		return (*goods);
	}

	std::string Card::getAction() {
		return  (*action);
	}
	



	
	


	