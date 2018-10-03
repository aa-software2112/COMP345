/*
 * MAP.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_MAP_H_
#define H_MAP_H_

#include <map>
#include <regex>
#include "Utilities.h"
using namespace std;

class Map {
	public:
		/** Constructor **/
		Map();
		void map_AddEntryToMapConfig(vector<string>& keyValueString);

	private:
		/** Contains the configuration options under [MAP] header */
		map<string, string> mapConfig;
		void map_DisplayMapConfig(void);

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
 * exposed to other source files where MAP_LOCAL isn't defined.
 * */
#ifdef MAP_LOCAL


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



#endif /* H_MAP_H_ */
