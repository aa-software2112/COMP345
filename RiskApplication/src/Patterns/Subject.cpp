
#define SUBJECT_LOCAL
#include "Subject.h"
#include "Observer.h"

void Subject::subject_Attach(Observer *o)
{
	this->subject_Observers->push_back(o);

}
void Subject::subject_Detach(Observer *o)
{
	this->subject_Observers->remove(o);
}
void Subject::subject_Notify()
{
	for(list<Observer *>::iterator it = this->subject_Observers->begin(); it != this->subject_Observers->end(); it++)
	{
		(*it)->observer_Update();
	}
}
Subject::Subject()
{
	this->subject_Observers = new list<Observer *>;
}
Subject::~Subject()
{
	delete this->subject_Observers;
}

