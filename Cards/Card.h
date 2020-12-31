#ifndef CARD_H
#define CARD_H

#include <vector>
#include <iostream>
#include <string>

class Card
{
public:
	Card(std::string good_, std::string action);
	Card();
	~Card();
	std::string getGoods();
	std::string getAction();

private:
	std::string* goods;
	std::string* action;
};


#endif

