/*
 * GAME_STATISTICS_OBSERVER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_GAME_STATISTICS_OBSERVER_H_
#define H_GAME_STATISTICS_OBSERVER_H_

#include "Utilities.h"
#include "Observer.h"
#include "Map.h"
#include <iostream>
#include <iomanip>
using namespace std;

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

/** This class is the observer of the Map class; it will obtain the
 * status of the current map by calling map_getPlayerToCountryMapping()
 * which returns a map of player pointers to a list of countries it owns, from which
 * the percentage map ownership can be easily calculated.
 */
class GameStatisticsObserver: public Observer {

public:
	virtual void observer_Update(void);
	void gameStatObs_setSubject(Map *m);

private:
	/** The subject of map type */
	Map *subject;


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
 * exposed to other source files where GAME_STATISTICS_OBSERVER_LOCAL isn't defined.
 * */
#ifdef GAME_STATISTICS_OBSERVER_LOCAL


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



#endif /* H_GAME_STATISTICS_OBSERVER_H_ */
