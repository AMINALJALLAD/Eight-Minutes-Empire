#ifndef MAINLOOP_H
#define MAINLOOP_H
#include "StartUp.h"
#include "GameObservers.h"
class MainLoop : public Observer, public StartUp
{
public:
	MainLoop();
	~MainLoop();
	MainLoop(int num);
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
	bool ended;
	int sizeOfCard;
	int maxOfCards;
};
#endif MAINLOOP_H
