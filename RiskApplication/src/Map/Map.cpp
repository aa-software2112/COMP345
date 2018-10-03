
#define MAP_LOCAL
#include "Map.h"

Map::Map()
{
	/** Initialize the entries that are necessary for configuration */
	mapConfig[string("author")] = "";
	mapConfig[string("image")] = "";
	mapConfig[string("wrap")] = "";
	mapConfig[string("scroll")] = "";
	mapConfig[string("warn")] = "";

}

void Map::map_AddEntryToMapConfig(vector<string>& keyValueString)
{
	/** Assumes the format is "someKey=SomeValue" */
	regex mapConfigPattern("(\\w+)=([a-zA-Z.'\\s]*)");
	smatch regexMatches;

	/** Iterate over each entry in Key=Value string */
	for (vector<string>::iterator it = keyValueString.begin(); it != keyValueString.end(); it++)
	{
		/** Search for pattern */
		if(regex_match(*it, regexMatches, mapConfigPattern))
		{

			/** Expects 2 groups (1 (always) + 2 (key, value)),
			 * stores the key, value pair in map
			 * */
			if (regexMatches.size() == 3)
			{
				mapConfig[regexMatches[1]] = regexMatches[2];
			}

		}
	}

	this->map_DisplayMapConfig();

}

void Map::map_DisplayMapConfig(void)
{
	print("********MAP CONFIGURATION********");
	for (map<string,string>::iterator it=mapConfig.begin(); it!=mapConfig.end(); ++it)
	{
		print(it->first + "=" + it->second);
	}


}
