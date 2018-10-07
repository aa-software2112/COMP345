/*
 * COUNTRY.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_COUNTRY_H_
#define H_COUNTRY_H_

#include <map>
#include "Utilities.h"
#include "Continent.h"
using namespace std;

class Continent;

class Country {
	public:
		/** Constructor **/
		Country(void);
		Country(string countryName);
		Country(Continent * linkContinent, string countryName, UINT xCoordinate, UINT yCoordinate );
		string country_GetName(void);
		void country_SetXCoordinate(UINT x);
		void country_SetYCoordinate(UINT y);
		void country_SetContinent(Continent * linkContinent);

	private:
		/** A pointer to the continent that this country belongs to */
		Continent * parentContinent;
		UINT xCoordinate;
		UINT yCoordinate;
		string countryName;
		friend ostream& operator<<(ostream&, const Country&);

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
 * exposed to other source files where COUNTRY_LOCAL isn't defined.
 * */
#ifdef COUNTRY_LOCAL


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



#endif /* H_COUNTRY_H_ */
