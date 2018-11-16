/*
 * SUBJECT.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_SUBJECT_H_
#define H_SUBJECT_H_

#include "Utilities.h"
using namespace std;

#include <list>

class Observer;

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/
class Subject {

	/** The subject of all observers */
public:
	virtual void subject_Attach(Observer *o);
	virtual void subject_Detach(Observer *o);
	virtual void subject_Notify();
	Subject();
	virtual ~Subject();
private:
	list<Observer*> * subject_Observers;

};



/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where SUBJECT_LOCAL isn't defined.
 * */
#ifdef SUBJECT_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_SUBJECT_H_ */
