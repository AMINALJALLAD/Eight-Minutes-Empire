#include "ComputerScoreObserver.h"

ComputeScoreObserver::ComputeScoreObserver() :Observer()
{
	gameStart = new GameStart();
	const int numOfPlayers = gameStart->getNoPlayers();
	playersScores = new int[numOfPlayers]();
	pointsOfCountries = new int[numOfPlayers]();
	pointsOfContinent = new int[numOfPlayers]();
	temp = new int[numOfPlayers]();
	tempOfConuntriesPoints = new int[numOfPlayers]();
	colorOfPlayers = new std::vector<std::string*>();
	arrayOfChar = new char[6]{ 'r','s','a','t','w', 'b' };
	pointsOfGoods = new int[6]();
	intializeColorArray();
}

ComputeScoreObserver::ComputeScoreObserver(GameStart* gameStartTemp) :Observer()
{
	gameStart = gameStartTemp;
	const int numOfPlayers = 2;
	playersScores = new int[numOfPlayers]();
	pointsOfCountries = new int[numOfPlayers]();
	pointsOfContinent = new int[numOfPlayers]();
	temp = new int[numOfPlayers]();
	tempOfConuntriesPoints = new int[numOfPlayers]();
	colorOfPlayers = new std::vector<std::string*>();
	arrayOfChar = new char[6]{ 'r','s','a','t','w' };
	pointsOfGoods = new int[6]();
	intializeColorArray();
}

int ComputeScoreObserver::findMinimum() {
	int min = pointsOfCountries[0], counterOfMin = 0, ind = 0;
	for (int i = 1; i < gameStart->getNoPlayers(); i++) {
		if (pointsOfCountries[i] < min) {
			std::cout << "min " << min << " ";
			min = pointsOfCountries[i];
			ind = i;
		}
		else if ((pointsOfCountries[i] == min)) {
			counterOfMin++;

		}
	}
	if (counterOfMin == 0) {
		return ind;
	}
	else {
		return -1;
	}

}

void ComputeScoreObserver::Update(std::string message) {
	computeScores();
	printScores();
	barGraph();
	int ind = 0;
	ind = findMinimum();
	if (ind >= 0) {
		minimumPlayerPossession(ind);
	}
	else {
		std::cout << "There is more than one has minimum location\n";
	}
	if (gameStart->isReachMax()) {
		whoWins();
	}

}

void ComputeScoreObserver::minimumPlayerPossession(int ind) {
	std::cout << "The minimum player " << (ind + 1) << " whose color is " << *colorOfPlayers->at(ind);
	std::cout << ", he has " << pointsOfCountries[ind] << " country/ies" << ", and " <<
		pointsOfCountries[ind] << " continent/ies" << ",and " << playersScores[ind] << " in total\n";
}






void ComputeScoreObserver::printInt(int* p) {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		std::cout << p[i] << " ";
	} std::cout << std::endl;
}

void ComputeScoreObserver::printChar(char* p) {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		std::cout << p[i] << " ";
	} std::cout << std::endl;
}

void ComputeScoreObserver::whoWins() {
	int index = 0;
	index = getIndexOfMaxValur(playersScores);
	if (index >= 0) {
		std::cout << "****Congratulation***\n The winner is " << (index + 1);
		std::cout << " with total " << playersScores[index] << " points";
		gameStart->getPlayers()->at(index)->printPlayer();

	}
	else {
		std::cout << "There is a tide. In other words more than one has maximum points";
	}
}

ComputeScoreObserver::~ComputeScoreObserver() {
	delete[] pointsOfCountries;
	delete[] pointsOfContinent;
	delete[] temp;
	delete[] tempOfConuntriesPoints;
	delete colorOfPlayers;
	delete playersOwned;
	delete[] arrayOfChar;
	delete[] pointsOfGoods;
}

void ComputeScoreObserver::IntializeAgain() {
	const int numOfPlayers = gameStart->getNoPlayers();
	playersScores = new int[numOfPlayers]();
	pointsOfCountries = new int[numOfPlayers]();
	pointsOfContinent = new int[numOfPlayers]();
	temp = new int[numOfPlayers]();
	tempOfConuntriesPoints = new int[numOfPlayers]();
	colorOfPlayers = new std::vector<std::string*>();
	arrayOfChar = new char[6]{ 'r','s','a','t','w', 'b' };
	pointsOfGoods = new int[6]();
	intializeColorArray();
}


void ComputeScoreObserver::computeScores() {
	IntializeAgain();
	getNumOfPoints(gameStart->getMap());
	int scores = 0; std::vector<Card*>* cards;
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		scores = 0;
		cards = gameStart->getPlayers()->at(i)->getHand()->getMyCards();
		scores += getCardPoints(cards);
		scores += pointsOfCountries[i];
		scores += pointsOfContinent[i];
		playersScores[i] = scores;
	}
}

int ComputeScoreObserver::getIndexOfMaxValur(int* ptr) {
	int max = 0, indexOfMax = 0, counterOfMAx = 0;
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		if (ptr[i] > max) {
			max = ptr[i];
			indexOfMax = i;
		}
		else if ((ptr[i] != 0) && (ptr[i] == max)) {
			counterOfMAx++;
		}
	}

	if ((counterOfMAx == 0) && (max > 0)) {
		return indexOfMax;
	}
	else {
		return -1; 
	}
}

