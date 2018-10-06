/*
 * CONTINENT.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_CONTINENT_H_
#define H_CONTINENT_H_


#include <map>
#include <regex>
#include "Country.h"
#include "Utilities.h"
using namespace std;

class Continent {
	public:
		/** Constructor **/
		Continent(string continentName, int bonusValue);
		void continent_AddLinkToCountry(Country country);

	private:
		friend ostream &operator<<(ostream&, const Continent&);

		string continentName;
		int bonusValue;

};


/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

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
 * exposed to other source files where CONTINENT_LOCAL isn't defined.
 * */
#ifdef CONTINENT_LOCAL


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



#endif /* H_CONTINENT_H_ */
