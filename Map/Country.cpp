#include "Country.h"

Country::Country(std::string name,Country* next)
{
	this->name = new std::string(name);
	this->next = next;
	this->landBorderList = new std::vector<Country*>;
	this->seaBorderList = new std::vector<Country*>;
	this->castles = new std::vector<std::string>;
	this->armies = new std::vector<std::string>;
	this->color = new std::string("White");
}

Country::Country() {
	this->name = NULL;
	this->next = NULL;
	this->landBorderList = new std::vector<Country*>;
	this->seaBorderList = new std::vector<Country*>;
	this->castles = new std::vector<std::string>;
	this->armies = new std::vector<std::string>;
	this->color = new std::string("White");
}

std::vector<std::string>* Country::getCastles()
{
	return this->castles;
}
std::vector<std::string>* Country::getArmies()
{
	return this->armies;
}
//void Country::buildCastle(std::string color) {
//	this->castles->push_back(color);
//}
bool Country::destroyCastle(std::string color) {
	for (size_t i = 0; i < castles->size(); i++) {
		if (this->castles->at(i).compare(color) == 0) {
			this->castles->erase(this->castles->begin() + i);
			return true;
		}
	}
	std::cout << "this player doesn't have a castle in ths country\n";
	return false;
}

std::string Country::getName()
{
	return *(this->name);
}
void Country::setColor(std::string color)
{
	this->color = new std::string(color);
}
Country* Country::getNext()
{
	return this->next;
}


void Country::setNext(Country* next)
{
	this->next = next;
}

bool Country::printCountry()
{
	std::cout << *(this->name) << " and has land borders with: ";
	for (size_t i = 0; i< ((*(this->landBorderList)).size()); i++) {
		std::cout<<(*(this->landBorderList))[i]->getName() << ", ";
	}
	std::cout <<  "\n and has sea borders with: ";
	for (size_t i = 0; i < ((*(this->seaBorderList)).size()); i++) {
		std::cout << (*(this->seaBorderList))[i]->getName() << ", ";
	}
	std::cout<<std::endl;
	return true;
}

std::vector<Country*>* Country::getLandBorderList()
{
	return this->landBorderList;
}

std::vector<Country*>* Country::getSeaBorderList()
{
	return this->seaBorderList;
}

bool Country::hasLandBorder(std::string name)
{
	for (size_t i = 0; i < this->landBorderList->size(); i++) {
		if ((*(this->landBorderList))[i]->getName().compare(name) == 0)
			return true;
	}
	return false;
}
bool Country::hasSeaBorder(std::string name)
{
	for (size_t i = 0; i < this->seaBorderList->size(); i++) {
		if ((*(this->seaBorderList))[i]->getName().compare(name) == 0)
			return true;
	}
	return false;
}


bool Country::hasBorder(std::string name)
{
	return (hasLandBorder(name)||hasSeaBorder(name));
}


std::string Country::getColor()
{
	return *this->color;
}



bool Country::hasPath(Country* other, std::vector <Country*>* checked)
{
	if (this->hasBorder(other->getName()))
		return true;
	else {
		checked->push_back(this);
		for (size_t i = 0; i < this->getLandBorderList()->size(); i++) {
			if (!inVector(this->getLandBorderList()->at(i), checked) && this->getLandBorderList()->at(i)->hasPath(other, checked))
				return true;
			else continue;
		}
		for (size_t i = 0; i < this->getSeaBorderList()->size(); i++) {
			if (!inVector(this->getSeaBorderList()->at(i), checked) && this->getSeaBorderList()->at(i)->hasPath(other, checked))
				return true;
			else continue;
		}
	}
	return false;
}
bool Country::inVector(Country* country, std::vector<Country*>* connected) {

	for (size_t i = 0; i < connected->size(); i++) {
		if (country->getName().compare(connected->at(i)->getName()) == 0)
			return true;
	}
	return false;
}
bool Country::hasArmy(std::string color) {
	for (size_t i = 0; i < armies->size(); i++)
		if (color.compare(armies->at(i)) == 0)
			return true;
	return false;
}