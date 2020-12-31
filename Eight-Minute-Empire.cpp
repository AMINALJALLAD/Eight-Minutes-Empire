// Eight-Minute-Empire.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Map.h"
#include "MapLoader.h"
#include "Deck.h"
#include "Hand.h"
#include "Card.h"
#include "Player.h"
#include <cstdlib>
#include <random>
#include <string>
#include <iostream>
#include "GameStart.h"
#include "StartUp.h"
#include"MainLoop.h"
#include "ComputeScoreGame.h"
#include "MainLoop2.h"

//*****************************************************************************
//*******************************Driver Assignment 3***************************
//*****************************************************************************

//*****************************************************************************
//Driver for Strategy (part 1)
//*****************************************************************************

int main()
{
	ComputeScoreGame* game = new ComputeScoreGame();
	game->printScores();
}

//*****************************************************************************
//Driver for Observer (part 2)
//*****************************************************************************
//int main()
//
//{
//	ComputeScoreGame* game = new ComputeScoreGame();
//	game->printScores();
//}

//*****************************************************************************
//Driver for Observer (part 3)
//*****************************************************************************

//int main()
//{
//	MainLoop2* game = new MainLoop2();
//}


//*****************************************************************************
//Driver for Singleton (part 4)
//*****************************************************************************
//Driver (a)
//int main()
//{
//	MainLoop2* game = new MainLoop2();
//}


//Driver (b)
//
//int main()
//{
//	//Map* mapTest = new Map();
//	std::ifstream inFile;
//	MapLoader* map = new MapLoader("../Eight-Minute-Empire/dataBase/Asia.map");
//	map->fileOpener(inFile);
//	map->fileLoader(inFile);
//	MapLoader* map2 = new MapLoader("../Eight-Minute-Empire/dataBase/Africa.map");
//	map->fileOpener(inFile);
//	map->fileLoader(inFile);
//	MapLoader* map3 = new MapLoader("../Eight-Minute-Empire/dataBase/Canada.map");
//	map->fileOpener(inFile);
//	map->fileLoader(inFile);
//
//}

//*****************************Assignmnt 2*********************************************
//*****************************************************************************
//Driver for Game score computation (part 1)
//*****************************************************************************

//int main()
//{
//	ComputeScoreGame* game = new ComputeScoreGame();
//	game->printScores();
//}
////*****************************************************************************
//Driver for Game score computation (part 2)
//*****************************************************************************

//int main()
//{
//	ComputeScoreGame* game = new ComputeScoreGame();
//	game->printScores();
//}
//*****************************************************************************
//Driver for Game score computation (part 3)
//*****************************************************************************

//int main()
//{
//
//	MainLoop2* game = new MainLoop2();
//	
//}

//*****************************************************************************
//Driver for Game score computation (part 4)
//*****************************************************************************

//int main()
//{
//	SingletonClass::instance();
//	SingletonClass::instance()->startGame();
//
//}



                        //*****************************************************************************
                        //*******************************Driver Assignment 2***************************
                        //*****************************************************************************


////*****************************************************************************
////Driver for Game Start (Paart 1)
////*****************************************************************************
//
//int main()
//{
//	GameStart* game = new GameStart();
//	
//	game->getMap()->printMap();
//	std::cout << "******************************************************************************\n";
//	std::cout << "******************************************************************************\n";
//	
//	if (game->getMap()->isConnected() && game->getMap()->isValid()) {
//		std::cout << "******************************************************************************\n";
//		std::cout << "\nthe map is valid and connected!\n";
//		std::cout << "\n******************************************************************************\n";
//	}
//
//	else if (game->getMap()->isValid()) {
//		std::cout << "******************************************************************************\n";
//		std::cout << "\nthe map isn't connected!\n";
//		std::cout << "\n******************************************************************************\n";
//	}
//	else {
//		std::cout << "******************************************************************************\n";
//		std::cout << "\nthe map is invalid!\n";
//		std::cout << "\n******************************************************************************\n";
//	}
//
//	game->getDeck()->show();
//	std::cout << "******************************************************************************\n";
//	std::cout << "******************************************************************************\n";
//	std::vector<Player*>* players = game->getPlayers();
//	for (size_t i = 0; i < players->size(); i++) {
//		players->at(i)->printPlayer();
//		std::cout << "******************************************************************************\n";
//	}
//}


