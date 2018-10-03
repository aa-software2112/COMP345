
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

void Map::map_AddListToMapConfig(vector<string>& keyValueString)
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

void Map::map_AddListToContinents(vector<string>& keyValueString)
{
	/** Assumes the format is "someContinent=SomeValue" */
	regex mapConfigPattern("([a-zA-Z0-9\\s]+)=([0-9]+)");
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
				/** Index = 1 (Continent name)
				 *  Index = 2 (Bonus value)
				 */
				mapContinents[regexMatches[1]] = new Continent(regexMatches[1], atoi(regexMatches[2].str().c_str()));
			}

		}
	}

	this->map_DisplayContinents();

}


void Map::map_DisplayContinents(void)
{
	print("********CONTINENTS********");
	for (map<string,Continent*>::iterator it=mapContinents.begin(); it!=mapContinents.end(); ++it)
	{
		cout << it->first << "=" << *(it->second);
	}


}


void Map::map_DisplayMapConfig(void)
{
	print("********MAP CONFIGURATION********");
	for (map<string,string>::iterator it=mapConfig.begin(); it!=mapConfig.end(); ++it)
	{
		print(it->first + "=" + it->second);
	}


}
