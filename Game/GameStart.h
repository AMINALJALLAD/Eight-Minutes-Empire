#ifndef GAMESTART_H
#define GAMESTART_H
#include "Map.h"
#include "Player.h"
#include "Deck.h"
#include "MapLoader.h"
class GameStart
{
public:
	GameStart();
	~GameStart();
	std::string getMapName();
	int getNoPlayers();
	std::string mapNumberNameVonverter(int mapNumber);
	int getNumberPlayers();
	void instantiatePlayers(int noPlayers);
	int getPlayerAge();
	void instantiateBank();
	Map* getMap();
	Deck* getDeck();
	std::vector<Player*>* getPlayers();
	bool isReachMax();
	void setReach(bool done);
private:
	Map* board;
	std::vector<Player*> *players;
	Deck* gameDeck;
	int*  gameBank; //total amount of money
	int* noPlayers;
	bool reach;
	//std::vector <Card*> *boardCards;

};
#endif GAMESTART_H
