/*
 * OBSERVER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_OBSERVER_H_
#define H_OBSERVER_H_

#include "Utilities.h"
using namespace std;

#include <list>

class Observer;

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/
class Observer {

public:
	~Observer();
	virtual void observer_Update() = 0;

protected:
	Observer();

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
 * exposed to other source files where OBSERVER_LOCAL isn't defined.
 * */
#ifdef OBSERVER_LOCAL


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



#endif /* H_OBSERVER_H_ */
