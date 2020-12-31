#include "BidingFacility.h"
#include <iostream>

BidingFacility::BidingFacility() {
	bidCoin = new int(-1);
}

BidingFacility::~BidingFacility() {
	delete bidCoin;
}

BidingFacility::BidingFacility(int bidCoin) {
	this->bidCoin = new int(bidCoin);
}

void BidingFacility::show() {
	std::cout << getBid()<<"\n";
}

int BidingFacility::getBid(){
	return *bidCoin;
}

