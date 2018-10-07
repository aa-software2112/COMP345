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
#include <vector>
#include "Utilities.h"
#include "Map.h"
#include "FileReader.h"

class MapLoader {
	public:
		/** Constructor **/
		MapLoader();
		Map * mapLoader_LoadMap(const std::string& pathToMap);

	private:
		/** Holds a pointer to the previously loaded map */
		Map * loadedMap;

		/** The three configuration map objects for storing key,value .map file pairs */
		map<string, string> continentConfig;
		map<string, string> territoryConfig;

		/** Enums representing index values for map header */
		enum mapHeaderIdx {
			MAP = 0,
			CONTINENTS,
			TERRITORIES,
			END_OF_FILE
		};

		FileReader * mapFileReader;
		std::string mapHeaders[4] = {"[Map]", "[Continents]", "[Territories]", "EOF"};
		//bool mapLoader_ParseConfig(string& stringBuffer, mapHeaderIdx configIndex);
		bool mapLoader_ParseConfig(vector<string>& stringBuffer, mapHeaderIdx configIndex);
		void mapLoader_ExtractFromBuffer(mapHeaderIdx);
		bool mapLoader_ParseMapFile(void);


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
