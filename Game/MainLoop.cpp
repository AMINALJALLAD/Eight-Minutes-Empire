#include "MainLoop.h"
#include <ctime>

MainLoop::MainLoop(int num) :StartUp(), Observer()
{
	ended = false;
	maxOfCards = getMaxOfCard();
	loop(num);
}

MainLoop::MainLoop() :Observer(),StartUp()
{
	ended = false;
	for (int i = 0; i < gameStart->getNoPlayers(); i++)
		gameStart->getPlayers()->at(i)->Attach(this);
	maxOfCards = getMaxOfCard();
	loop();
}

MainLoop::~MainLoop()
{
	
}

int MainLoop::getMaxOfCard() {
	switch (gameStart->getNoPlayers())
	{
	case 2:
		return 6;
	case 3:
		return 10;
	case 4:
		return 8;
	default:
		return 7;
	}
}

bool MainLoop::reachToMax(int sizeOfCards) {
	return (sizeOfCards == maxOfCards);
}
void MainLoop::changePlayerStrategy(int index) {
	int choice = -1;
	while (!(choice == 0 || choice == 1)) {
		std::cout << "Do you want to change the " << gameStart->getPlayers()->at(index)->getColor() <<
			" strategy? (0) No -- (1) Yes :  ";
		std::cin >> choice;
	}
	if (choice == 1) {
		while (!(choice == 2 || choice == 3 || choice == 4)) {
			std::cout << "please select the strategy you want to set to the " << gameStart->getPlayers()->at(index)->getColor() <<
				" Player? (2) Greedy -- (3) Moderate -- (4) Human :  ";
			std::cin >> choice;
		}
		if (choice == 2) {
			gameStart->getPlayers()->at(index)->setStrategy(new Greedy());
		}
		else if (choice == 3) {
			gameStart->getPlayers()->at(index)->setStrategy(new Moderate());
		}		
		else {
			gameStart->getPlayers()->at(index)->setStrategy(new Human());
		}
	}
}

void MainLoop::Update( std::string message)
{
	display(message);
}

void MainLoop::display(std::string message)
{
	std::cout << std::endl << message << std::endl;
}

void MainLoop::loop(int num) {
	int debug = 0;
	std::string* possPlaChang = new std::string("");
	std::string* possCounChang = new std::string("");
	while (!ended) {
		for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
			if (debug < 1) 
				changePlayerStrategy(i);
			gameStart->getPlayers()->at(i)->selectCard(i, gameStart->getMap(),gameStart->getDeck(), possCounChang, possPlaChang);
			if (reachToMax(static_cast<int> (gameStart->getPlayers()->at(i)->getHand()->getMyCards()->size()))) {
				ended = true;
				break;
			}
		}
		debug++;
	}
}

void MainLoop::loop() {
	int debug = 0;
	int track = 0;
	while (!ended) {
		std::vector<std::string*>* prevBoard = copyActions(gameStart->getDeck());
		track++;
		
		for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
			std::string* possPlaChang = new std::string("");
			std::string* possCounChang = new std::string("");
			if (debug < 1)
				changePlayerStrategy(i);
			gameStart->getDeck()->show();
			gameStart->getPlayers()->at(i)->selectCard(i, gameStart->getMap(), gameStart->getDeck(), possCounChang, possPlaChang);
			applyChanges(possCounChang, possPlaChang);
			if (reachToMax(static_cast<int>(gameStart->getPlayers()->at(i)->getHand()->getMyCards()->size()))) 
			{
				ended = true;
				break;
			}
		}
		std::vector<std::string*>* newvBoard = copyActions(gameStart->getDeck());
		if (!notEqualVectors(newvBoard, prevBoard)) {
			ended = true;
			std::cout << "\n****The game will stop now because no action can be taken****\n";
		}
		debug++;
		delete newvBoard;		
		delete prevBoard;
		newvBoard = NULL;	
		prevBoard = NULL;

	}
}

