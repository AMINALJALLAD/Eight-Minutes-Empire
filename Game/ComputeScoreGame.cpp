#include "ComputeScoreGame.h"

ComputeScoreGame::ComputeScoreGame():MainLoop()
{
	
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
	getNumOfPoints(gameStart->getMap());
	printScores();
}

void ComputeScoreGame::whoWins() {
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

void ComputeScoreGame::printInt(int* p) {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		std::cout << p[i] << " ";
	} std::cout << std::endl;
}

void ComputeScoreGame::printChar(char* p) {
	for (int i = 0; i < 6; i++) {
		std::cout << p[i] << " ";
	} std::cout << std::endl;
}

ComputeScoreGame::~ComputeScoreGame() {
	whoWins();
	delete[] pointsOfCountries;
	delete[] pointsOfContinent;
	delete[] temp;
	delete[] tempOfConuntriesPoints;
	delete colorOfPlayers;
	delete[] arrayOfChar;
	delete[] pointsOfGoods;
}

void ComputeScoreGame::intializeColorArray() {
	std::string *temp = NULL;
	//std::cout << ", and colorofplayers size are " << colorOfPlayers->size();
	/*for (int i = 0; i < colorofplayers->size(); i++) {
		std::cout << *colorofplayers->at(i) << " ";
	}
	std::cout << "all colors before itiallizer\n";*/
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		temp = new std::string(gameStart->getPlayers()->at(i)->getColor());
		colorOfPlayers->push_back(temp);
		/*std::cout << "color " << i << " is " << *temp << " ";
		std::cout << ", and color in colorofplayers " << i << " is " << *colorofplayers->at(i) << "\n";
		std::cout << "size is " << colorofplayers->size() << " ";*/
		/*for (int i = 0; i < colorofplayers->size(); i++) {
			std::cout << *colorofplayers->at(i) << " ";
		} std::cout << std::endl;*/
	//	delete temp;
	}std::cout << std::endl;
	/*std::cout << ", and colorofplayers size are " << colorOfPlayers->size();
	for (int i = 0; i < colorOfPlayers->size(); i++) {
		std::cout << "\ti is " << i << " ";
		std::cout << *colorofplayers->at(i) << " ";
	}
	std::cout << "all colors from itiallizer\n";*/
}

void ComputeScoreGame::computeScores() {
	int scores = 0; std::vector<Card*>* cards;
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		//std::cout << "player " << i << " has ";
		cards = gameStart->getPlayers()->at(i)->getHand()->getMyCards();
		//std::cout << "we should call getCardPoints() ";
		int p = getCardPoints(cards);
		//std::cout << "After calling getCardPoints() " ;
		scores += p;
		//std::cout << ", and score from cards " << p << " points ";
		scores += pointsOfCountries[i];
		//std::cout << ", and score from cards " << pointsOfCountries[i] << " points ";
		scores += pointsOfContinent[i];
		//std::cout << ", and score from cards " << pointsOfContinent[i] << " points ";
		playersScores[i] = scores;
	}
}

int ComputeScoreGame::getIndexOfMaxValur(int* ptr) {
	int max = 0, indexOfMax = 0, counterOfMAx = 0;
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		if (ptr[i] > max) {
			max = ptr[i];
			indexOfMax = i;
		}else if ((ptr[i] != 0) &&(ptr[i] == max)) {
		//	std::cout << "ptr[i] is " << ptr[i] << ", and  max is " << max << ", so tide in cremenent counter\n";
			counterOfMAx++;
		}
	}
	/*std::cout << "After finish the index\nThe max is " << max << ", and counterOfMAx " << counterOfMAx;
	std::cout << ", and the index is " << indexOfMax << "\n";*/
	if ((counterOfMAx == 0) && (max > 0) )  {
	//	std::cout << "the winner is " << *colorOfPlayers->at(indexOfMax) << "\n";
		return indexOfMax;
	}
	else {
	//	std::cout << "the is no winner in finc\n";
		return -1; // more than one has the same maximum armies
	}
}

void ComputeScoreGame::whoDominantCountry() {
	//std::cout << "Calling from whoDominantCountry\n";
	int indexOfMax = getIndexOfMaxValur(temp);
	if (indexOfMax >= 0) {
		//std::cout << "indexOfMax is " << indexOfMax;
		pointsOfCountries[indexOfMax] += 1;
		tempOfConuntriesPoints[indexOfMax]++;
	}
}

void ComputeScoreGame::startOver(int* ptr) {
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		ptr[i] = 0;
	}
}



