/*
 * main.cpp
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */
#include <iostream>

#include "MapLoader.h"
#include "Map.h"

int main()
{
	/************************************************
	 *
	 * Map Loader & Graph
	 *
	 ***********************************************/

	/** Change this path to comply with your filesystem (make sure there is a trailing forward slash) */
	string basePathToMapFolder = "C:/Users/Anthony Andreoli/Desktop/Concordia/2018 - FALL/COMP 345/REPOSITORY/COMP345/RiskApplication/MapFiles/";

	string mapFiles[] = {basePathToMapFolder + "World.map", \
							basePathToMapFolder + "Annys World.map", \
							basePathToMapFolder + "WorldMissingMap.map", \
							basePathToMapFolder + "Caribbean.map", \
							basePathToMapFolder + "Grill's Galaxy.map" \
						};

	MapLoader p;

	Map * newMap;

	if ( (newMap = p.mapLoader_LoadMap(mapFiles[3])) == NULL)
	{
		print("Could not parse file");
		return 0;
	}

	/** Map is of valid format */
	print("Map is valid!");

	/** Pull all countries - allCountries contains pointers to Country objects, so
	 * any editing you perform on these countries (with setters) will be directly
	 * changed in the graph countries (which is what we want). Aka these Country objects are exactly
	 * the same ones from the graph
	 * */
	vector<Country *> allCountries = newMap->map_GetAllCountries();

	print("********ALL COUNTRIES********");
	for (UINT i = 0; i<allCountries.size(); i++)
	{
		cout << *(allCountries[i]) << endl;
	}


	/** Pull adjacent countries */
	if (allCountries.size() > 0)
	{
		/** Pick a country you want to get adjacency of - say country at index 0 */
		Country * someCountry = allCountries[0];

		/** Get adjacent countries */
		vector<Country *> adjacentCountries = newMap->map_GetCountriesAdjacentTo(someCountry);

		print("********ADJACENT COUNTRIES ********");
		cout << "Countries Adjacent to " << *someCountry << " are:" << endl;

		for (UINT i = 0; i<adjacentCountries.size(); i++)
		{

			/** Before army set */
			cout << *(adjacentCountries[i]) << endl;

			/** Note the number of armies changing because of use of pointers */
			(*(adjacentCountries[i])).country_SetNumArmies(99);

			/** After army set */
			cout << *(adjacentCountries[i]) << endl;

		}


	}

	/************************************************
	 *
	 * 						Dice
	 *
	 ***********************************************/

	/** Put driver code here */


	/************************************************
	 *
	 *						Player
	 *
	 ***********************************************/

	/** Put driver code here */

	/************************************************
	 *
	 * 					Cards (Deck/Hand)
	 *
	 ***********************************************/

	/** Put driver code here */



	return 0;
}