void MainLoop::applyChanges(std::string* possCounChang, std::string* possPlaChang) {
	for (size_t i = 0; i < gameStart->getPlayers()->size(); i++) {
		if (gameStart->getPlayers()->at(i)->getColor().compare(*possPlaChang) == 0)
			for (size_t j = 0; j < gameStart->getPlayers()->at(j)->getOwned()->size(); j++) {
				if (gameStart->getPlayers()->at(i)->getOwned()->at(j)->getName().compare(*possCounChang) == 0) {
					gameStart->getPlayers()->at(i)->getOwned()->erase(gameStart->getPlayers()->at(i)->getOwned()->begin() + j);
					delete possCounChang;
					delete possPlaChang;
					possCounChang = NULL;
					possPlaChang = NULL;
					return;
				}

			}
	}
}
std::vector <std::string*>*  MainLoop::copyActions(Deck* deck) {
	std::vector <std::string*>* someVector = new std::vector <std::string*>;
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++)
		someVector->push_back(new std::string(deck->getBoardCards()->at(i)->getAction()));
	return someVector;
}
bool MainLoop::notEqualVectors(std::vector <std::string*>* prev, std::vector <std::string*>* newx) {
	for (size_t i = 0; i < prev->size(); i++)
		if(prev->at(i)->compare(*newx->at(i))!=0)
			return true;
	return false;
}
//***************************************************************************
//void MainLoop::loop(int num) {
//	while (!ended) {
//		for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
//			bool done = false, ignore = false; int input = 0;
//			gameStart->getPlayers()->at(i)->selectCard(gameStart->getDeck());
//			do {
//				int choice;
//				ignore = false;
//				done =
//					//choice = askUserForCard(i);
//					//Card* selected = gameStart->getDeck()->isPossibleDrawCard(choice);
//					//if (possibleAction(selected->getAction(), i)) {
//					//	std::cout << "Before selecting the card ";
//					//	std::cout << "The board deck is ";
//					//	gameStart->getDeck()->show();
//					//	std::cout << "The main deck is ";
//					//	gameStart->getDeck()->show2();
//					//	selected = gameStart->getDeck()->draw(choice - 1);
//					//	std::cout << "After selection the card ";
//					//	std::cout << "The board deck is ";
//					//	gameStart->getDeck()->show();
//					//	std::cout << "The main deck is ";
//					//	gameStart->getDeck()->show2();
//					//	gameStart->getPlayers()->at(i)->getHand()->addCard(selected);
//					//	gameStart->getPlayers()->at(i)->payCoin(getCardCost(choice, i));
//					//	doAction(i, selected->getAction());
//					//	done = true;
//					//}
//			} while (!done);
//
//				if (reachToMax(gameStart->getPlayers()->at(i)->getHand()->getMyCards()->size())) {
//					ended = true;
//					break;
//				}
//		}
//	}
//}
//
//void MainLoop::loop() {
//
//	while (!ended) {
//		for (int i = 0; i < this->gameStart->getNoPlayers(); i++) {
//			bool done = false, ignore = false; int input = 0;
//			do {
//				int choice;
//				ignore = false;
//				done = gameStart->getPlayers()->at(i)->selectCard(gameStart->getDeck());
//				//if (this->gameStart->getPlayers()->at(i)->getColor().compare("comp") == 0) {
//				//	std::srand(std::time(0));
//				//	int boardCardSize = 6;
//				//	choice = (rand() % boardCardSize) + 1;
//				//}
//				//else
//				//	choice = askUserForCard(i);
//				//Card* selected = gameStart->getDeck()->isPossibleDrawCard(choice);
//				//if (possibleAction(selected->getAction(), i)) {
//				//	selected = gameStart->getDeck()->draw(choice - 1);
//				//	gameStart->getPlayers()->at(i)->getHand()->addCard(selected);
//				//	gameStart->getPlayers()->at(i)->payCoin(getCardCost(choice, i));
//				//	if (!gameStart->getPlayers()->at(i)->Ignore()) {
//				//		doAction(i, selected->getAction());
//				//	}
//				//	done = true;
//				//}
//			} while (!done);
//
//			if (reachToMax(gameStart->getPlayers()->at(i)->getHand()->getMyCards()->size())) {
//				ended = true;
//				break;
//			}
//		}
//	}
//}
//
//
//