//void ComputeScoreGame::barGraph() {
//	//std::cout << "Calling from bar graph ";
//	//std::cout << "total capacitis" << playersOwned->size()<< "\n";
//for (int k = 0; k < gameStart->getNoPlayers(); k++) {
//	//std::cout <<  "Player owned size" << playersOwned->at(k)->size() <<" --";
//	std::cout << "Player " << (k + 1) << " has ";
//	for (int l = 0; l < playersOwned->at(k)->size(); l++) {
//		std::cout << playersOwned->at(k)->at(l) << " ";
//	}std::cout << std::endl; // 1
//}std::cout << std::endl;
//}
	


//void ComputeScoreGame::whichColorDominientCountry(std::vector<std::string>* colors) {
//	/*std::cout << "From whichColorDominientCountry function \n";
//	std::cout << "colors size are " << colors->size() << ", and colors ";*/
//	for (int i = 0; i < colors->size(); i++) {
//		std::cout << colors->at(i) << " ";
//	}
//	//std::cout << "\n and colorOfPlayers size are " << colorOfPlayers->size() << " ";
//	/*for (int i = 0; i < ; i++) {
//		std::cout << *colorOfPlayers->at(i) << " ";
//	}*/
//	std::cout << "all colors\n";
//	for (int i = 0; i < colors->size(); i++) {
//		for (int j = 0; j < color; j++) {
//			if (colors->at(i)._Equal("fake")) {
//				std::cout << "It is fake";
//				continue;
//			}
//		/*	std::cout << "************Inside loop************  i is " << i << ", j is " << j << "\n";
//			std::cout << colors->at(i);
//			std::cout << " " << *colorOfPlayers->at(j) << "\n";
//			std::cout << colors->at(i)._Equal(*colorOfPlayers->at(j));
//			std::cout << "************************\n";*/
//			if (colors->at(i)._Equal(*colorOfPlayers->at(j))) {
//			//	std::cout << "It is same";
//				std::cout << temp[j];
//				temp[j]++;
//			//	std::cout << temp[j] << "changed \n";
//			}
//		}
//	}
//}

void ComputeScoreGame::whoDominantConinent() {
//	std::cout << "calling from whodominantconinent\n";
	int indexofmax = getIndexOfMaxValur(tempOfConuntriesPoints);
//	std::cout << "indexofmax is " << indexofmax << " ";
	if (indexofmax >= 0) {
	//	std::cout << "the winner is " << *colorofplayers->at(indexofmax) << "\n";
		pointsOfContinent[indexofmax] += 1;
	}
	//std::cout << "the max is " << indexofmax;
	//std::cout << "no winner in this continent\n";
}

//void ComputeScoreGame::getNumOfPoints(Map* board) {
//	Continent* tempConinent = board->getHead();
//	Country* tempCountry;
//	while (tempConinent != NULL) {
//	//	std::cout << "The continent is " << tempConinent->getName() << std::endl;
//		tempCountry = tempConinent->getHead();
//		startOver(tempOfConuntriesPoints);
//		while (tempCountry != NULL) {
//			std::cout << "The county is " << tempCountry->getName() << std::endl;
//			std::cout << "The armies are " ;
//			for (int i = 0; i < tempCountry->getArmies()->size(); i++) {
//				std::cout << tempCountry->getArmies()->at(i) << " ";
//			} std::cout << "That is all" << std::endl;
//		//	std::cout << "Is there and arimes in this country " <<(tempCountry->getArmies()->size() >= 1) << " ";
//			if (tempCountry->getArmies()->size() >= 1) {
//			//	std::cout << "Yes It is ";
//				startOver(temp);  // set values to zero
//				std::cout << "temp before wich color dominate is ";
//				printInt(temp);
//				whichColorDominientCountry(tempCountry->getArmies());
//				std::cout << "Temp after wich color dominate is ";
//				printInt(temp);
//			//	std::cout << "tempOfConuntriesPoints before wich country dominate is ";
//			//	printInt(tempOfConuntriesPoints);
//				whoDominantCountry();
//			//	std::cout << "tempOfConuntriesPoints after wich country dominate is ";
//			//	printInt(tempOfConuntriesPoints);
//			}
//			tempCountry = tempCountry->getNext();
//		}
//	/*	std::cout << "Before whoDominantConinent pointsOfContinent is ";
//		printInt(pointsOfContinent);*/
//		whoDominantConinent();
//	/*	std::cout << "After whoDominantConinent pointsOfContinent is "; 
//		printInt(pointsOfContinent);*/
//		tempConinent = tempConinent->getNext();
//		
//	}
//	
//}

