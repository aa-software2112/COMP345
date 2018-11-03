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
#include "RiskGame.h"
#include "Country.h"
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Card.h"
#include "Hand.h"

class Continent;
class RiskGame;

class Player {
	public:
		/** Constructor **/
		Player();
		Player(string name);

		string player_getPlayerName();
		DiceRollingFacility* player_getMyDRF();
		Hand* player_getMyHand();
		std::vector<Country*> player_getMyCountries();
		bool player_checkCountryOwnership(Country* currentCountry);

		void player_reinforce(RiskGame* currentGame);
		void player_attack(RiskGame* currentGame);
		void player_fortify(RiskGame* currentGame);

		void player_addCountry(Country *newCountry);
		void player_removeCountry(Country *newCountry);

		/** Gets the total number of armies owned by a player */
		unsigned int player_getTotalNumberArmies(void);

		/** Gets a set of all unique continents that have countries owned by player */
		set<Continent *> * player_getUniqueContinents(void);

		Player player_returnOwner(Country *currentCountry);
		friend ostream& operator<<(ostream& output, Player& p);

	private:
		string myName;
		DiceRollingFacility myDRF;
		Hand myHand;
		vector<Country*> myCollectionOfCountries;
};



#endif /* RISKAPPLICATION_H_PLAYER_H_ */
