#include "Player.h"
#include <ctime>
#include<vector>
int Player::noPlayers = 0;

Player::Player() {
	color = new std::string("no color");
	myHand = new Hand();
	owned = new std::vector<Country*>();
	cubes = new int(3);
	discs = new int(14);
	coins = new int(0);
	this->strategy = new Human();
	noPlayers++;
	tools = new BidingFacility();
	age = new int(0);
}

void Player::payCoin(int payment)
{
	*(this->coins) -= payment;
}

Player::Player(std::string color_,int age, PlayerAction* strategy) {
	color = new std::string(color_);
	myHand = new Hand();
	owned = new std::vector<Country*>();
	cubes = new int(3);
	discs = new int(14);
	coins = new int(0);
	tools = new BidingFacility();
	this->age = new int (age);
	noPlayers++;
	this->strategy = strategy;
}

void Player::setStrategy(PlayerAction* strategy) {
	this->strategy = strategy;
}

//Player::~Player() {
//	delete cubes;
//	delete discs;
//	delete coins;
//	Hand* myHand;
//	delete tools;
//	for (int i = 0; i < owned->size(); i++) {
//		delete owned->at(i);
//	}
//	delete owned;
//	delete age;
//	
//}

bool Player::selectCard (int index, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer) {

	std::string* message = new std::string("");
	if (this->strategy->selectCard(*color, index, *coins, myHand, owned, map, deck, changedCountry, changedPlayer, message))
	{
		Notify(*message);
		this->printPlayer();
		return true;
	}
	return false;
}

bool isValidAge(int age) {
	return ((age >= 8) && (age <= 100));
}

bool Player::isValidBid(int bidCoin) {
	return ((bidCoin >= 0) && (bidCoin <= *(this->coins)));
}

void Player::setBid(){
	int bidNum = 0;
	bool done = false;
	if (this->color->compare("comp") == 0) {
		std::cout << "\nThe computer made her bid; once all players make their bids i will reveal the winner!\n\n";
		int bidSecret = rand() % *(this->coins);
		this->tools = new BidingFacility(bidSecret);
	}
	else {
		do {
			std::cout << "Enter a bid between 0 and " << *(this->coins) << ", such that other players donesn't know your bid: ";
			std::cin >> bidNum;
			if (isValidBid(bidNum)) {
				this->tools = new BidingFacility(bidNum);
				std::cout << "\nThanks, Your bid was recorded once all players make their bid i will reveal the winner!\n\n";
				done = true;
			}
			else {
				std::cout << "\nYou should enter a valid bid";
			}
		} while (!done);
	}
}


void Player::setCoin(int* bank) {
	switch (Player::noPlayers) {
	case 5:
		*(this->coins) = 8;
		*bank -= *(this->coins);
		break;
	case 4:
		*(this->coins) = 9;
		*bank -= *(this->coins);
		break;
	case 3:
		*(this->coins) = 11;
		*bank -= *(this->coins);
		break;
	default:
		*(this->coins) = 14;
		*bank -= *(this->coins);
		break;
	}
}

int Player::getAge() { 
	return *age;
}

int Player::getCoin() {  
	return *(this->coins);
}


std::vector<Country*>* Player::getOwned() {
	return owned;
}


bool Player::isPossibuyCard(int avaiableCoins, int cardCost) {
	return (avaiableCoins >= cardCost);
}

void Player::buyCard(Deck* deck)
{
	bool done = false;
	do {
		int deckPosition = amin::slectPosition();
		int costOfCard = amin::getCost(deckPosition);
		done = isPossibuyCard(this->getCoin(), costOfCard);
		if (!done) {
			std::cout << "Sorry you don't have sufficient money to buy this card";
			continue;
		}
		else {
			this->myHand->exchange(deck, deckPosition);
			this->payCoin(costOfCard);
		}
	}while (!done);
}

BidingFacility* Player::getBid()
{
	return this->tools;
}
Hand* Player::getHand()
{
	return this->myHand;
}
std::string Player::getColor()
{
	return *(this->color);
}
int Player::getCubes()
{
	return *this->cubes;
}
int Player::getDiscs()
{
	return *this->discs;
}
int amin::slectPosition() {
	int position = 0;
	std::cout << "Enter a position for the card you wish to draw from 1 to 6";
	bool done = false;
	do {
		std::cin >> position;
		if (isValidPosition(position)) {
			done = true;
		}
		else {
			std::cout << "You should enter a valid Position";
		}
	} while (!done);
	return position;
}
int amin::getCost(int Position) {
	switch (Position) {
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 1;
	case 4:
		return 2;
	case 5:
		return 2;
	case 6:
		return 3;
	default:
		return -1;

	}
}
void Player::printPlayer() 
{
	std::cout << "My color is: " << this->getColor() << "\n";
	std::cout << "My age is: " << this->getAge() << "\n";
	std::cout << "The number of coins I have are: " << this->getCoin() << "\n";
	std::cout << "The countries where i have armies or Cities are:( ";
	for (size_t i = 0; i < owned->size(); i++)
		std::cout << owned->at(i)->getName() << ", ";
	std::cout << ")\n\n\n";
}
void Player::placeNewArmies(Map* world, std::string countryStr, bool samePlace) {
	int iteration = 0; bool valid = true; Country* wanted = NULL;
	countryStr = world->getRandom();
	wanted = world->findCountry(countryStr);
	wanted->getArmies()->push_back(this->getColor());
	this->getOwned()->push_back(wanted);
	iteration++;
}
void Player::placeNewArmies2(Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace) {
	int iteration = 0; bool valid = true; Country* wanted = NULL;
	do {
		//	std::cout << "Itertion from placing is " << iteration;
		if (countryStr != " ") {
			wanted = world->findCountry(countryStr);
		}
		else {
			std::cout << "\nPlease enter where you want to place your " << (iteration + 1) << " army: ";
			std::cin >> countryStr;
			wanted = world->findCountry(countryStr);
		}
		wanted->getArmies()->push_back(this->getColor());
		this->owned->push_back(wanted);
		if (!samePlace) {
			countryStr = " ";
		}
		iteration++;
		
	} while ((iteration < numOfArmiesPlacing));
}