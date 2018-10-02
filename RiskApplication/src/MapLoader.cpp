
#define MAP_LOADER_LOCAL
#include "MapLoader.h"
using namespace std;

MapLoader::MapLoader() {

	this->mapFileReader = NULL;

	/** The mapConfig expects 5 explicit keys, all
	 * other configurations are based on the map itself and cannot be hard-coded */
	this->mapConfig["author"];
	this->mapConfig["image"];
	this->mapConfig["wrap"];
	this->mapConfig["scroll"];
	this->mapConfig["warn"];

	print("MapLoader Constructor");

}

/** Opens the file, reads it, and extracts data from it */
void MapLoader::mapLoader_LoadMap(const std::string& pathToMap)
{
	/** TODO: reset all attributes belonging to this object */

	/** Create new file container for current map file */
	this->mapFileReader = new FileReader(pathToMap);

	/** Extract content from .map file */
	this->mapLoader_ParseMapFile();

}

/** Function attempts to extract all data from .map files:
 * Returns false if any of the headers is not found
 */
bool MapLoader::mapLoader_ParseMapFile(void)
{
	bool parsedAllSections = false;
	string stringBuffer;

	/** Could not find [Map] */
	if(!this->mapFileReader->fileReader_findLineContaining(mapHeaders[0]))
	{

		print("Invalid file format!");
		return parsedAllSections;
	}

	/** [Map] found, extract [Map] configuration, then parse continents section, then territories */
	if (this->mapLoader_ParseConfig(stringBuffer, MAP))
	{
		/** Parse results */
		print(stringBuffer);

		if(this->mapLoader_ParseConfig(stringBuffer, CONTINENTS))
		{
			/** Parse results */
			print(stringBuffer);

			if( this->mapLoader_ParseConfig(stringBuffer, TERRITORIES))
			{
				/** Parse results */
				print(stringBuffer);

				parsedAllSections = true;
			}

		}

	}
	/** The file could not be read to completion - invalid format*/
	else
	{
		print("Invalid file format!");
		parsedAllSections = false;

	}

	return parsedAllSections;
}

/** Returns true if, while extracting all data from current header, the start of the
 * next header was found, otherwise returns false
 */
bool MapLoader::mapLoader_ParseConfig(string& stringBuffer, mapHeaderIdx configIndex)
{

	/** Clear string buffer */
	stringBuffer = "";

	/** Store all strings in buffer until next header is reached */
	if(this->mapFileReader->fileReader_getStringUntilLineContaining(stringBuffer, mapHeaders[configIndex + 1]))
	{

		//print("Buffer for " + mapHeaders[configIndex] + ":\n" + stringBuffer);
		return true;

	}
	/** Next value was not reached */
	else
	{
		/** In the case of searching through TERRITORIES, there is no header that follows */
		if ((configIndex + 1) == END_OF_FILE)
		{
			//print("Buffer for " + mapHeaders[configIndex] + ":\n" + stringBuffer);
			return true;
		}

		//print("Could not find " + mapHeaders[configIndex + 1]);
		//print("Buffer for " + mapHeaders[configIndex] + ":\n" + stringBuffer);
		return false;
	}


}
