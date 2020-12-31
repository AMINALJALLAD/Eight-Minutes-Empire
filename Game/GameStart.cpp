#include "GameStart.h"

GameStart::GameStart()
{
	std::ifstream inFile; // 
	std::string directory ("../Eight-Minute-Empire//dataBase/");
	std::string fileName (getMapName());
	std::string extension(".map");
	MapLoader* loader = new MapLoader(directory+fileName+extension);
	loader->fileOpener(inFile);
	this->board = loader->fileLoader(inFile);
	if (board->getSize() == 0) {
		std::cout << "There is nothing in this map.\nProgram will exit";
		exit(1);
	}
	int tempNoPlayers = getNumberPlayers();
	if(tempNoPlayers == 1)
		this->noPlayers = new int(tempNoPlayers+1);
	else
		this->noPlayers = new int(tempNoPlayers);
	instantiateBank();
	instantiatePlayers(tempNoPlayers);
	for (size_t i = 0; i < players->size(); i++)
		players->at(i)->setCoin(gameBank);
	this->gameDeck = new Deck();
	reach = false;
}

//*******************************************************************************
GameStart::~GameStart()
{
	
	delete gameDeck;
	delete gameBank; //total amount of money
	delete noPlayers;
	delete board;
	for (int i = 0; players->size(); i++) {
		delete players->at(i);
	} delete players;
}


//*******************************************************************************
std::string GameStart::getMapName() 
{
	std::cout << "Please enter the number coresponding to the map you would like to play\n"
		"(1-Africa -2-Asia -3-Ausralia -4-Canada -5-Europe -6-SAmerica -7-US -8-UK -9-invalid -10-isolated): ";
	int mapNumber;
	std::cin >> mapNumber;
	return mapNumberNameVonverter(mapNumber);
}

int GameStart::getNoPlayers() {
	return *noPlayers;
}
//*******************************************************************************
std::string GameStart::mapNumberNameVonverter(int mapNumber)
{
	switch (mapNumber) {
	case 10:
		return "isolated";
		break;
	case 9:
		return "invalid";
		break;
	case 8:
		return "UK";
		break;
	case 7:
		return "US";
		break;
	case 6:
		return "SAmerica";
		break;
	case 5:
		return "Europe";
		break;
	case 4:
		return "Canada";
		break;
	case 3:
		return "Ausralia";
		break;
	case 2:
		return "Asia";
		break;
	case 1:
		return "Africa";
		break;
	default:
		std::cout << "INVALID ENTRY; PLEASE TRY AGAIN!\n";
		return (getMapName());
		break;
	}
}


//*******************************************************************************
int GameStart::getNumberPlayers() 
{
	std::cout << "Please enter the number of players between(1-5)\n(1- if you want to play against the computer): ";
	int noPlayers;
	std::cin >> noPlayers;
	if (noPlayers > 0 && noPlayers < 6)
		return noPlayers;
	return getNumberPlayers();
}


//*******************************************************************************
void GameStart::instantiatePlayers(int noPlayers)
{
	this->players = new std::vector <Player*>;
	if (noPlayers == 1) {
		int difficulty = -1;
		Player* computer = NULL;
		while (!(difficulty == 1 || difficulty == 2)) {
			std::cout << "please enter the strategy of the computer (1) Greedy -- (2) Moderate";
			std::cin >> difficulty;
		}
		if(difficulty == 1)
			computer = new Player("comp", 99, new Greedy());
		else
			computer = new Player("comp", 99, new Moderate());
		this->players->push_back(computer);
	}

	std::vector <std::string> colors{ "Red","Blue","Green","Yellow","Black", "Brown" };
	for (int i = 0; i < noPlayers; i++) {
		std::cout << "Player " << (i + 1) << " : Please Enter the number corresponding to the color you want to choose\n";
		for (size_t j = 0; j < colors.size() ; j++)
			std::cout << " - "<< j <<"-"<< colors.at(j);
		std::cout << "\n";
		size_t choice  = -1;
		while (choice < 0 || choice >= colors.size()) {
			std::cin >> choice;
			if (choice < 0 || choice >= colors.size()) {
				std::cout << "Invalid Input. Please enter a valid number between zero and " << (colors.size() - 1) << std::endl;
			}
		}
		std::string color = colors.at(choice);
		colors.erase(colors.begin()+choice);
		int age = getPlayerAge();
		this->players->push_back(new Player(color, age, new Human()));
	}
}


//*******************************************************************************
int GameStart::getPlayerAge()
{
	std::cout << "Player Enter your age: ";
	int age;
	do{
		std::cin >> age;
		if ((age <= 7) || (age >= 100)) {
			std::cout << "It is not valid. Please enter a valid age";
		}
	}while ( (age <= 7) || (age >=100) );
	return age;
}


//*******************************************************************************
void GameStart::instantiateBank() {
	switch (*(this->noPlayers)) {
	case 5:
		this->gameBank = new int(40);
		break;
	case 4:
		this->gameBank = new int(36);
		break;
	case 3:
		this->gameBank = new int(33);
		break;
	default:
		this->gameBank = new int(28);
		break;
	}
}

Map* GameStart::getMap()
{
	return this->board;
}

Deck* GameStart::getDeck()
{
	return this->gameDeck;
}

std::vector<Player*>* GameStart::getPlayers()
{
	return this->players;
}

bool GameStart::isReachMax() {
	return reach;
}

void GameStart::setReach(bool done) {
	reach = done;
}

