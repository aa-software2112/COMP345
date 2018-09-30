
#define MAP_LOADER_LOCAL
#include "MapLoader.h"
using namespace std;

MapLoader::MapLoader() {

	this->mapFileContainer = NULL;
	print("MapLoader Constructor");

}

/** Opens the file, reads it, and extracts data from it */
void MapLoader::mapLoader_LoadMap(const std::string& pathToMap)
{

	/** Create new file container for current map file */
	this->mapFileContainer = new FileContainer(pathToMap);

	this->mapFileContainer->fileContainer_openFileInMode(FileContainer::fileOperation::READ);

	this->mapFileContainer->fileContainer_displayRemainingContents();

}

