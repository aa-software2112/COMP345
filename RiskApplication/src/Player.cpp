/*
 * Player.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */
#include <iostream>
#include "Player.h"
#include "Country.h"
#include "Map.h"
#include <vector>
#include "Card.h"

Player::Player(){
}

Player::Player(string newName){
	playerName = newName;
}



void Player::reinforce(){
	cout << "Reinforcing";
	/* Calculating the amount of new armies at the start of the turn */
	int newArmiesCount = collectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* STILL NEED TO IMPLEMENT FUNCTION THAT CHECKS IF PLAYER CONTROLS A FULL CONTINENT */
	bool controlsFullContinent = false;

	/* Bonus armies if player controls a whole continent */
	if(controlsFullContinent) {
		int continentNum = 0;
		switch(continentNum){
			case 1:	cout << "5 Bonus armies for controlling N. America" << endl;
					newArmiesCount = newArmiesCount + 5;
					break;
			case 2:	cout << "2 Bonus armies for controlling S. America" << endl;
					newArmiesCount = newArmiesCount + 2;
					break;
			case 3:	cout << "3 Bonus armies for controlling Africa" << endl;
					newArmiesCount = newArmiesCount + 3;
					break;
			case 4:	cout << "7 Bonus armies for controlling Asia" << endl;
					newArmiesCount = newArmiesCount + 7;
					break;
			case 5:	cout << "5 Bonus armies for controlling Asia" << endl;
					newArmiesCount = newArmiesCount + 5;
					break;
			case 6:	cout << "2 Bonus armies for controlling Australia" << endl;
					newArmiesCount = newArmiesCount + 2;
					break;
			default:cout << "No army bonus from continent control" << endl;
					break;
		}
	}

	bool cardsForArmiesRequest = false;

	/* If player's hand has 5 or more cards, they MUST exchange for armies (not coded yet) */

	/* Reserved for force-exchange code */

	if(cardsForArmiesRequest){
		int valueReturnedByExchangeFunction = 0;
		newArmiesCount = newArmiesCount + valueReturnedByExchangeFunction;
	}

	/* Display all countries owned by player */

	unsigned int countryIndex;
	int numOfArmiesPlaced;

	while(newArmiesCount != 0){
		cout << "List of my countries:" << endl;

		for(unsigned int x = 0; x < collectionOfCountries.size(); x++){
			cout << "[" << x << "] " << *collectionOfCountries[x] << endl;
		}

		cout << "Where would you like place your new army unit(s)?" << " (" << newArmiesCount << " unit(s) left!) Enter the country index." << endl;
		cin >> countryIndex;

		if(countryIndex < 0 || countryIndex >= collectionOfCountries.size()){
			cout << "Index value out of range! Please select a valid index." << endl;
			cout << "Where would you like place your new army unit(s)?" << " (" << newArmiesCount << " unit(s) left!) Enter the country index." << endl;
			cin >> countryIndex;
		}

		cout << "How many army unit(s) would you like to place here?" << " (" << newArmiesCount << " unit(s) left!)" << endl;
		cin >> numOfArmiesPlaced;

		if(numOfArmiesPlaced > newArmiesCount){
			cout << "You do not have enough army units left!" << endl;
			cout << "How many army unit(s) would you like to place here?" << " (" << newArmiesCount << " units left!)" << endl;
			cin >> numOfArmiesPlaced;
		}
		unsigned int currentArmiesOnCountry = collectionOfCountries[countryIndex]->country_GetNumArmies();

		collectionOfCountries[countryIndex]->country_SetNumArmies(currentArmiesOnCountry + numOfArmiesPlaced);

		newArmiesCount = newArmiesCount - numOfArmiesPlaced;
	}
}


