/*
 * DiceRollingFacility.h
 *
 *  Created on: Oct 9, 2018
 *      Author: Joy Anne Valdez
 */

#ifndef RISKAPPLICATION_H_DICEROLLINGFACILITY_H_
#define RISKAPPLICATION_H_DICEROLLINGFACILITY_H_

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "utilities.h"
#include <time.h>

class DiceRollingFacility{
	public:
		DiceRollingFacility();

		int resultsRolled[3];
        /* The following declared values will keep track of how many times each dice value is rolled. */
		int rolledOne = 0, rolledTwo = 0, rolledThree = 0, rolledFour = 0, rolledFive = 0, rolledSix = 0, totalRolls = 0;

		void diceRollingFacility_rollDice(int numDiceRolled);

		void diceRollingFacility_printPlayerDiceStatistics();       // Displays percentages of all individual values rolled.
};






#endif /* RISKAPPLICATION_H_DICEROLLINGFACILITY_H_ */
