/*
 * MAP_LOADER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_MAP_LOADER_H_
#define H_MAP_LOADER_H_

#include <fstream>
#include "Utilities.h"

class MapLoader {
	public:
		/** Constructor **/
		MapLoader();
		void mapLoader_LoadMap(const std::string& pathToMap);

	private:
		bool mapLoader_FileExists(const std::string& path);


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
 * exposed to other source files where MAP_LOADER_LOCAL isn't defined.
 * */
#ifdef MAP_LOADER_LOCAL


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



#endif /* H_MAP_LOADER_H_ */
