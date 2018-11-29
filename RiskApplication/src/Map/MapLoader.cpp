
#define MAP_LOADER_LOCAL
#include "MapLoader.h"
using namespace std;

MapLoader::MapLoader() {

	this->mapFileReader = NULL;

	this->loadedMap = NULL;

}

/** Opens the file, reads it, and extracts data from it */
Map * MapLoader::mapLoader_LoadMap(const std::string& pathToMap)
{
	/** TODO: reset all attributes belonging to this object */

	/** Create new file container for current map file */
	this->mapFileReader = new FileReader(pathToMap);


	/** Extract content from .map file */
	/** TODO throw an error if map file is not parsable within defined format, or
	 * if key,value pairs are missing for any necessary section
	 */
	if(this->mapLoader_ParseMapFile())
	{
		/** Get the map name */
		vector<string> splitStringTokens;
		string delimiter = "/";
		string stringToSplit = pathToMap;

		splitString(stringToSplit, delimiter, splitStringTokens);


		/** Sets the map name */
		if (splitStringTokens.size() > 0)
		{
			this->loadedMap->map_SetMapName(splitStringTokens.back());
		}
		else
		{
			string s = "MAP NAME NOT FOUND";
			this->loadedMap->map_SetMapName(s);
		}

		return this->loadedMap;
	}
	else
	{
		delete this->loadedMap;
	}

	cout << "NULL MAP" << endl;
	return NULL;
}

/** Function attempts to extract all data from .map files:
 * Returns false if any of the headers is not found
 */
bool MapLoader::mapLoader_ParseMapFile(void)
{
	bool parsedAllSections = false;

	vector<string> stringBuffer;

	/** This will be the Map object returned to caller */
	this->loadedMap = new Map();

	/** Could not find [Map] */
	if(!this->mapFileReader->fileReader_findLineContaining(mapHeaders[0]))
	{
		return parsedAllSections;
	}

	/** [Map] found, extract [Map] configuration, then parse continents section, then territories */
	if (this->mapLoader_ParseConfig(stringBuffer, MAP))
	{
		if (!loadedMap->map_AddListToMapConfig(stringBuffer))
		{
			return false;
		}

		if(this->mapLoader_ParseConfig(stringBuffer, CONTINENTS))
		{
			/** Parse results */
			if(!loadedMap->map_AddListToContinents(stringBuffer))
			{
				return false;
			}

			if( this->mapLoader_ParseConfig(stringBuffer, TERRITORIES))
			{
				/** Parse results */
				if(!loadedMap->map_AddListToCountries(stringBuffer))
				{
					return false;
				}

				parsedAllSections = true;
			}

		}

	}


	return parsedAllSections;
}

/** Returns true if, while extracting all data from current header, the start of the
 * next header was found, otherwise returns false
 */
bool MapLoader::mapLoader_ParseConfig(vector<string>& stringBuffer, mapHeaderIdx configIndex)
{

	/** Clear string buffer */
	stringBuffer.erase(stringBuffer.begin(), stringBuffer.end());

	/** Store all strings in buffer until next header is reached */
	if(this->mapFileReader->fileReader_getStringUntilLineContaining(stringBuffer, mapHeaders[configIndex + 1]))
	{
		return true;
	}
	/** Next value was not reached */
	else
	{
		/** In the case of searching through TERRITORIES, there is no header that follows */
		if ((configIndex + 1) == END_OF_FILE)
		{
			return true;
		}

		return false;
	}


}
