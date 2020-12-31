//Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H
#include <list>
#include <iostream>
#include <string>
class Observer {
public:
	~Observer();
	virtual void Update(std::string message) = 0;
protected:
	Observer();

};
#endif

#ifndef SUBJECT_H
#define SUBJECT_H
class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(std::string message);
	Subject();
	~Subject();
private:
	std::list<Observer*>* _observers;

};
#endif