void Player::attack(Map *currentMap){

	bool attacking = true;

	while (attacking){
		cout << "Attacking" << endl;

		vector<Country *> countriesAvailableToAttack;

		cout << "List of my countries:" << endl << endl;

		for (unsigned int x = 0; x < collectionOfCountries.size();x++) {
			if(collectionOfCountries[x]->country_GetOwner() == this) {
				if(collectionOfCountries[x]->country_GetNumArmies() >= 2){
					vector<Country *> vectorOfAdjacentCountries = currentMap->map_GetCountriesAdjacentTo(collectionOfCountries[x]);

					for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
						if (vectorOfAdjacentCountries[y]->country_GetOwner() != this) {
							cout << collectionOfCountries[x]->country_GetName() << " may attack " << vectorOfAdjacentCountries[y]->country_GetName() << endl;
						}
					}
				}
			}
		}

		cout << endl;

		int attackInput = 0;
		cout << "Do you wish to attack? Enter 0 for no and 1 for yes." << endl;
		cin >> attackInput;

		if(attackInput == 0){
			attacking = false;
		}
		else {
			string nameOfAttackingCountry = "";
			string nameOfDefendingCountry = "";

			cout << "Which country do you wish to attack with?" << endl;
			cin >> nameOfAttackingCountry;

			cout << "Which country do you wish to attack?" << endl;
			cin >> nameOfDefendingCountry;

			vector<Country *> vectorOfAllCountries = currentMap->map_GetAllCountries();

			for(unsigned int i = 0; i < vectorOfAllCountries.size();i++){
				if(nameOfAttackingCountry == vectorOfAllCountries[i]->country_GetName()){
					for(unsigned int j = 0; j < vectorOfAllCountries.size();j++){
						if(nameOfDefendingCountry == vectorOfAllCountries[j]->country_GetName()){

							cout << nameOfAttackingCountry << " has " << vectorOfAllCountries[i]->country_GetNumArmies() << " armies." << endl;
							cout << nameOfDefendingCountry << " has " << vectorOfAllCountries[j]->country_GetNumArmies() << " armies." << endl;

							Player* attacker = vectorOfAllCountries[i]->country_GetOwner();
							Player* defender = vectorOfAllCountries[j]->country_GetOwner();

							int numOfDiceAttacker;
							int numOfDiceDefender;

							if(vectorOfAllCountries[i]->country_GetNumArmies() == 2) {
								numOfDiceAttacker = 1;
							}
							else if (vectorOfAllCountries[i]->country_GetNumArmies() == 3){
								numOfDiceAttacker = 2;
							}
							else {
								numOfDiceAttacker = 3;
							}
							attacker->myDRF.rollDice(numOfDiceAttacker);

							if(vectorOfAllCountries[j]->country_GetNumArmies() == 1) {
								numOfDiceDefender = 1;
							}
							else {
								numOfDiceDefender = 2;
							}
							defender->myDRF.rollDice(numOfDiceDefender);

							cout << "Num of dice attacker: " << numOfDiceAttacker << endl;
							cout << "Num of dice defender: " << numOfDiceDefender << endl;

							cout << "Attacker: " << endl;
							cout << attacker->myDRF.resultsRolled[0] << endl;
							cout << attacker->myDRF.resultsRolled[1] << endl;
							cout << attacker->myDRF.resultsRolled[2] << endl;

							cout << "Defender: " << endl;
							cout << defender->myDRF.resultsRolled[0] << endl;
							cout << defender->myDRF.resultsRolled[1] << endl;
							cout << defender->myDRF.resultsRolled[2] << endl;

							if(numOfDiceAttacker == 1 && numOfDiceDefender == 1){
								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetOwner(vectorOfAllCountries[i]->country_GetOwner());
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
							else if(numOfDiceAttacker == 1 && numOfDiceDefender == 2){
								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
							else if(numOfDiceAttacker == 2 && numOfDiceDefender == 1){
								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetOwner(vectorOfAllCountries[i]->country_GetOwner());
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() + 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
							else if (numOfDiceAttacker == 2 && numOfDiceDefender == 2){
								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
								if(attacker->myDRF.resultsRolled[1] > defender->myDRF.resultsRolled[1]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
							else if(numOfDiceAttacker == 3 && numOfDiceDefender == 1){
								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
							else if (numOfDiceAttacker == 3 && numOfDiceDefender == 2){


								if(attacker->myDRF.resultsRolled[0] > defender->myDRF.resultsRolled[0]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}


								if(attacker->myDRF.resultsRolled[1] > defender->myDRF.resultsRolled[1]){
									vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() - 1);
								}
								else {
									vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - 1);
								}
							}
						}
					}
				}
			}

		}


	}

	/* Implement dice roll code (Player chooses how many dice, etc */


}


void Player::fortity(Map *currentMap){

	cout << "Fortifying" << endl;

	cout << "List of my countries:" << endl << endl;

	for (unsigned int x = 0; x < collectionOfCountries.size();x++) {
		if(collectionOfCountries[x]->country_GetOwner() == this) {
			if(collectionOfCountries[x]->country_GetNumArmies() >= 2){
				vector<Country *> vectorOfAdjacentCountries = currentMap->map_GetCountriesAdjacentTo(collectionOfCountries[x]);

				for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
					if (vectorOfAdjacentCountries[y]->country_GetOwner() == this) {
						cout << collectionOfCountries[x]->country_GetName() << " may fortify " << vectorOfAdjacentCountries[y]->country_GetName() << endl;
					}
				}
			}
		}
	}

	int fortifyInput = 0;
	cout << "Do you wish to fortify? Enter 0 for no and 1 for yes." << endl;
	cin >> fortifyInput;

	if(fortifyInput == 1){
		string fromCountry = "";
		string toCountry = "";

		cout << "Which country do you wish to fortify from?" << endl;
		cin >> fromCountry;

		cout << "Which country do you wish to fortify to?" << endl;
		cin >> toCountry;

		vector<Country *> vectorOfAllCountries = currentMap->map_GetAllCountries();

		for(unsigned int i = 0; i < vectorOfAllCountries.size();i++){
			if(fromCountry == vectorOfAllCountries[i]->country_GetName()){
				for(unsigned int j = 0; j < vectorOfAllCountries.size();j++){
					if(toCountry == vectorOfAllCountries[j]->country_GetName()){
						bool fortifyNumberFlag = false;

						while (!fortifyNumberFlag) {

							int numOfArmiesToMove = 0;
							cout << "How many army units would you like to move? (There are " << vectorOfAllCountries[i]->country_GetNumArmies() << " units on " << vectorOfAllCountries[i]->country_GetName() << "." << endl;
							cin >> numOfArmiesToMove;

							if(numOfArmiesToMove < 0) {
								cout << "Invalid entry. Please enter a number greater or equal to 0." << endl;
							}
							else if (numOfArmiesToMove == 0) {
								cout << "You have entered 0, therefore no armies were moved." << endl;
							}
							else if (numOfArmiesToMove >= vectorOfAllCountries[i]->country_GetNumArmies()) {
								cout << "Invalid entry. You must leave at least 1 army unit behind." << endl;
							}
							else {
								vectorOfAllCountries[i]->country_SetNumArmies(vectorOfAllCountries[i]->country_GetNumArmies() - numOfArmiesToMove);
								vectorOfAllCountries[j]->country_SetNumArmies(vectorOfAllCountries[j]->country_GetNumArmies() + numOfArmiesToMove);
								fortifyNumberFlag = true;
								cout << "Successfully sent " << numOfArmiesToMove << " army units from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName();
							}
						}
					}
				}
			}
		}
	}

}


void Player::addCountry(Country *currentCountry){
	collectionOfCountries.push_back(currentCountry);
}

void Player::removeCountry(Country *currentCountry){
	for(unsigned int x = 0; x < collectionOfCountries.size();x++){
		if(currentCountry->country_GetName() == collectionOfCountries[x]->country_GetName())
			collectionOfCountries.erase(collectionOfCountries.begin() + x);
	}
}

int Player::exchange(Map *currentMap) {
	int infantry = 0;
	int cav = 0;
	int art = 0;

	cout << "number of cards: " << myHand.getNumberOfCards() << endl;
	for (int i = 0; i < myHand.getNumberOfCards(); i++) {
		if (myHand.getHandOfCards()[i]->getType() == INFANTRY) {
			infantry++;
		}
		if (myHand.getHandOfCards()[i]->getType() == ARTILLERY) {
			art++;
		}
		if (myHand.getHandOfCards()[i]->getType() == CAVALRY) {

			cav++;

		}
	}

	cout << "My hand has: " << endl << endl;

	cout << "Infantry: " << infantry << endl;
	cout << "Artillery: " << art << endl;
	cout << "Cavalry: " << cav << endl;

	if (infantry >= 3) {
		int count = 0;
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == INFANTRY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				infantry = infantry - 1;
				count++;
				if (count == 3) {

					break;

				}
			}

		}
		currentMap->setsTraded++;
		return 5 * currentMap->setsTraded;
	}

	if (cav >= 3) {
		int count = 0;
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == CAVALRY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				cav = cav - 1;
				count++;
				if (count == 3) {

					break;

				}
			}

		}
		currentMap->setsTraded++;
		return 5 * currentMap->setsTraded;
	}

	if (art >= 3) {
		int count = 0;
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == ARTILLERY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				art = art - 1;
				count++;
				if (count == 3) {

					break;

				}
			}

		}
		currentMap->setsTraded++;
		return 5 * currentMap->setsTraded;
	}

	if (art >= 1 && cav >= 1 && infantry >= 1) {

		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == ARTILLERY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				art = art - 1;
				break;
			}

		}
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == CAVALRY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				cav = cav - 1;
				break;
			}

		}
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {

			if (myHand.getHandOfCards()[i]->getType() == INFANTRY) {

				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				infantry = infantry - 1;
				break;
			}

		}
		currentMap->setsTraded++;
		return 5 * currentMap->setsTraded;
	}
}


