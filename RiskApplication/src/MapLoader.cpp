
#define MAP_LOADER_LOCAL
#include "MapLoader.h"
using namespace std;

MapLoader::MapLoader() {

	print("MapLoader Constructor");

}

/** Opens the file, reads it, and extracts data from it */
void MapLoader::mapLoader_LoadMap(const std::string& pathToMap)
{

	/** Check if file exists - TODO throw an exception if this occurs*/
	if (!this->mapLoader_FileExists(pathToMap))
	{
		print ("File does not exist!");
		return;
	}

	/** Open the file */
	fstream mapHdl;
	string lineRead;

	mapHdl.open(pathToMap.c_str(), std::ios::in );

	/** Read entire contents of file */
	while (getline(mapHdl, lineRead))
	{
		print(lineRead);
	}


	mapHdl.close();

}

/** Checks if a file exists */
bool MapLoader::mapLoader_FileExists(const std::string& path)
{
	FILE * file = fopen(path.c_str(), "r");

	if (file == NULL)
	{
		return false;
	}

	fclose(file);
	return true;

}
