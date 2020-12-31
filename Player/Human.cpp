#include "Human.h"
Human::Human() :PlayerAction() {

}

void Human::placeNewArmies(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr, int numOfArmiesPlacing, bool samePlace) {
	int iteration = 0; bool valid = true; Country* wanted = NULL;
	do {
		if (countryStr != " ") {
			wanted = world->findCountry(countryStr);
		}
		else {
			std::cout << "\nPlease enter where you want to place your " << (iteration + 1) << " army: ";
			std::cin >> countryStr;
			wanted = world->findCountry(countryStr);
		}
		if (color.compare("fake") != 0 && color.compare("comp") != 0)
			valid = isValidArmyPlace(color, world, countryStr, wanted);
		if (!valid) {
			std::cout << "You can only place armies at the start country or at a country where you have a castle" << std::endl;
			std::cout << "Please enter where you want to place your " << (iteration + 1) << " army: ";
			std::cin >> countryStr;
			continue;
		}
		else {
			wanted->getArmies()->push_back(color);
			owned->push_back(wanted);
			if (!samePlace) {
				countryStr = " ";
			}
			iteration++;
		}
	} while ((iteration < numOfArmiesPlacing));
}


void Human::moveOverLand(std::string color, std::vector <Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving)
{
	int iteration = 0; bool valid = false;
	do {
		std::cout << "\nPlease enter from where you want to move your " << (iteration + 1) << " army: ";
		std::cin >> origin_str;
		std::cout << "\nPlease enter to where you want to move your " << (iteration + 1) << " army: ";
		std::cin >> destination_str;
		valid = isValidmovingOverLand(world, origin_str, destination_str, color);
		if (!valid) {
			std::cout << "there's no a ground border between the two countries, or you don't have armies a the origin country." << std::endl;
			continue;
		}
		else {
			MoveArmies(color, owned, world, origin_str, destination_str);
			iteration++;
		}
	} while (iteration < numOfArmiesMoving);
}


bool Human::Ignore() {
	std::cout << "Do you want to ignore the action (0) for No; otherwise Yes? ";
	int input = 0;
	std::cin >> input;
	return (input);
}

void Human::moveOverSea(std::string color, std::vector <Country*>* owned, Map* world, std::string origin_str, std::string destination_str, int numOfArmiesMoving)
{
	int iteration = 0; bool valid = false; int indexOfCountry = 0;
	do {
		std::cout << "\nPlease enter from where you want to move your " << (iteration + 1) << " army: ";
		std::cin >> origin_str;
		std::cout << "\nPlease enter to where you want to move your " << (iteration + 1) << " army: ";
		std::cin >> destination_str;
		valid = isValidmovingOverSea(world, origin_str, destination_str, color);
		if (!valid) {
			std::cout << "there's no sea border between the two countries" << std::endl;
			continue;
		}
		else {
			MoveArmies(color, owned, world, origin_str, destination_str);
			iteration++;
		}
	} while (iteration < numOfArmiesMoving);
}

void Human::buildCity(std::string color, std::vector <Country*>* owned, Map* world, std::string countryStr) {
	bool valid = false; Country* wanted = NULL; int ind = 0;
	do {
		ind = 0;
		std::cout << "\nPlease enter where you want to build your city: ";
		std::cin >> countryStr;
		wanted = world->findCountry(countryStr);
		valid = isPossiblebuildCity(color, world, wanted);
		if (valid) {
			wanted->getCastles()->push_back(color);
		}
		else {
			std::cout << "You are not allowed to build a city here." << std::endl;
		}
	} while (!valid);
}

void Human::destroyArmy(std::string color, std::vector<Country*>* owned, Map* world, std::string* countryStr, std::string* enemyColor) {
	bool valid = false; Country* wanted = NULL; int index = 0;
	do {
		index = 0;
		std::cout << "\nPlease enter the color of the army you want to destroy: ";
		std::cin >> *enemyColor;
		std::cout << "\nPlease enter the country where this army exist: ";
		std::cin >> *countryStr;
		wanted = world->findCountry(*countryStr);
		valid = isPossibleDestroyArmy(world, wanted, *enemyColor, index);
		if (valid) {
			wanted->getArmies()->erase(wanted->getArmies()->begin() + index);
		}
		else {
			std::cout << "This enemy doesn't have any army in this country." << std::endl;
		}
	} while (!valid);

}

