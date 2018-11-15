
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

Map::~Map()
{

}

bool Map::map_AddListToMapConfig(vector<string>& keyValueString)
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
			else
			{
				return false;
			}

		}
	}

	return true;


}

bool Map::map_AddListToContinents(vector<string>& keyValueString)
{
	/** Assumes the format is "someContinent=SomeValue" */
	regex mapConfigPattern("([\\W\\w\\s]+)=([0-9]+)");
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
			else
			{
				return false;
			}

		}
	}

	return true;

}

bool Map::map_AddListToCountries(vector<string>& commaSeparatedStrings)
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

		/** The first five values, from Index 0 -> Index 3 should be available */
		if (splitStringContainer.size() >= 4)
		{
			/** Format of each is checked here - if all are valid, entries are processed */
			if ( (splitStringContainer[0] != "") && isNumeric(splitStringContainer[1]) &&
					isNumeric(splitStringContainer[2]) && (mapContinents.find(splitStringContainer[3]) != mapContinents.end()) )
			{

				/** Will be used to obtain vertex stored into graph */
				Graph<Country, string>::Vertex * countryVertex;
				Graph<Country, string>::Vertex * countryAtOtherEndVertex;
				Graph<Country,string>::Edge * edgeBetweenVertices; // unused?

				/** Country already exists */
				if ( mapCountries.find(splitStringContainer[0]) != mapCountries.end() )
				{
					/** Add remaining data to it (x, y, and continent)*/
					Country *tempCountry = mapCountries[splitStringContainer[0]];
					tempCountry->country_SetXCoordinate((UINT) (strtol(splitStringContainer[1].c_str(), NULL, 10) ));
					tempCountry->country_SetYCoordinate((UINT) (strtol(splitStringContainer[2].c_str(), NULL, 10) ));
					tempCountry->country_SetContinent(mapContinents[splitStringContainer[3]]);
					mapContinents[splitStringContainer[3]]->continent_AddLinkToVertex(mapVertex[splitStringContainer[0]]);

				}
				/** Country doesn't exist yet */
				else
				{
					int xCoord = (UINT) (strtol(splitStringContainer[1].c_str(), NULL, 10) );
					int yCoord = (UINT) (strtol(splitStringContainer[2].c_str(), NULL, 10) );

					Country *tempCountry = new Country(mapContinents[splitStringContainer[3]], \
							splitStringContainer[0], xCoord, yCoord, NULL);

					mapCountries[splitStringContainer[0]] = tempCountry;

					/** A country should be added to list of vertices in graph */
					countryVertex = graph.graph_InsertVertex(tempCountry);

					/** Add vertex to mapVertex (to see which vertex values already exist by string key) */
					mapVertex[splitStringContainer[0]] = countryVertex;


					mapContinents[splitStringContainer[3]]->continent_AddLinkToVertex(countryVertex);
				}

				/** Loop over all countries (Vx) and add them to some graph function addEdge(Vu, Vx) */
				size_t countryLinkIndex = 0;
				countryVertex = mapVertex[splitStringContainer[0]];

				Country *tempCountry;
				Graph<Country, string>::Vertex *tempVertex;

				for(countryLinkIndex = 4; countryLinkIndex < splitStringContainer.size(); countryLinkIndex++)
				{

					/** Skip this entry, it is blank */
					if (splitStringContainer[countryLinkIndex] == "")
					{
						continue;
					}

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
			else
			{
				/** Incorrect format for the first four entries of the row */
				return false;
			}

		}
		else
		{
			/** Not an empty line */
			if (!(splitStringContainer.size() == 1 && ( (splitStringContainer[0] == "\n") || (splitStringContainer[0] == "\r") || \
					(splitStringContainer[0] == "\n\r") || (splitStringContainer[0].c_str()[0] == NULL))))
			{

				/** Not enough data to create a vertex/country */
				return false;
			}

		}


	}


	return true;

}

vector<Country *> Map::map_GetCountriesAdjacentTo(Country * someCountry)
{
	/** Should only be passing countries to this function that come from the graph (not ones created outside of Map object) */

	/** Adjacent-country container */
	vector<Country *> adjacentCountries;

	/** Get vertex corresponding to parameter country */
	Graph<Country, string>::Vertex * vertexOfCountry = mapVertex[someCountry->country_GetName()];

	/** For each vertex and edge v, e connected to u */
	map<Graph<Country, string>::Vertex *, Graph<Country, string>::Edge *> * adjacencyMap = (*vertexOfCountry).vertex_GetOutgoing();

	for (typename std::map<Graph<Country, string>::Vertex *, Graph<Country, string>::Edge *>::iterator it=(*adjacencyMap).begin(); it!=(*adjacencyMap).end(); ++it)
	{
		adjacentCountries.push_back( (*(it->first)).vertex_GetElementPtr());
	}

	return adjacentCountries;

}

vector<Country *> Map::map_GetAllCountries(void)
{
	/** Pull vertices list */
	vector<Graph<Country, string>::Vertex *> * allVertices = graph.graph_GetVertices();

	/** Country container */
	vector<Country *> allCountriesContainer;

	/** Iterate over all vertices, extract countries form them */
	for(unsigned int i = 0; i< (*allVertices).size(); i++)
	{
		allCountriesContainer.push_back( (*((*allVertices)[i])).vertex_GetElementPtr());
	}


	return allCountriesContainer;

}

bool Map::map_IsConnected(void)
{
	return this->graph.graph_isConnected();
}

bool Map::map_AllContinentsConnectedSubgraphs(void)
{

	bool allConnected = true;
	Continent * nextContinent;
	set<Graph<Country, string>::Vertex *> subGraphOfVertices;

	/** Iterate over all continents */
	for (map<string,Continent*>::iterator it=mapContinents.begin(); it!=mapContinents.end(); ++it)
	{
		nextContinent = it->second;

		subGraphOfVertices = nextContinent->continent_GetVerticesAsSet();

		cout << "Checking subgraph connectivity of Continent: " + nextContinent->continent_GetContinentName() << endl;

		allConnected &= this->graph.graph_IsConnectedSubgraph(subGraphOfVertices);


	}

	return allConnected;

}

bool Map::map_IsValidMap(void)
{

	/** Checks that the map is connected, and all subgraphs are conencted subgraphs */
	return this->map_IsConnected() && this->map_AllContinentsConnectedSubgraphs();


}

void Map::map_DisplayAllContinentSizes(void)
{

	for (map<string,Continent*>::iterator it=mapContinents.begin(); it!=mapContinents.end(); ++it)
	{
		cout << it->first << "=" << *(it->second) << " with #Countries: " << (*(it->second)).continent_GetNumberOfCountries() << endl;
		(*(it->second)).continent_DisplayCountries();
	}
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

int Map::map_GetNumCountries(void)
{
	return this->mapVertex.size();
}


map<Player *, vector<Country *> *> Map::map_getPlayerToCountryMapping(void)
{
	/** Creates the initial map */
	map<Player *, vector<Country *> *> playerToCountryMap = new map<Player *, vector<Country *> *>;

	/** Iterate through each country */
	for(map<string, Country*>::iterator it = mapCountries.begin(); it < mapCountries.end(); it++)
	{
		/** Capture the country */
		Country * c = (it)->second;

		/** Capture the player that owns it */
		Player * p = c->country_GetOwner();

		/** Check that the player already exists, if not, create the vector in memory */
		if (playerToCountryMap.count(p) == 0)
		{
			playerToCountryMap[p] = new vector<Country *>;
		}


		/** Add the country to the player map */
		playerToCountryMap[p]->push_back(c);


	}

	return playerToCountryMap;

}

