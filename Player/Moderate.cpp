

#include "Moderate.h"
#include <ctime>
Moderate::Moderate() :PlayerAction() {

}


void Moderate::placeNewArmies(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace) {
	//std::cout << "in Place new army\n";
	int iteration = 0; bool valid = false; Country* wanted = NULL;
	for (int i = 0; i < numOfArmiesPlacing; i++)
	{
		int trial = 0;
		do {

			if (trial == 3) {
				wanted = world->getStart();
				countryStr = wanted->getName();
			}
			else {
				std::srand((unsigned int)std::time(0));
				int randNum = (rand() % owned->size());
				wanted = owned->at(randNum);
				countryStr = wanted->getName();
			}
			valid = isValidArmyPlace(color, world, countryStr, wanted);
			trial++;
		} while (!valid);
		wanted->getArmies()->push_back(color);
		owned->push_back(wanted);
		wanted = NULL;
	}
}


void Moderate::moveOverLand(std::string color, std::vector <Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving)
{
	int iteration = 0; bool valid = false;
	do {
		std::srand((unsigned int)std::time(0));
		int randNum = (rand() % owned->size());
		Country* origin = owned->at(randNum);
		origin_str = origin->getName();
		if (origin->getLandBorderList()->size() > 0) {
			randNum = (rand() % origin->getLandBorderList()->size());
			destination_str = origin->getLandBorderList()->at(randNum)->getName();
			valid = (isValidmovingOverLand(world, origin_str, destination_str,color) && contains(origin->getArmies(), color));
		}
		if (!valid) {
			continue;
		}
		else {
			MoveArmies(color, owned, world, origin_str, destination_str);
			iteration++;
		}
		//std::cout << "\n***An army has been moved from " << origin_str << "to " << destination_str << " for the " <<
		//	color << " player" << std::endl;
	} while (iteration < numOfArmiesMoving);
}


bool Moderate::Ignore() {
	return false;
}

void Moderate::moveOverSea(std::string color, std::vector <Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving)
{
	//std::cout << "in move overseas\n";
	int iteration = 0; bool valid = false;
	do {
		std::srand((unsigned int)std::time(0));
		int randNum = (rand() % owned->size());
		Country* origin = owned->at(randNum);
		origin_str = origin->getName();
		if (origin->getSeaBorderList()->size() > 0) {
			randNum = (rand() % origin->getSeaBorderList()->size());
			destination_str = origin->getSeaBorderList()->at(randNum)->getName();
			valid = (isValidmovingOverSea(world, origin_str, destination_str,color) && contains(origin->getArmies(), color));
		}
		if (!valid) {
			continue;
		}
		else {
			MoveArmies(color, owned, world, origin_str, destination_str);
			iteration++;
		}
		//std::cout << "\n***An army has been moved from " << origin_str << "to " << destination_str << " for the " <<
			//color << " player" << std::endl;
	} while (iteration < numOfArmiesMoving);
}

void Moderate::buildCity(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr) {
	//std::cout << "\nin Build city\n";

	bool valid = false; Country* wanted = NULL; int ind = 0;
	do {
		ind = 0;
		std::srand((unsigned int)std::time(0));
		int randNum = (rand() % owned->size());
		wanted = owned->at(randNum);
		valid = isPossiblebuildCity(color, world, wanted);
		if (valid) {
			wanted->getCastles()->push_back(color);
		}
		//std::cout << "\n***a city has been built at " << countryStr << " for the " <<
			//color << " player" << std::endl;
	} while (!valid);
}

void Moderate::destroyArmy(std::string color, std::vector <Country*>* owned, Map* map, std::string* countryStr, std::string* enemyColor) {
	//std::cout << "in Destroy army\n";

	bool valid = false; Country* wanted = NULL; int index = 0;
	do {
		index = 0;
		int iSecret;
		std::vector<Country*>* possibleEnemy = map->possibleEnemies(color);
		//std::cout << "*********ARAndas*********" << possibleEnemy->size();
		std::srand((unsigned int)std::time(0));
		iSecret = rand() % possibleEnemy->size();
		wanted = possibleEnemy->at(iSecret);
		iSecret = rand() % wanted->getArmies()->size();
		*enemyColor = wanted->getArmies()->at(iSecret);
		valid = isPossibleDestroyArmy(map, wanted, *enemyColor, index);
		if (valid) {
			*countryStr = wanted->getName();
			//std::cout << "\n***The " << color << " player destroyed an army for the " << *enemyColor <<
				//" player" << " in " << wanted->getName() << std::endl;
			wanted->getArmies()->erase(wanted->getArmies()->begin() + index);
		}
	} while (!valid);
	//std::cout << "\n***an army has been destroyed at " << countryStr << " for the " <<
		//color << " player by" << enemyColor << " player" << std::endl;
}

