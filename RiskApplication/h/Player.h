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
		string playerName;
		DiceRollingFacility myDRF;
		Hand myHand;
		std::vector<Country*> collectionOfCountries;

		/** Constructor **/
		Player();
		Player(string name);

		void reinforce();
		void attack(Map *currentMap);
		void fortity(Map *currentMap);

		void addCountry(Country *newCountry);
		void removeCountry(Country *newCountry);

		int exchange(Map *currentMap);

		Player returnOwner(Country *currentCountry);

};



#endif /* RISKAPPLICATION_H_PLAYER_H_ */
