/*
 * Player.h
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */

#ifndef RISKAPPLICATION_H_PLAYER_H_
#define RISKAPPLICATION_H_PLAYER_H_

#include <vector>
#include <set>
#include "Utilities.h"
using namespace std;
#include "Country.h"
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Card.h"
#include "Hand.h"

class Continent;

class Player {
	public:
		/** Constructor **/
		Player();
		Player(string name);

		string player_getPlayerName();
		DiceRollingFacility* player_getMyDRF();
		Hand* player_getMyHand();
		std::vector<Country*> player_getMyCountries();

		void reinforce(Map *currentMap);
		void attack(Map *currentMap);
		void fortify(Map *currentMap);

		void addCountry(Country *newCountry);
		void removeCountry(Country *newCountry);

		int exchange(Map *currentMap);

		/** Gets the total number of armies owned by a player */
		int player_getTotalNumberArmies(void);

		/** Gets a set of all unique continents that have countries owned by player */
		set<Continent *> * player_getUniqueContinents(void);

		Player returnOwner(Country *currentCountry);
		friend ostream& operator<<(ostream& output, Player& p);

	private:
		string playerName;
		DiceRollingFacility myDRF;
		Hand myHand;
		vector<Country*> collectionOfCountries;
};



#endif /* RISKAPPLICATION_H_PLAYER_H_ */