bool Moderate::selectCard(std::string color, int index, int& coins, Hand* hand, std::vector <Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer, std::string* message) {
	//std::cout << "\nin select card method\n";
	bool done = false, ignore = false; int input = 0;
	int choice;
	Card* selected = NULL;
	if (hasplace(deck, choice) && coins > getCardCost(choice)) {
		selected = deck->isPossibleDrawCard(choice);

		if (possibleAction(selected->getAction(), map, owned, color)) {
			selected = deck->draw(choice - 1);
			hand->addCard(selected);
			payCoin(coins, getCardCost(choice));
			//std::cout << "\n***The action that the " << color << " player selected is: " <<
				//selected->getAction() << std::endl;
			doAction(color, map, owned, selected->getAction(), changedCountry, changedPlayer);
		}
		*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice)) + " coins\nThe action that he chose was " + selected->getAction() + "\n";
		return true;
	}
	else if (hasMoveLand(deck, choice) && coins > getCardCost(choice)) {
		selected = deck->isPossibleDrawCard(choice);
		if (possibleAction(selected->getAction(), map, owned, color)) {
			selected = deck->draw(choice - 1);
			hand->addCard(selected);
			payCoin(coins, getCardCost(choice));
			//std::cout << "\n***The action that the " << color << " player selected is: " <<
				//selected->getAction() << std::endl;
			doAction(color, map, owned, selected->getAction(), changedCountry, changedPlayer);
		}
		*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice)) + " coins\nThe action that he chose was " + selected->getAction() + "\n";
		return true;
	}
	else if (hasMoveSea(deck, choice) && coins > getCardCost(choice)) {
		selected = deck->isPossibleDrawCard(choice);
		if (possibleAction(selected->getAction(), map, owned, color)) {
			selected = deck->draw(choice - 1);
			hand->addCard(selected);
			payCoin(coins, getCardCost(choice));
			//std::cout << "\n***The action that the " << color << " player selected is: " <<
				//selected->getAction() << std::endl;
			doAction(color, map, owned, selected->getAction(), changedCountry, changedPlayer);
		}
		*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice)) + " coins\nThe action that he chose was " + selected->getAction() + "\n";
		return true;
	}
	else {
		if (someCardPlayable(deck, coins, map, owned, color)) {
			std::vector<Card*>* playableCards = getCardPlayable(deck, coins, map, owned, color);

			do {
				std::srand((unsigned int)std::time(0));
				choice = (rand() % playableCards->size());
				choice = getIndex(deck->getBoardCards(), playableCards->at(choice)) + 1;
				selected = deck->isPossibleDrawCard(choice);
			} while (!(coins >= getCardCost(choice) && possibleAction(selected->getAction(), map, owned, color)));
		}
		else
			ignore = true;

		if (!ignore) {
			selected = deck->draw(choice - 1);
			hand->addCard(selected);
			payCoin(coins, getCardCost(choice));
			//std::cout << "\n***The action that the " << color << " player selected is: " <<
				//selected->getAction() << std::endl;
			doAction(color, map, owned, selected->getAction(), changedCountry, changedPlayer);
			*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice)) + " coins\nThe action that he chose was " + selected->getAction() + "\n";

		}
		else {
			*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice)) + " coins\nThe action that he chose was " + selected->getAction() + ", but he decided to ignore the action\n";
		}

		return true;
	}

	return false;
}