//*****************************************************************************
//Driver for StartUp phase (Part 2)
//*****************************************************************************

//int main(){
//	StartUp* game = new StartUp();
//
//	game->gameStart->getDeck()->show();
//	std::cout << "******************************************************************************\n";
//	std::cout << "******************************************************************************\n";
//	std::vector<Player*>* players = game->gameStart->getPlayers();
//	for (size_t i = 0; i < players->size(); i++) {
//		players->at(i)->printPlayer();
//		std::cout << "******************************************************************************\n";
//	}
//}


//*****************************************************************************
//Driver for main game loop (part 3)
//*****************************************************************************

//int main()
//{
//	MainLoop* game = new MainLoop();
//
//}

//*****************************************************************************
//Driver for Player Action (part 4)
//*****************************************************************************
//
//int main()
//{
//	PlayerAction* game = new PlayerAction();
//
//}

////*****************************************************************************
////Driver for Game score computation (part 5)
////*****************************************************************************
//
//int main()
//{
//	ComputeScoreGame* game = new ComputeScoreGame();
//	game->printScores();
//}

//*****************************************************************************
//Driver for the Map implementation
//*****************************************************************************

//int main()
//{
//	Map* world = new Map();
//
//	Continent* africa = world->addContinent("Africa");
//	Country* egy = africa->addCountry(10, "EGYPT");
//	africa->addBorder(egy, 20, "libya");
//	africa->addBorder(egy, 30, "Sudan");
//
//	Continent* na = world->addContinent("Nort America");
//	Country* can = na->addCountry(10, "Canada");
//	na->addBorder(can, 20, "USA");
//	na->addBorder(can, 30, "Russia");
//
//	Continent* asia = world->addContinent("Asia");
//	Country* syria = asia->addCountry(100, "Syria");
//	Country* invalid = asia->addCountry(100, "EGYPT");
//	asia->addBorder(syria, 20, "Lebanon");
//	asia->addBorder(syria, 30, "Palestine");
//	world->printMap();
//	if (world->isValid()) 
//		std::cout << "the map is valid! Enjoy playing";
//	else
//		std::cout << "invalid!invalid!invalid!invalid!invalid!invalid!invalid!";
//	
//}

//*****************************************************************************
//Driver for the map loader and map implementation
//*****************************************************************************

//int main()
//{
//	std::ifstream inFile;
//	MapLoader* map = new MapLoader("../Eight-Minute-Empire/dataBase/Asia.map");
//	map->fileOpener(inFile);
//	map->fileLoader(inFile);
//}

//*****************************************************************************
//Driver for the Player and BiddingFacility parts (Q3 & Q5)
//*****************************************************************************