void ComputeScoreGame::getNumOfPoints(Map* board) {
	Continent* tempConinent = board->getHead();
	Country* tempCountry;
	while (tempConinent != NULL) {
		//	std::cout << "The continent is " << tempConinent->getName() << std::endl;
		tempCountry = tempConinent->getHead();
		startOver(tempOfConuntriesPoints);
		while (tempCountry != NULL) {
		/*	std::cout << "The county is " << tempCountry->getName() << std::endl;
			std::cout << "The armies are ";
			for (int i = 0; i < tempCountry->getArmies()->size(); i++) {
				std::cout << tempCountry->getArmies()->at(i) << " ";
			} std::cout << "That is all" << std::endl;*/
			//	std::cout << "Is there and arimes in this country " <<(tempCountry->getArmies()->size() >= 1) << " ";
			if (tempCountry->getArmies()->size() >= 1) {
				//	std::cout << "Yes It is ";
				startOver(temp);  // set values to zero
			/*	std::cout << "Temp before wich color dominate is ";
				printInt(temp);*/
				whichColorDominientCountry(tempCountry->getArmies());
			/*		std::cout << "Temp after wich color dominate is ";
					printInt(temp);
					std::cout << "tempOfConuntriesPoints before wich country dominate is ";
					printInt(tempOfConuntriesPoints);*/
				whoDominantCountry();
				/*	std::cout << "tempOfConuntriesPoints after wich country dominate is ";
					printInt(tempOfConuntriesPoints);*/
			}
			tempCountry = tempCountry->getNext();
		}
		/*	std::cout << "Before whoDominantConinent pointsOfContinent is ";
			printInt(pointsOfContinent);*/
		whoDominantConinent();
		/*	std::cout << "after whodominantconinent pointsofcontinent is ";
			printInt(pointsOfContinent);*/
		tempConinent = tempConinent->getNext();
	}
	//barGraph();
}




int ComputeScoreGame::getIndextOfArray(char fisrtChar) {
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

int ComputeScoreGame::getGoodsPoints() {
	int score = 0;
	//std::cout << "score from getGoodsPoints() is  ";
	/*for (int i = 0; i < 6; i++) {
		std::cout << pointsOfGoods[i] << " ";
	}*/
	//std::cout << "************************************\ncorresponding from char() is  ";
	//printChar(arrayOfChar);
	score += (pointsOfGoods[0] / 1);
	score += (pointsOfGoods[1] / 2);
	score += (pointsOfGoods[2] / 3);
	score += (pointsOfGoods[3] / 2);
	score += (pointsOfGoods[4] / 2);
	score += (pointsOfGoods[5] / 2);
	//std::cout << "After that from getGoodsPoints() is  ";
	/*for (int i = 0; i < 6; i++) {
		std::cout << pointsOfGoods[i] << " ";
	}
	std::cout << "score from getGoodsPoints() is  " << score << "\n";*/
	return score;
}

int ComputeScoreGame::getCardPoints(std::vector<Card*>* cards) {
	//std::cout << "from getCardPoints ";
	Card* aCard = NULL; char fisrtChar = 'l'; int ind = 0, points = 0;
	startOver(pointsOfGoods);
	for (int i = 0; i < cards->size(); i++) {
		aCard = cards->at(i);
		fisrtChar = aCard->getGoods().at(0);
	//	std::cout << "this card good is " << aCard->getGoods() << ", and fisrtChar is " << fisrtChar << " ";
		if (fisrtChar == 'c') {  // crystal or carrot, then get the second char
			fisrtChar = aCard->getGoods().at(1); // r for crystal and a for carrot
		//	std::cout << ", Because c firsr char this card good is " << aCard->getGoods() << ", and fisrtChar is " << fisrtChar;
		}
		ind = getIndextOfArray(fisrtChar);
	//	std::cout << "index is " << ind << "\n";
		pointsOfGoods[ind] += 1;
	}
	//std::cout << "pointsOfGoods is " ;
	//printInt(pointsOfGoods);
	return getGoodsPoints();
}
void ComputeScoreGame::printScores() {
	computeScores();
	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
		std::cout << "The player number " << (i + 1) << ": has " << pointsOfCountries[i] << " country/ies, " <<
			", and " << pointsOfContinent[i] << " continent/s " << ", and gets " << (playersScores[i] - (pointsOfCountries[i] + pointsOfContinent[i])) <<
			" ponits from card goods. Therefore, he has in total " << playersScores[i] << " points\n";
	}std::cout << "\n";
	whoWins();
}