bool Human::selectCard(std::string color, int index, int& coins, Hand* hand, std::vector<Country*>* owned, Map* map, Deck* deck, std::string* changedCountry, std::string* changedPlayer, std::string* message) {
	bool done = false, ignore = false; int input = 0; Card* selected;
	int choice;
	do {
		choice = askUserForCard(color, coins);
		selected = deck->isPossibleDrawCard(choice);
		if (possibleAction(selected->getAction(), map, color, owned)) {
			selected = deck->draw(choice - 1);
			hand->addCard(selected);
			payCoin(coins, getCardCost(choice, color, coins));
			if (!Ignore())
				doAction(color, map, owned, selected->getAction(), changedCountry, changedPlayer);
			done = true;
		}
	} while (!done);

	*message = "The " + color + " player selected the " + std::to_string(choice) + ", card, he would pay " + std::to_string(getCardCost(choice, color, coins)) + " coins\nThe action that he chose was " + selected->getAction() + "\n";
	return true;
}

void Human::doAction(std::string color, Map* map, std::vector <Country*>* owned, std::string actionString, std::string* changedCountry, std::string* changedPlayer) {
	char lastChar = actionString.at(actionString.length() - 1);
	std::string temp = "";
	if (lastChar == '&') {
		temp = actionString.substr(0, 6);
		doAction(color, map, owned, temp, changedCountry, changedPlayer);
		temp = actionString.substr(17, 5);
		doAction(color, map, owned, temp, changedCountry, changedPlayer);
		return;
	}
	else if (lastChar == '|') {
		std::string temp1 = "", temp2 = "";
		temp1 = actionString.substr(0, 14);
		temp2 = actionString.substr(17, 17);
		std::cout << "You have two options, \nFirst option is " << temp1 << std::endl << "Second option is " << temp2 << "\n enter 1, else enter 2: ";
		int option; bool valid = false, firstValid = possibleAction(temp1, map, color, owned), secondValid = possibleAction(temp2, map, color, owned);
		do
		{
			if (firstValid && secondValid) {
				std::cin >> option;
				if (option == 1) {
					return doAction(color, map, owned, temp1, changedCountry, changedPlayer);
				}
				else if (option == 2) {
					return doAction(color, map, owned, temp2, changedCountry, changedPlayer);
				}
				else {
					std::cout << "It is not valid input.";
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

bool Human::possibleAction(std::string actionString, Map* map, std::string color, std::vector <Country*>* owned) {
	std::cout << actionString.at(actionString.length() - 1);
	char lastChar = actionString.at(actionString.length() - 1); // to check if it is a combination operations or not
	std::string* temp1 = new std::string(""), * temp2 = new std::string("");
	if (lastChar == '&') {
		temp1 = new std::string(actionString.substr(0, 6));
		temp2 = new std::string(actionString.substr(17, 5));
		return (possibleAction(*temp1, map, color, owned) && possibleAction(*temp2, map, color, owned));
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
		for (int i = 0; i < owned->size(); i++) {
			if (owned->at(i)->hasArmy(color) && owned->at(i)->getLandBorderList()->size() > 0)
				return true;
		}
		std::cout << "Sorry you can't move any where through land at this moment\n";
		return false;
	}
	else if (subSrting._Equal("moveS")) {
		for (int i = 0; i < owned->size(); i++) {
			if (owned->at(i)->hasArmy(color) && owned->at(i)->getSeaBorderList()->size() > 0)
				return true;
		}
		std::cout << "Sorry you can't move any where through Sea at this moment\n";
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
		std::cout << "Sorry you can't destroy any army at this moment\n";
		return false;
	}
	else if (subSrting._Equal("build")) {
		return true;
	}
	return true;
}


int Human::askUserForCard(std::string color, int& coins) {
	std::cout << "This the turn of the " << color <<
		"; Please select one of the following cards according to the amount you are willing to pay" <<
		" \n(The cost between brackets beside the number): ";
	int choice = -1;
	std::cin >> choice;
	if ((choice <= 0) || (choice >= 7)) {
		std::cout << "Invalid number. Please try it again." << std::endl;
		return askUserForCard(color, coins);
	}
	int cost = getCardCost(choice, color, coins);
	if (coins < cost)
		return askUserForCard(color, coins);
	else
		return choice;
}


int Human::getCardCost(int choice, std::string color, int& coins) {
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
	case 1:
		return 0;
		break;
	default:
		return askUserForCard(color, coins);
		break;
	}
}