void ComputeScoreObserver::startOver(int* ptr) {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		ptr[i] = 0;
	}
}


void ComputeScoreObserver::barGraph() {
	std::cout << "The bar graph for each players \n";
	for (int k = 0; k < gameStart->getNoPlayers(); k++) {
		std::cout << "Player " << (k + 1) << " has ";
		for (int l = 0; l < playersOwned->at(k)->size(); l++) {
			std::cout << playersOwned->at(k)->at(l) << " ";
		}std::cout << std::endl; // 1
	}std::cout << std::endl;
}

void ComputeScoreObserver::getNumOfPoints(Map* board) {
	Continent* tempConinent = board->getHead();
	Country* tempCountry;
	while (tempConinent != NULL) {
		std::cout << "****The continent is " << tempConinent->getName() << "****\n";
		tempCountry = tempConinent->getHead();
		startOver(tempOfConuntriesPoints);
		while (tempCountry != NULL) {
			std::cout << "The county is " << tempCountry->getName() << std::endl;
			if (tempCountry->getArmies()->size()) {
				for (int i = 0; i < gameStart->getNoPlayers(); i++) {
					std::cout << "Player " << (i + 1) << " ";
					for (int j = 0; j < tempCountry->getArmies()->size(); j++) {
						if (gameStart->getPlayers()->at(i)->getColor()._Equal(tempCountry->getArmies()->at(j))) {
							std::cout << tempCountry->getArmies()->at(j) << " ";
						}
					}std::cout << "\n";
				}std::cout << "\n";
			}
			if (tempCountry->getArmies()->size() >= 1) {
				startOver(temp);  // set values to zero
				whichColorDominientCountry(tempCountry->getArmies());
				whoDominantCountry(tempCountry);
			}
			tempCountry = tempCountry->getNext();
		}
		whoDominantConinent(tempConinent);
		tempConinent = tempConinent->getNext();
	}
}

int ComputeScoreObserver::getIndextOfArray(char fisrtChar) {
	switch (fisrtChar)
	{
	case 'r': // crystal
		return 0;
	case 's': // stone
		return 1;
	case 'a': // carrot
		return 2;
	case 't':  // tree
		return 3;
	case 'w':   // wild
		return 4;
	case 'b':
		return 5;
	default:
		return 0;
	}

}

int ComputeScoreObserver::getGoodsPoints() {
	int score = 0;
	score += (pointsOfGoods[0] / 1);
	score += (pointsOfGoods[1] / 2);
	score += (pointsOfGoods[2] / 3);
	score += (pointsOfGoods[3] / 2);
	score += (pointsOfGoods[4] / 2);
	score += (pointsOfGoods[5] / 2);
	return score;
}

int ComputeScoreObserver::getCardPoints(std::vector<Card*>* cards) {
	Card* aCard = NULL; char fisrtChar = 'l'; int ind = 0, points = 0;
	startOver(pointsOfGoods);
	for (int i = 0; i < cards->size(); i++) {
		aCard = cards->at(i);
		fisrtChar = aCard->getGoods().at(0);
		if (fisrtChar == 'c') {  // crystal or carrot, then get the second char
			fisrtChar = aCard->getGoods().at(1); // r for crystal and a for carrot
		}
		ind = getIndextOfArray(fisrtChar);
		pointsOfGoods[ind] += 1;
	}
	points = getGoodsPoints();
	return points;
}
void ComputeScoreObserver::printScores() {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		std::cout << "The player " << i << " has " << pointsOfCountries[i] << " country/ies, " <<
			", and " << pointsOfContinent[i] << " continent/s " << ", and gets " << (playersScores[i] - (pointsOfCountries[i] + pointsOfContinent[i])) <<
			" ponits from card goods. Therefore, he has in total " << playersScores[i] << " points\n";
		std::cout << std::endl;
	}
}

void ComputeScoreObserver::whoDominantConinent(Continent* continent) {
	int indexOfMax = getIndexOfMaxValur(tempOfConuntriesPoints);
	if (indexOfMax >= 0) {
		pointsOfContinent[indexOfMax] += 1;
		playersOwned->at(indexOfMax)->push_back(continent->getName());
	}
}


void ComputeScoreObserver::intializeColorArray() {
	std::string* temp = NULL;
	playersOwned = new std::vector<std::vector<std::string>*>();
	std::vector<std::string>* tempOwned;
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		tempOwned = new std::vector<std::string>;
		playersOwned->push_back(tempOwned);
		temp = new std::string(gameStart->getPlayers()->at(i)->getColor());
		colorOfPlayers->push_back(temp);
	}std::cout << std::endl;
}

void ComputeScoreObserver::whoDominantCountry(Country* country) {
	int indexOfMax = getIndexOfMaxValur(temp); bool found = false;
	if (indexOfMax >= 0) {
		pointsOfCountries[indexOfMax] += 1;
		tempOfConuntriesPoints[indexOfMax]++;
		playersOwned->at(indexOfMax)->push_back(country->getName());
	}
}

void ComputeScoreObserver::whichColorDominientCountry(std::vector<std::string>* colors) {
	for (int i = 0; i < colors->size(); i++) {
		for (int j = 0; j < colorOfPlayers->size(); j++) {
			if (colors->at(i)._Equal("fake")) {
				//	std::cout << "It is fake";
				continue;
			}
			if (colors->at(i)._Equal(*colorOfPlayers->at(j))) {

				temp[j]++;
			}
		}
	}
}