//Player* findBidwinner(std::vector<Player*> players) {
//	int max = players[0]->getBid()->getBid();
//	std::vector<Player*> maxbids;
//	for (size_t i = 1; i < players.size(); i++) {
//		if (max < players[i]->getBid()->getBid())
//			max = players[i]->getBid()->getBid();
//	}
//	for (size_t i = 0; i < players.size(); i++) {
//		if (max == players[i]->getBid()->getBid())
//			maxbids.push_back(players[i]);
//	}
//	if (maxbids.size() < 2)
//		return maxbids[0];
//	else {
//		Player* youngest = maxbids[0];
//		int minage = maxbids[0]->getAge();
//		std::cout << "there's a tie in the bids between " << maxbids.size() <<" players;therefore, the youngest" <<
//			"player wins!" << std::endl;
//		for (size_t i = 1; i < maxbids.size(); i++) {
//			if (minage > maxbids[i]->getBid()->getBid())
//				youngest = maxbids[i];
//		}
//		return youngest;
//	}
//}
//
//int main() {
//	Player *p1, *p2, *p3, *winner;
//	std::vector<Player*> players;
//	players.push_back(new Player("red",30));
//	players.push_back(new Player("blue",20));
//	players.push_back(new Player("green",10));
//	for (size_t i = 0; i < players.size(); i++)
//		players[i]->setCoin();
//	for (size_t i = 0; i < players.size(); i++)
//		players[i]->setBid();
//	std::cout << "The bids that was made are:" << std::endl;
//	for (size_t i = 0; i < players.size(); i++) {
//		std::cout << players[i]->getColor() << " -------> ";
//		players[i]->getBid()->show();
//		std::cout << "\n";
//	}
//	std::cout << "Now all players made there bids, processing the winner..." << std::endl;
//	winner = findBidwinner(players);
//	winner->payCoin(winner->getBid()->getBid());
//	std::cout << "the winner is the " << winner->getColor() << " player, the bid was deducted from his coins!\n" << 
//		"The winner player now has "<<winner->getCoin()<<" coins.\nnow, let's start actually playing..." << std::endl;
//
//	//creating mickey mouse map for test
//
//	Map* world = new Map();
//
//	Continent* africa = world->addContinent("Africa");
//	Country* egy = africa->addCountry(10, "EGYPT");
//	africa->addBorder(egy, 20, "libya");
//	africa->addBorder(egy, 30, "Sudan");
//
//	Continent* na = world->addContinent("Nort America");
//	Country* can = na->addCountry(10, "Canada");
//	na->addBorder(can, 20, "USA");
//	na->addBorder(can, 30, "Russia");
//
//	Continent* asia = world->addContinent("Asia");
//	Country* syria = asia->addCountry(100, "Syria");
//	asia->addBorder(syria, 20, "Lebanon");
//	asia->addBorder(syria, 30, "Palestine");
//	std::cout << "the color of Egypt before placing armies is: " << egy->getColor() << std::endl;
//	
//	//test place armies
//	winner->placeNewArmies(world, "EGYPT");
//	std::cout << "the color of Egypt after placing armies is: " << egy->getColor() << std::endl;
//
//	//test MoveArmies
//	winner->MoveArmies(world, "EGYPT", "libya");
//	Country* lib = world->findCountry("libya");
//
//	std::cout << "the color of Egypt after moving army out of it: " << egy->getColor() << std::endl;
//	std::cout << "the color of Libya after moving army to it: " << lib->getColor() << std::endl;
//
//	//test moveOverLand()
//	africa->addBorder(lib, 20, "Algeria");
//	winner->moveOverLand(world, "libya", "Algeria");
//	Country* alg = world->findCountry("Algeria");
//	std::cout << "the color of Libya after moving army out of it: " << lib->getColor() << std::endl;
//	std::cout << "the color of Algeria after moving army to it: " << alg->getColor() << std::endl;
//
//	//test buildCity()
//	africa->addBorder(alg, 20, "Tunisia");
//	winner->buildCity(world, "Tunisia");
//	Country* tun = world->findCountry("Tunisia");
//	std::cout << "the color of Tunisia before Building the city: " << egy->getColor() << std::endl;
//	std::cout << "the color of Tunisia after Building the city: " << tun->getColor() << std::endl;
//
//	//test destroyArmy()
//	std::cout << "the color of Algeria before dstroying the army in it: " << alg->getColor() << std::endl;
//
//	players[0]->destroyArmy(world, "Algeria");
//	std::cout << "the color of Algeria after dstroying the army in it: " << alg->getColor() << std::endl;
//
//	//test moveOverLand() No border
//	winner->moveOverLand(world, "Tunisia", "Egypt");
//
//	return 0;
//}


//*****************************************************************************
//Driver for the Deck part 4
//*****************************************************************************


//int getrandom() {
//	int t = static_cast<int>(rand() % 40);
//	return  t;
//}
//std::string random_string()
//{
//	std::string str("0123456789abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
//
//	std::random_device rd;
//	std::mt19937 generator(rd());
//
//	std::shuffle(str.begin(), str.end(), generator);
//
//	return str.substr(0, 10);    // assumes 32 < number of characters in str         
//}
//int main() {
//	//deck temp;
//	Deck* deck = new Deck();
//
//	for (int i = 0; i < 42; i++) {
//		int num = getrandom();
//		Card* card = new Card(i,random_string());
//		deck->addCard(card);
//	}
//	deck->show();
//	std::cout << "*********************************\n";
//	deck->shuffle();
//	//Hand* hand = new Hand();
//	//for (int ind = 0; ind < 6; ind++) {
//	//	hand->addCard(deck->draw(ind));
//	//}
//	//hand->show();
//	//std::cout << "the deck now after drawing 6 cards" << std::endl;
//	std::cout << "*********************************\n";
//
//	deck->show();
//
//	//delete deck;
//	return 0;
//}
