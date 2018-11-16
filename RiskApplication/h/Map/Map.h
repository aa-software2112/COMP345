/*
 * MAP.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_MAP_H_
#define H_MAP_H_

#include <map>
#include <regex>
#include <locale>
#include "Continent.h"
#include "Country.h"
#include "Graph.h"
#include "Utilities.h"
#include "Subject.h"
using namespace std;

class Player;

class Map: public Subject {
	public:
		int setsTraded = 0;
		/** Constructor **/
		Map();
		~Map();
		bool map_AddListToMapConfig(vector<string>& keyValueString);
		bool map_AddListToContinents(vector<string>& keyValueString);
		bool map_AddListToCountries(vector<string>& keyValueString);
		void map_DisplayAllContinentSizes(void);
		bool map_AllContinentsConnectedSubgraphs(void);
		bool map_IsValidMap(void);
		vector<Country *> map_GetCountriesAdjacentTo(Country * someCountry);
		vector<Country *> map_GetAllCountries(void);
		bool map_IsConnected(void);
		int map_GetNumCountries(void);

		/** This is for the observer to call, in order to get the state of the map
		 * in terms of player ownership of countries
		 */
		map<Player *, vector<Country *> *> * map_GetPlayerToCountryMapping(void);

	private:
		/** Graph where nodes contain countries, and edges contain strings */
		Graph<Country, string> graph;
		map<string, string> mapConfig;
		map<string, Continent*> mapContinents;
		map<string, Country*> mapCountries;
		map<string, Graph<Country, string>::Vertex *> mapVertex;
		void map_DisplayMapConfig(void);
		void map_DisplayContinents(void);

};

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where MAP_LOCAL isn't defined.
 * */
#ifdef MAP_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_MAP_H_ */