void Moderate::doAction(std::string color, Map* map, std::vector <Country*>* owned, std::string actionString, std::string* changedCountry, std::string* changedPlayer) {
	//std::cout << "in doAction\n";
	char lastChar = actionString.at(actionString.length() - 1);
	std::string temp = "";
	if (lastChar == '&') {
		temp = actionString.substr(0, 6);
		doAction(color, map, owned, temp, changedCountry, changedPlayer);
		temp = actionString.substr(17, 5);
		doAction(color, map, owned, temp, changedCountry, changedPlayer);
	}
	else if (lastChar == '|') {
		std::string temp1 = "", temp2 = "";
		temp1 = actionString.substr(0, 14);
		temp2 = actionString.substr(17, 17);
		int option; bool valid = false, firstValid = possibleAction(temp1, map, owned, color), secondValid = possibleAction(temp2, map, owned, color);
		do
		{
			if (firstValid && secondValid) {
				std::srand((unsigned int)std::time(0));
				option = (rand() % 2) + 1;
				if (option == 1) {
					return doAction(color, map, owned, temp1, changedCountry, changedPlayer);
				}
				else if (option == 2) {
					return doAction(color, map, owned, temp2, changedCountry, changedPlayer);
				}
			}
			else if (firstValid) {
				return doAction(color, map, owned, temp1, changedCountry, changedPlayer);
			}
			else if (secondValid) {
				return doAction(color, map, owned, temp2, changedCountry, changedPlayer);
			}
		} while (!valid);
		if (option == 1) {
			doAction(color, map, owned, temp1, changedCountry, changedPlayer);
			return;
		}
		else if (option == 2) {
			doAction(color, map, owned, temp2, changedCountry, changedPlayer);
			return;
		}
	}
	int numOfIteration = 0;
	std::string subSrting = actionString.substr(0, 5);

	if (subSrting._Equal("place")) {
		numOfIteration = std::stoi(actionString.substr(6, 7));
		this->placeNewArmies(color, owned, map, " ", numOfIteration, false);
	}

	else if (subSrting._Equal("moveL")) {
		numOfIteration = std::stoi(actionString.substr(9, 10));
		this->moveOverLand(color, owned, map, " ", " ", numOfIteration);
	}

	else if (subSrting._Equal("moveS")) {
		numOfIteration = std::stoi(actionString.substr(8, 9));
		this->moveOverSea(color, owned, map, " ", " ", numOfIteration);
	}

	else if (subSrting._Equal("desto")) {
		this->destroyArmy(color, owned, map, changedCountry, changedPlayer);
	}

	else if (subSrting._Equal("build")) {
		this->buildCity(color, owned, map, " ");
	}
}

bool Moderate::possibleAction(std::string actionString, Map* map, std::vector <Country*>* owned, std::string color) {
	char lastChar = actionString.at(actionString.length() - 1); // to check if it is a combination operations or not
	std::string* temp1 = new std::string(""), * temp2 = new std::string("");
	if (lastChar == '&') {
		temp1 = new std::string(actionString.substr(0, 6));
		temp2 = new std::string(actionString.substr(17, 5));
		return (possibleAction(*temp1, map, owned, color) && possibleAction(*temp2, map, owned, color));
	}
	else if (lastChar == '|') {
		return true;
	}
	std::string subSrting = actionString.substr(0, 5);
	std::vector<std::string>* armies = new std::vector<std::string>;
	std::vector<Country*>* tempOfCountries = owned;
	std::vector<Country*>* templandBorder = NULL, * tempSeaBorder;
	Country* tempOneCountry = NULL;
	std::string nameFirstCountry = "", nameSecondCountry = "";
	if (subSrting._Equal("place")) {
		return true;
	}
	else if (subSrting._Equal("moveL")) {
		for (int i = 0; i < tempOfCountries->size(); i++) {
			tempOneCountry = tempOfCountries->at(i);
			nameFirstCountry = tempOfCountries->at(i)->getName();
			templandBorder = tempOneCountry->getLandBorderList();
			for (int j = 0; j < templandBorder->size(); j++) {
				nameSecondCountry = templandBorder->at(j)->getName();
				if (this->isValidmovingOverLand(map, nameFirstCountry, nameSecondCountry,color)) {
					return true;
				}
			}
		}
		//std::cout << "Sorry you can't move any where through land at this moment\n";
		return false;
	}
	else if (subSrting._Equal("moveS")) {
		for (int i = 0; i < tempOfCountries->size(); i++) {
			tempOneCountry = tempOfCountries->at(i);
			nameFirstCountry = tempOfCountries->at(i)->getName();
			tempSeaBorder = tempOneCountry->getSeaBorderList();
			for (int j = 0; j < tempSeaBorder->size(); j++) {
				nameSecondCountry = tempSeaBorder->at(j)->getName();
				if (this->isValidmovingOverSea(map, nameFirstCountry, nameSecondCountry,color)) {
					return true;
				}
			}
		}
		//std::cout << "Sorry you can't move any where through Sea  at this moment\n";
		return false;
	}
	else if (subSrting._Equal("desto")) {
		for (int i = 0; i < tempOfCountries->size(); i++) {
			tempOneCountry = tempOfCountries->at(i);
			armies = tempOneCountry->getArmies();
			for (int j = 0; j < armies->size(); j++) {
				if (!(armies->at(i)._Equal(color))) {
					return true;
				}
			}
		}
		//std::cout << "Sorry you can't destroy any army at this moment\n";
		return false;
	}
	else if (subSrting._Equal("build")) {
		return true;
	}
	return true;
}