void ComputeScoreGame::whichColorDominientCountry(std::vector<std::string>* colors) {
	/*std::cout << "from whichcolordominientcountry function \n";
	std::cout << "colors size are " << colors->size() << ", and colors ";*/
	/*for (int i = 0; i < colors->size(); i++) {
		std::cout << colors->at(i) << " ";
	}*/
	//std::cout << "\n and colorofplayers size are " << colorofplayers->size() << " ";
	/*for (int i = 0; i < colorofplayers->size(); i++) {
		std::cout << *colorofplayers->at(i) << " ";
	}
	std::cout << "all colors\n";*/
	for (int i = 0; i < colors->size(); i++) {
		for (int j = 0; j < colorOfPlayers->size(); j++) {
			if (colors->at(i)._Equal("fake")) {
			//	std::cout << "it is fake";
				continue;
			}
			/*	std::cout << "************inside loop************  i is " << i << ", j is " << j << "\n";
				std::cout << colors->at(i);
				std::cout << " " << *colorofplayers->at(j) << "\n";
				std::cout << colors->at(i)._equal(*colorofplayers->at(j));
				std::cout << "************************\n";*/
			if (colors->at(i)._Equal(*colorOfPlayers->at(j))) {
				//	std::cout << "it is same";
				//std::cout << temp[j];
				temp[j]++;
				//	std::cout << temp[j] << "changed \n";
			}
		}
	}
}


//void ComputeScoreGame::whoDominantConinent(Continent* continent) {
//	//	std::cout << "Calling from whoDominantConinent\n";
//	int indexOfMax = getIndexOfMaxValur(tempOfConuntriesPoints);
//	//	std::cout << "indexOfMax is " << indexOfMax << " ";
//	if (indexOfMax >= 0) {
//		//	std::cout << "The winner is " << *colorOfPlayers->at(indexOfMax) << "\n";
//		pointsOfContinent[indexOfMax] += 1;
//	//	std::cout << "before pusing continent " << playersOwned->size() << " ";
//		playersOwned->at(indexOfMax)->push_back(continent->getName());
//	//	std::cout << "After pusing continent" << playersOwned->size() << "\n";
//	}
//	//std::cout << "The max is " << indexOfMax;
//	//std::cout << "No winner in this continent\n";
//}

//void ComputeScoreGame::intializeColorArray() {
//	std::string* temp = NULL;
//	playersOwned = new std::vector<std::vector<std::string>*>();
//	std::vector<std::string>* tempOwned;
//	//std::cout << ", and colorOfPlayers size are " << colorOfPlayers->size();
//	/*for (int i = 0; i < colorOfPlayers->size(); i++) {
//		std::cout << *colorOfPlayers->at(i) << " ";
//	}
//	std::cout << "all colors before itiallizer\n";*/
//	for (int i = 0; i < gameStart->getNoPlayers(); i++) {
//		tempOwned = new std::vector<std::string>;
//		//std::cout << "before pusing " << playersOwned->size() << " ";
//		playersOwned->push_back(tempOwned);
//		//std::cout << "After pusing" << playersOwned->size() << "\n";
//		temp = new std::string(gameStart->getPlayers()->at(i)->getColor());
//		colorOfPlayers->push_back(temp);
//		/*std::cout << "color " << i << " is " << *temp << " ";
//		std::cout << ", and color in colorOfPlayers " << i << " is " << *colorOfPlayers->at(i) << "\n";
//		std::cout << "size is " << colorOfPlayers->size() << " ";*/
//		/*for (int i = 0; i < colorOfPlayers->size(); i++) {
//			std::cout << *colorOfPlayers->at(i) << " ";
//		} std::cout << std::endl;*/
//		//	delete temp;
//	}std::cout << std::endl;
//	//std::cout << ", and colorOfPlayers size are " << colorOfPlayers->size();
//	//for (int i = 0; i < colorOfPlayers->size(); i++) {
//	//	std::cout << "\ti is " << i << " ";
//	//	std::cout << *colorOfPlayers->at(i) << " ";
//	//}
//	//std::cout << "all colors from itiallizer\n";
//}

//void ComputeScoreGame::whoDominantCountry(Country* country) {
//	//std::cout << "Calling from whoDominantCountry\n";
//	int indexOfMax = getIndexOfMaxValur(temp);
//	if (indexOfMax >= 0) {
//		pointsOfCountries[indexOfMax] += 1;
//		tempOfConuntriesPoints[indexOfMax]++;
//		//std::cout << "before pusing country " << playersOwned->at(indexOfMax)->size() << " ";
//		playersOwned->at(indexOfMax)->push_back(country->getName());
//		//std::cout << "After pusing country " << playersOwned->at(indexOfMax)->size() << " ";
//	}
//}
//void ComputeScoreGame::update() {
//	printScores();
//	barGraph();
//}


