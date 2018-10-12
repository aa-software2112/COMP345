/*
 * Player.h
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */

#ifndef RISKAPPLICATION_H_PLAYER_H_
#define RISKAPPLICATION_H_PLAYER_H_

#include <vector>
#include "Country.h"
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Card.h"
#include "Hand.h"


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

		Player returnOwner(Country *currentCountry);

	private:
		string playerName;
		DiceRollingFacility myDRF;
		Hand myHand;
		std::vector<Country*> collectionOfCountries;
};



#endif /* RISKAPPLICATION_H_PLAYER_H_ */
