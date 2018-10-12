/*
 * DiceRollingFacility.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Joy Anne Valdez
 */

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "DiceRollingFacility.h"
#include <iostream>

using namespace std;

void DiceRollingFacility::rollDice(int numDiceRolled){

	resultsRolled[0] = 0;
	resultsRolled[1] = 0;
	resultsRolled[2] = 0;

	for(int x = 0; x < numDiceRolled;x++){
		int valueRolled = rand()% 6 + 1;        // Generates a random number between 1 and 6
		resultsRolled[x] = valueRolled;
		if(valueRolled == 1){                   // The amount of times a [1] was rolled
			rolledOne++;
		}
		else if(valueRolled == 2){               // The amount of times a [2] was rolled
			rolledTwo++;
		}
		else if(valueRolled == 3){               // The amount of times a [3] was rolled
			rolledThree++;
		}
		else if(valueRolled == 4){               // The amount of times a [4] was rolled
			rolledFour++;
		}
		else if(valueRolled == 5){               // The amount of times a [5] was rolled
			rolledFive++;
		}
		else {                                   // The amount of times a [6] was rolled
			rolledSix++;
		}
		totalRolls++;
	}
    //*****************************************************************************************
	if(numDiceRolled == 3) {                // Three Dice Roll Sorting Container
		int highest;
		int nextHighest;
		int lowest;
        // when resultsRolled[0] has highest value
		if(resultsRolled[0] >= resultsRolled[1] && resultsRolled[0] >= resultsRolled[2]) {
			highest = resultsRolled[0];

			if(resultsRolled[1] >= resultsRolled[0]){
				nextHighest = resultsRolled[1];
				lowest = resultsRolled[2];
			}
			else {
				nextHighest = resultsRolled[2];
				lowest = resultsRolled[1];
			}

		}
        // when resultsRolled[1] has highest value
		if(resultsRolled[1] >= resultsRolled[0] && resultsRolled[1] >= resultsRolled[2]) {
			highest = resultsRolled[1];

			if(resultsRolled[0] >= resultsRolled[2]){
				nextHighest = resultsRolled[0];
				lowest = resultsRolled[2];
			}
			else {
				nextHighest = resultsRolled[2];
				lowest = resultsRolled[0];
			}

		}
        // when resultsRolled[2] has highest value
		if(resultsRolled[2] >= resultsRolled[0] && resultsRolled[2] >= resultsRolled[1]) {
			highest = resultsRolled[2];

			if(resultsRolled[0] >= resultsRolled[1]){
				nextHighest = resultsRolled[0];
				lowest = resultsRolled[1];
			}
			else {
				nextHighest = resultsRolled[1];
				lowest = resultsRolled[0];
			}
		}
        // Sorting array from highest to lowest
		resultsRolled[0] = highest;
		resultsRolled[1] = nextHighest;
		resultsRolled[2] = lowest;
	}
    //*****************************************************************************************
	else if (numDiceRolled == 2) {              // Two Dice Roll Sorting Container
		int highest;
		int lowest;
		if(resultsRolled[0] >= resultsRolled[1]) {      // when resultsRolled[0] has highest value
			highest = resultsRolled[0];
			lowest = resultsRolled[1];
		}
		else {                                          // when resultsRolled[1] has highest value
			highest = resultsRolled[1];
			lowest = resultsRolled[0];
		}
        // Sorting array from highest to lowest
		resultsRolled[0] = highest;
		resultsRolled[1] = lowest;
	}
}
//*****************************************************************************************
void DiceRollingFacility::printPlayerDiceStatistics() {
	if(totalRolls == 0) {
		cout << "This player hasn't rolled any dice yet." << endl;
	}
	else {
		/* Storing default precision */
		streamsize ss = std::cout.precision();
		cout << "-----------------------------" << endl;
		cout << fixed << setprecision(2);
		cout << "1: " <<  rolledOne / (double)totalRolls * 100 << "%" << endl;
		cout << "2: " <<  rolledTwo / (double)totalRolls * 100 << "%" << endl;
		cout << "3: " <<  rolledThree / (double)totalRolls * 100 << "%" << endl;
		cout << "4: " <<  rolledFour / (double)totalRolls * 100 << "%" << endl;
		cout << "5: " <<  rolledFive / (double)totalRolls * 100 << "%" << endl;
		cout << "6: " <<  rolledSix / (double)totalRolls * 100 << "%" << endl;
		cout << "-----------------------------" << endl;
		cout << setprecision(ss);
	}
}


