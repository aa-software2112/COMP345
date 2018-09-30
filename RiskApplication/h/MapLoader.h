/*
 * MAP_LOADER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_MAP_LOADER_H_
#define H_MAP_LOADER_H_

#include <fstream>
#include <map>
#include "Utilities.h"
#include "FileReader.h"

class MapLoader {
	public:
		/** Constructor **/
		MapLoader();
		void mapLoader_LoadMap(const std::string& pathToMap);

	private:
		/** The three configuration map objects for storing key,value .map file pairs */
		map<string, string> mapConfig;
		map<string, string> continentConfig;
		map<string, string> territoryConfig;

		FileReader * mapFileReader;
		std::string mapHeaders[4] = {"[Map]", "[Continents]", "[Territories]", "EOF"};
		bool mapLoader_ParseConfig(int configIndex);
		void mapLoader_ParseMapFile(void);


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