bool Moderate::hasBuild(Deck* deck, int& index) {
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (deck->getBoardCards()->at(i)->getAction().find("build") != std::string::npos) {
			index = static_cast<int> (i) + 1;
			return true;
		}
	}
	return false;
}

bool Moderate::hasDestroy(Deck* deck, int& index) {
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (deck->getBoardCards()->at(i)->getAction().find("desto") != std::string::npos) {
			index = static_cast<int> (i) + 1;
			return true;
		}
	}
	return false;
}

bool Moderate::hasMoveSea(Deck* deck, int& index) {
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (deck->getBoardCards()->at(i)->getAction().find("moveS") != std::string::npos) {
			index = static_cast<int> (i) + 1;
			return true;
		}
	}
	return false;
}

bool Moderate::hasMoveLand(Deck* deck, int& index) {
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (deck->getBoardCards()->at(i)->getAction().find("moveL") != std::string::npos) {
			index = static_cast<int> (i) + 1;
			return true;
		}
	}
	return false;
}

bool Moderate::hasplace(Deck* deck, int& index) {
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (deck->getBoardCards()->at(i)->getAction().find("place") != std::string::npos) {
			index = static_cast<int> (i) + 1;
			return true;
		}
	}
	return false;
}


int Moderate::getCardCost(int choice) {
	switch (choice) {
	case 6:
		return 3;
		break;
	case 5:
		return 2;
		break;
	case 4:
		return 2;
		break;
	case 3:
		return 1;
		break;
	case 2:
		return 1;
		break;
	default:
		return 0;
		break;
	}
}

bool Moderate::contains(std::vector<std::string>* someVector, std::string value) {
	for (size_t i = 0; i < someVector->size(); i++) {
		if (someVector->at(i).compare(value) == 0)
			return true;
	}
	return false;
}

bool Moderate::someCardPlayable(Deck* deck, int& coins, Map* map, std::vector<Country*>* owned, std::string color)
{
	//std::cout << "\nin someCardPlayable\n";
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (possibleAction(deck->getBoardCards()->at(i)->getAction(), map, owned, color) && coins >= getCardCost(i + 1)) {
			//std::cout << "\n" << deck->getBoardCards()->at(i)->getAction() << " " << coins << "\n";
			return true;
		}
	}
	return false;
}
std::vector<Card*>* Moderate::getCardPlayable(Deck* deck, int& coins, Map* map, std::vector<Country*>* owned, std::string color)
{
	//std::cout << "\nin getCardPlayable\n";
	std::vector<Card*>* possCards = new std::vector<Card*>;
	for (size_t i = 0; i < deck->getBoardCards()->size(); i++) {
		if (possibleAction(deck->getBoardCards()->at(i)->getAction(), map, owned, color) && coins >= getCardCost(i + 1)) {
			possCards->push_back(deck->getBoardCards()->at(i));
		}
	}
	return possCards;
}
int Moderate::getIndex(std::vector<Card*>* boardCards, Card* card)
{
	//std::cout << "\nin getCardPlayable\n";
	for (size_t i = 0; i < boardCards->size(); i++) {
		if (boardCards->at(i)->getAction().compare(card->getAction()) == 0)
			return i;
	}
	return 1;
}
