#include <iostream>
#include "Continent.h"

Continent::Continent(std::string name, Continent* next)
{
	this->name = new std::string(name);
	this->next = next;
	this->head = NULL;
	this->noCountries = 0;
}

Continent::Continent() {  // added by Amin default constructor
	this->name = NULL;
	this->next = NULL;
	this->head = NULL;
	this->noCountries = 0;
}
std::string Continent::getName() {
	return *(this->name);
}

Continent* Continent::getNext()
{
	return this->next;
}

bool Continent::print() {
	std::cout << "The countries in the continent of " << *(this->name) << " are: " << std::endl;
	Country* temp = this->head;
		for (int i = 0; i < this->noCountries; i++) {
			temp->printCountry();
			temp = temp->getNext();
		}
		return true;
}

bool Continent::empty()
{
	return (this->noCountries) == 0;
}

Country* Continent::findCountry(std::string name)
{
	Country* iterator = this->head;
	for (int i = 0; i < this->noCountries; i++) {
		if ((iterator->getName()).compare(name) == 0)
			return iterator;
		iterator = iterator->getNext();
	}
	return NULL;
}

Country* Continent::addCountry(std::string name)
{
	if (this->empty()) {
		Country* ptr = new Country(name, NULL);
		this->head = ptr;
		this->noCountries++;
		return this->head;
	}
	else {
		Country* ptr = new Country(name, this->head);
		this->head = ptr;
		this->noCountries++;
		return this->head;
	}
	
}
Country* Continent::getHead()
{
	return this->head;
}
bool Continent::addBorder(Country* origin, std::string name)
{
	Country* temp1 = this->findCountry(name);
	if (temp1 != NULL) {
		((origin->getLandBorderList()))->push_back(temp1);
		((temp1->getLandBorderList()))->push_back(origin);
	}
	else {
		temp1 = this->addCountry(name);
		((origin->getLandBorderList()))->push_back(temp1);
		((temp1->getLandBorderList()))->push_back(origin);
	}
	return true;
}
