
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

void Map::map_AddListToCountries(vector<string>& commaSeparatedStrings)
{
	string delimiterByComma(",");
	vector<string> splitStringContainer;


	/** Iterate over each entry in Key=Value string */
	for (vector<string>::iterator it = commaSeparatedStrings.begin(); it != commaSeparatedStrings.end(); it++)
	{
		/** Split comma separated string */
		splitString(*it, delimiterByComma, splitStringContainer);

		/** Size of split string (which is a territory) must be AT-LEAST 5, defined as
		 * Index 0: New Country/Territory (Non-blank string)
		 * Index 1: X-coordinate (must be numeric)
		 * Index 2: Y-coordinate (must be numeric)
		 * Index 3: Continent that Index 0 belongs to (must exist as a continent object by this point in 'mapContinents')
		 * Index 4: At least 1 country that Index 0 connects to
		 * Index 5 +: All other countries that Index 0 connects to
		 */

		/** The first five values, from Index 0 -> Index 4 should be available */
		if (splitStringContainer.size() >= 5)
		{
			/** Format of each is checked here - if all are valid, entries are processed */
			if ( (splitStringContainer[0] != "") && isNumeric(splitStringContainer[1]) &&
					isNumeric(splitStringContainer[2]) && (mapContinents.find(splitStringContainer[3]) != mapContinents.end()) )
			{
				//print("\nNEW COUNTRY");
				//print(splitStringContainer);


				/** Create the country ... TODO implement mapCountries as <string, Vertex<Country>> once Graph is implemented */
				/** TODO add the country to the list of verticies with edges - Vu is made here */
				/** Check if current country already exists (made by a previous entry) */

				/** Will be used to obtain vertex stored into graph */
				Graph<Country, string>::Vertex * countryVertex;
				Graph<Country, string>::Vertex * countryAtOtherEndVertex;
				Graph<Country,string>::Edge * edgeBetweenVertices;

				if ( mapCountries.find(splitStringContainer[0]) != mapCountries.end() )
				{
					/** Add remaining data to it (x, y, and continent)*/
					Country *tempCountry = mapCountries[splitStringContainer[0]];
					tempCountry->country_SetXCoordinate((UINT) (strtol(splitStringContainer[1].c_str(), NULL, 10) ));
					tempCountry->country_SetYCoordinate((UINT) (strtol(splitStringContainer[2].c_str(), NULL, 10) ));
					tempCountry->country_SetContinent(mapContinents[splitStringContainer[3]]);

				}
				/** Country doesn't exist yet */
				else
				{
					int xCoord = (UINT) (strtol(splitStringContainer[1].c_str(), NULL, 10) );
					int yCoord = (UINT) (strtol(splitStringContainer[2].c_str(), NULL, 10) );

					Country *tempCountry = new Country(mapContinents[splitStringContainer[3]], \
							splitStringContainer[0], xCoord, yCoord);

					mapCountries[splitStringContainer[0]] = tempCountry;

					/** A country should be added to list of vertices in graph */
					countryVertex = graph.graph_InsertVertex(tempCountry);

					/** Add vertex to mapVertex (to see which vertex values already exist by string key) */
					mapVertex[splitStringContainer[0]] = countryVertex;
				}

				/** Loop over all countries (Vx) and TODO add them to some graph function addEdge(Vu, Vx) */
				size_t countryLinkIndex = 0;
				countryVertex = mapVertex[splitStringContainer[0]];

				Country *tempCountry;
				Graph<Country, string>::Vertex *tempVertex;

				for(countryLinkIndex = 4; countryLinkIndex < splitStringContainer.size(); countryLinkIndex++)
				{

					/** Country linking to country at Index 0 does not exist; must be created first */
					if ( mapCountries.find(splitStringContainer[countryLinkIndex]) == mapCountries.end() )
					{
						tempCountry =  new Country(splitStringContainer[countryLinkIndex]);

						mapCountries[splitStringContainer[countryLinkIndex]] = tempCountry;

						/** Insert next country */
						countryAtOtherEndVertex = graph.graph_InsertVertex(tempCountry);
						mapVertex[splitStringContainer[countryLinkIndex]] = countryAtOtherEndVertex;

						/** Insert edge between two countries */
						edgeBetweenVertices = graph.graph_InsertEdgeBetween(countryVertex, countryAtOtherEndVertex);
					}
					/** TODO Country already exists, add it as an edge, vertex pair to Vu */
					else
					{
						tempVertex = mapVertex[splitStringContainer[countryLinkIndex]];

						/** Insert edge between two countries */
						edgeBetweenVertices = graph.graph_InsertEdgeBetween(countryVertex, tempVertex);


					}


				}

			}

		}


	}

	graph.graph_DisplayGraph();

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
