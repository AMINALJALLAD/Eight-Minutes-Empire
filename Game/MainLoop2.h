#pragma once
#include "StartUp.h"
#include "ComputerScoreObserver.h"
#ifndef MAIN_LOOP2_H
#define MAIN_LOOP2_H

class MainLoop2 : public StartUp, public Subject
{
public:
	MainLoop2();
	~MainLoop2();
	MainLoop2(int num);
	void loop();
	void applyChanges(std::string* possCounChang, std::string* possPlaChang);
	std::vector<std::string*>* copyActions(Deck* deck);
	bool notEqualVectors(std::vector<std::string*>* prev, std::vector<std::string*>* newx);
	void loop(int num);
	int getMaxOfCard();
	bool reachToMax(int sizeOfCards);
	void changePlayerStrategy(int index);
	void Update(std::string message);
	void display(std::string message);


private:
	ComputeScoreObserver* observer;
	bool ended;
	int sizeOfCard;
	int maxOfCards;
};
#endif MAINLOOP2_H


