
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

	/** Create new file container for current map file */
	this->mapFileReader = new FileReader(pathToMap);

	/** Found [Map], parse and store key, value pairs until [Continents] */
	if(this->mapFileReader->fileReader_findLineContaining(mapHeaders[0]))
	{

		this->mapLoader_ParseMapFile();

	}
	/**
	this->mapFileReader->fileReader_findLineContaining(mapHeaders[1]);
	this->mapFileReader->fileReader_findLineContaining(mapHeaders[2]);
	*/
}

void MapLoader::mapLoader_ParseMapFile(void)
{

	/** Map configuration was parsed and reached [Continents] */
	if (this->mapLoader_ParseConfig(0))
	{
		/** Continents were parsed and reached [Territories] */
		if(this->mapLoader_ParseConfig(1))
		{

			if (this->mapLoader_ParseConfig(2))
			{

				return;
			}


		}


	}


}

bool MapLoader::mapLoader_ParseConfig(int configIndex)
{
	string stringBuffer;

	/** Store all strings in buffer until [Continents] is reached */
	if(this->mapFileReader->fileReader_getStringUntilLineContaining(stringBuffer, mapHeaders[configIndex + 1]))
	{

		print("Buffer for " + mapHeaders[configIndex] + ":\n" + stringBuffer);
		return true;

	}
	/** Continents was not reached */
	else
	{
		print("Could not find " + mapHeaders[configIndex + 1]);
		print("Buffer for " + mapHeaders[configIndex] + ":\n" + stringBuffer);
		return false;
	}



}
