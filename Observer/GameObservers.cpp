#include "GameObservers.h"
Observer::~Observer()
{
};

Observer::Observer()
{
};

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::Detach(Observer* o)
{
	_observers->remove(o);
}

void Subject::Notify(std::string message)
{
	std::list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update(message);
}

Subject::Subject()
{
	_observers = new std::list <Observer*>;
}

Subject::~Subject()
{
	delete _observers;
}
