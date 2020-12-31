#include "PlayerAction.h"

void PlayerAction::MoveArmies(std::string color,std::vector<Country*>* owned, Map* world, std::string origin_str, std::string destination_str)
{
	Country* oigin_ob = world->findCountry(origin_str);
	Country* destination_ob = world->findCountry(destination_str);
	for (size_t i = 0; i < oigin_ob->getArmies()->size(); i++) {
		if (color.compare(oigin_ob->getArmies()->at(i)) == 0) {
			oigin_ob->getArmies()->erase(oigin_ob->getArmies()->begin() + i);
			break;
		}
	}
	destination_ob->getArmies()->push_back(color);
	size_t i;
	for (i = 0; i < (owned->size()); i++) {
		if (owned->at(i)->getName().compare(origin_str) == 0) {
			(owned->erase(owned->begin() + i));
			owned->push_back(destination_ob);
			break;
		}

	}

}

bool PlayerAction::isValidArmyPlace(std::string color, Map* world, std::string countryStr, Country* wanted)
{
	if (world->getStart()->getName().compare(countryStr) == 0) {
		return true;
	}
	for (size_t i = 0; i < wanted->getCastles()->size(); i++) {
		if (color.compare(wanted->getCastles()->at(i)) == 0) {
			return true;
		}
	}
	return false;
}


bool PlayerAction::isValidmovingOverLand(Map* world, std::string origin_str, std::string destination_str,std::string color)
{
	Country* oigin_ob = world->findCountry(origin_str);
	if (oigin_ob->hasLandBorder(destination_str) && oigin_ob->hasArmy(color)) {
		return true;
	}
	return false;
}


bool PlayerAction::isValidmovingOverSea(Map* world, std::string origin_str, std::string destination_str, std::string color)
{
	Country* oigin_ob = world->findCountry(origin_str);
	if (oigin_ob->hasSeaBorder(destination_str) && oigin_ob->hasArmy(color)) {
		return true;
	}
	return false;
}



bool PlayerAction::isPossiblebuildCity(std::string color, Map* world, Country* wanted) {
	for (size_t i = 0; i < wanted->getArmies()->size(); i++) {
		if (color.compare(wanted->getArmies()->at(i)) == 0) {
			return true;
		}
	}
	return false;
}


bool PlayerAction::isPossibleDestroyArmy(Map* world, Country* wanted, std::string enemyColor, int& index) {
	for (size_t i = 0; i < wanted->getArmies()->size(); i++) {
		if (enemyColor.compare(wanted->getArmies()->at(i)) == 0) {
			index = static_cast<int> (i);
			return true;
		}
	}
	return false;
}

void PlayerAction::payCoin(int& coins, int payment)
{
	coins -= payment;
}
