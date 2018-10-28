/*
 * Player.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */
#include <iostream>
#include "Player.h"

ostream& operator<<(ostream& output, Player& p)
{
	/** TODO: Should add number of armies to be displayed */
	output << "Player: " << p.playerName << endl;
	return output;

}

set<Continent *> * Player::player_getUniqueContinents(void)
{
	/** Set of continents */
	set<Continent *> * uniqueContinents = new set<Continent *>;

	/** Iterate over all countries */
	for(vector<Country*>::iterator it = collectionOfCountries.begin(); it<collectionOfCountries.end(); it++)
	{
		Country *c = *it;

		/** Keeps adding to the set */
		uniqueContinents->insert(c->country_GetContinent());

	}

	return uniqueContinents;
}


/* Default constructor */
Player::Player(){
}

/* Constructor that sets an initial player name */
Player::Player(string newName){
	playerName = newName;
}

/* Getter function for the player's name */
string Player::player_getPlayerName() {
	return this->playerName;
}

/* Getter function for the player's DiceRollingFacility object */
DiceRollingFacility* Player::player_getMyDRF() {
	return &myDRF;
}

/* Getter function for the player's Hand object */
Hand* Player::player_getMyHand() {
	return &myHand;
}

/* Getter function for the player's collection of countries (vector of country object references) */
std::vector<Country*> Player::player_getMyCountries() {
	return this->collectionOfCountries;
}

int Player::player_getTotalNumberArmies(void)
{

	int totalNumArmies = 0;

	for(vector<Country*>::iterator it = this->collectionOfCountries.begin(); it < this->collectionOfCountries.end(); it++)
	{
		totalNumArmies += (*(*it)).country_GetNumArmies();
	}

	return totalNumArmies;

}


/* reinforce();
 * The function current requires a Map* parameter because we stored a member called setsTraded inside of the Map Class
 * that will hold the global amount of card sets traded in. This member will eventually be moved to another class such as
 * Game, or anywhere else more appropriate later on.
 */
void Player::reinforce(Map* currentMap){
	cout << "Reinforcing" << endl;

	/* Display player's hand */

	cout << "My current hand:" << endl;
	cout << endl;

	for(unsigned int w = 0; w < myHand.getHandOfCards().size();w++) {
		myHand.getHandOfCards()[w]->printType();
	}

	cout << endl;

	/* Calculating the amount of new armies at the start of the turn */
	int newArmiesCount = collectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* STILL NEED TO IMPLEMENT FUNCTION THAT CHECKS IF PLAYER CONTROLS A FULL CONTINENT */

	/*
	 *
	 *
	 *
	 *	RESERVED
	 *
	 *
	 */

	bool controlsFullContinent = false;

	/* Bonus armies if player controls a whole continent */
	if(controlsFullContinent) {

		/* Temporary example, may completely be scratched for a different implementation */
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

	/* If player's hand has 5 or more cards, they MUST exchange for armies */
	while(myHand.getHandOfCards().size() > 5) {
		newArmiesCount = newArmiesCount + exchange(currentMap); // exchange(currentMap) will modify the hand of the player, thus decrementing their hand size
	}

	/* If the player's hand is 5 or lower, prompt them if they want to exchange cards. */
	cout << "Would you like to trade in a set of cards? Enter 0 for no or 1 for yes." << endl;

	int exchangeCardsInput;
	cin >> exchangeCardsInput;

	if(exchangeCardsInput == 1) {
		newArmiesCount = newArmiesCount + exchange(currentMap);
	}

	/* Display all countries owned by player */

	unsigned int countryIndex; // this will hold the index of the country in the player's hand that they wish to reinforce
	int numOfArmiesPlaced; // this will hold the number of army units the player wants to place on a country

	/* This loop will run as long as the player did not place all their additional reinforcement units */
	while(newArmiesCount != 0){
		cout << "List of my countries:" << endl << endl;

		/* Printing out the player's collection of countries with their respective index in the player's hand */
		for(unsigned int x = 0; x < collectionOfCountries.size(); x++){
			cout << "[" << x << "] " << *collectionOfCountries[x] << endl;
		}

		/* Prompt the player the enter the index of the country they would like to reinforce */
		bool validIndex = false;
		while (!validIndex) {
			cout << "Where would you like place your new army unit(s)? Enter the country index." << endl;
			cin >> countryIndex;

			if(countryIndex < 0 || countryIndex >= collectionOfCountries.size()){
				cout << "Index value out of range! Please select a valid index." << endl;
			}
			else {
				validIndex = true;
			}
		}

		/* Prompt the player the enter the index of the country they would like to reinforce */
		bool validNumOfArmies = false;
		while (!validNumOfArmies) {
			cout << "How many army unit(s) would you like to place here?" << " (" << newArmiesCount << " unit(s) left!)" << endl;
			cin >> numOfArmiesPlaced;
			if(numOfArmiesPlaced > newArmiesCount){
				cout << "You do not have enough army units left! Please enter a valid number." << endl;
			}
			else {
				validNumOfArmies = true;
			}
		}

		/* Add the armies to the appropriate country */
		collectionOfCountries[countryIndex]->country_SetNumArmies(collectionOfCountries[countryIndex]->country_GetNumArmies() + numOfArmiesPlaced);

		/* Decrement the number of new armies available*/
		newArmiesCount = newArmiesCount - numOfArmiesPlaced;
	}
}

/* attack();
 * The player's attack() function
 */
void Player::attack(Map *currentMap){

	bool attacking = true; // flag variable needed to conduct continuous attacks

	while (attacking){
		cout << "Attacking" << endl;

		cout << "List of possible attacks:" << endl << endl;

		/* This outer loop will go through the player's collection of countries */
		for (unsigned int x = 0; x < collectionOfCountries.size();x++) {
			/* Checking if the current country has at least 2 armies on them to perform an attack */
			if(collectionOfCountries[x]->country_GetNumArmies() >= 2){

				/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
				vector<Country *> vectorOfAdjacentCountries = currentMap->map_GetCountriesAdjacentTo(collectionOfCountries[x]);

				/* Loop through the adjacent countries */
				for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
					/* Check if the current country is an enemy country */
					if (vectorOfAdjacentCountries[y]->country_GetOwner() != this) {
						/* Print out a line confirming the possibility to perform this attack */
						cout << collectionOfCountries[x]->country_GetName() << " (" << collectionOfCountries[x]->country_GetNumArmies() << " units) may attack " << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
					}
				}
			}
		}

		cout << endl;

		/* Prompt the player if they want to perform an attack */
		int attackInput = 0;
		cout << "Do you wish to attack? Enter 0 for no or 1 for yes." << endl;
		cin >> attackInput;

		if(attackInput == 0){
			attacking = false;
		}
		else {
			string nameOfAttackingCountry = "";
			string nameOfDefendingCountry = "";

			/* Prompt the player to enter the name of the attack country then the name of the defending country (did not implement error checking, therefore the strings must be enter appropriately */

			cout << "Which country do you wish to attack with?" << endl;
			cin >> nameOfAttackingCountry;

			cout << "Which country do you wish to attack?" << endl;
			cin >> nameOfDefendingCountry;

			/* Create a vector that will hold all countries in the game */
			vector<Country *> vectorOfAllCountries = currentMap->map_GetAllCountries();

			/* Loop through all the countries in the vector */
			for(unsigned int i = 0; i < vectorOfAllCountries.size();i++) {
				/* Find the attacking country (index i) */
				if(nameOfAttackingCountry == vectorOfAllCountries[i]->country_GetName()) {
					/* Loop through all the countries in the vector again */
					for(unsigned int j = 0; j < vectorOfAllCountries.size();j++) {
						/* Find the defending country (index j) */
						if(nameOfDefendingCountry == vectorOfAllCountries[j]->country_GetName()) {

							/* Print out the state of these countries */
							cout << endl;
							cout << "Attacking: " << nameOfAttackingCountry << " has " << vectorOfAllCountries[i]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[i]->country_GetOwner()->player_getPlayerName() << endl;
							cout << "Defending: " << nameOfDefendingCountry << " has " << vectorOfAllCountries[j]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[j]->country_GetOwner()->player_getPlayerName()  << endl;

							/* Preparing variables to perform the attacking process */

							Country* attackingCountry = vectorOfAllCountries[i];
							Country* defendingCountry = vectorOfAllCountries[j];
							int numOfDiceAttacker;
							int numOfDiceDefender;

							/* Prompting the attacking player how many dice they wish to roll */
							if(attackingCountry->country_GetNumArmies() == 2) {
								cout << "The attacker can only roll one die, as they only have two army units on the attacking country." << endl;
								numOfDiceAttacker = 1;
							}
							else {
								bool attackerDiceNumFlag = false;

								while (!attackerDiceNumFlag){
									cout << "Attacker, how many dice would you like to roll? Enter 1, 2 or 3. (REMINDER: " << attackingCountry->country_GetNumArmies() << " units on your country)" << endl;
									cin >> numOfDiceAttacker;

									if (numOfDiceAttacker < 1 || numOfDiceAttacker > 3) {
										cout << "Invalid. Please entry a valid dice number. (1-3)" << endl;
									}
									else {
										attackerDiceNumFlag = true;
									}
								}
							}

							/* Roll the appropriate number of dice in the attacking player's DiceRollingFacility object */
							attackingCountry->country_GetOwner()->myDRF.rollDice(numOfDiceAttacker);

							/* Prompting the defending player how many dice they wish to roll */
							if(defendingCountry->country_GetNumArmies() == 1) {
								cout << "The defender can only roll one die, as they only have one army unit on the defending country." << endl;
								numOfDiceDefender = 1;
							}
							else {
								bool defenderDiceNumFlag = false;

								while (!defenderDiceNumFlag){
									cout << "Defender, how many dice would you like to roll? Enter 1 or 2. (REMINDER: " << defendingCountry->country_GetNumArmies() << " units on your country)" << endl;
									cin >> numOfDiceDefender;

									if (numOfDiceDefender < 1 || numOfDiceDefender > 2) {
										cout << "Invalid. Please entry a valid dice number. (1-2)" << endl;
									}
									else {
										defenderDiceNumFlag = true;
									}
								}
							}
							/* Roll the appropriate number of dice in the attacking player's DiceRollingFacility object */
							defendingCountry->country_GetOwner()->myDRF.rollDice(numOfDiceDefender);

							/* Print out the dice rolling results */
							cout << "************************** DICE ROLL **************************" << endl << endl;
							cout << "Attacker rolled " << numOfDiceAttacker << " die/dice." << endl;
							cout << "Defender rolled " << numOfDiceDefender << " die/dice." << endl;

							cout << endl;

							cout << "Attacker's dice: " << endl;
							cout << attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] << endl;
							cout << attackingCountry->country_GetOwner()->myDRF.resultsRolled[1] << endl;
							cout << attackingCountry->country_GetOwner()->myDRF.resultsRolled[2] << endl;

							cout << endl;

							cout << "Defender's dice: " << endl;
							cout << defendingCountry->country_GetOwner()->myDRF.resultsRolled[0] << endl;
							cout << defendingCountry->country_GetOwner()->myDRF.resultsRolled[1] << endl;
							cout << defendingCountry->country_GetOwner()->myDRF.resultsRolled[2] << endl;


							int numOfArmiesToMove = 0; // This will hold the number of armies to move if the attacker captures a country */

							/* Logic block behind attacking from one country to another */
							if(numOfDiceAttacker == 1 && numOfDiceDefender == 1) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the battle." << endl;
									cout << "The defender has no more units on their country." << endl;
									cout << "Attacker, how many army units would you like to move from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName() << "? You can move up to " << vectorOfAllCountries[i]->country_GetNumArmies() - 1 << " units." << endl;
									cin >> numOfArmiesToMove;
									defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
									defendingCountry->country_SetNumArmies(numOfArmiesToMove);
									cout << playerName << " now owns " << defendingCountry->country_GetName() << "." << endl;
								}
								else {
									cout << "The defender won the battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}
							}
							else if(numOfDiceAttacker == 1 && numOfDiceDefender == 2) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the battle." << endl;
									defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
								}
								else {
									cout << "The defender won the battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}
							}
							else if(numOfDiceAttacker == 2 && numOfDiceDefender == 1) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the battle." << endl;
									cout << "The defender has no more units on their country." << endl;
									cout << "Attacker, how many army units would you like to move from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName() << "? You can move up to " << vectorOfAllCountries[i]->country_GetNumArmies() - 1 << " units." << endl;
									cin >> numOfArmiesToMove;
									defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
									defendingCountry->country_SetNumArmies(numOfArmiesToMove);
									cout << playerName << " now owns " << defendingCountry->country_GetName() << "." << endl;
								}
								else {
									cout << "The defender won the battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}
							}
							else if (numOfDiceAttacker == 2 && numOfDiceDefender == 2) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the first battle." << endl;
									defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
								}
								else {
									cout << "The defender won the first battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}

								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[1] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[1]) {
									cout << "The attacker won the second battle." << endl;
									defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
								}
								else {
									cout << "The defender won the second battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}

								if(defendingCountry->country_GetNumArmies() == 0) {
									cout << "The defender has no more units on their country." << endl;
									cout << "Attacker, how many army units would you like to move from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName() << "? You can move up to " << vectorOfAllCountries[i]->country_GetNumArmies() - 1 << " units." << endl;
									cin >> numOfArmiesToMove;
									defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
									defendingCountry->country_SetNumArmies(numOfArmiesToMove);
									cout << playerName << " now owns " << defendingCountry->country_GetName() << "." << endl;
								}
							}
							else if(numOfDiceAttacker == 3 && numOfDiceDefender == 1) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the battle." << endl;
									cout << "The defender has no more units on their country." << endl;
									cout << "Attacker, how many army units would you like to move from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName() << "? You can move up to " << vectorOfAllCountries[i]->country_GetNumArmies() - 1 << " units." << endl;
									cin >> numOfArmiesToMove;
									defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
									defendingCountry->country_SetNumArmies(numOfArmiesToMove);
									cout << playerName << " now owns " << defendingCountry->country_GetName() << "." << endl;
								}
								else {
									cout << "The defender won the battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}
							}
							else if (numOfDiceAttacker == 3 && numOfDiceDefender == 2) {
								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
									cout << "The attacker won the first battle." << endl;
									defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
								}
								else {
									cout << "The defender won the first battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}

								if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[1] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[1]){
									cout << "The attacker won the second battle." << endl;
									defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
								}
								else {
									cout << "The defender won the second battle." << endl;
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
								}

								if(defendingCountry->country_GetNumArmies() == 0) {
									cout << "The defender has no more units on their country." << endl;
									cout << "Attacker, how many army units would you like to move from " << vectorOfAllCountries[i]->country_GetName() << " to " << vectorOfAllCountries[j]->country_GetName() << "? You can move up to " << vectorOfAllCountries[i]->country_GetNumArmies() - 1 << " units." << endl;
									cin >> numOfArmiesToMove;
									defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
									attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
									defendingCountry->country_SetNumArmies(numOfArmiesToMove);
									cout << playerName << " now owns " << defendingCountry->country_GetName() << "." << endl << endl;
								}
							}
						}
					}
				}
			}
		}
	}
}

/* fortify();
 * The player's fortify function
 */
void Player::fortify(Map *currentMap){

	cout << "Fortifying" << endl;

	cout << "List of my countries:" << endl << endl;

	/* This outer loop will go through the player's collection of countries */
	for (unsigned int x = 0; x < collectionOfCountries.size();x++) {
		/* Checking if the current country has at least 2 armies on them to perform a fortify, needs to at least leave 1 army behind */
		if(collectionOfCountries[x]->country_GetNumArmies() >= 2){
			/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
			vector<Country *> vectorOfAdjacentCountries = currentMap->map_GetCountriesAdjacentTo(collectionOfCountries[x]);
			/* Loop through the adjacent countries */
			for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
				/* Check if the current country is an ally country */
				if (vectorOfAdjacentCountries[y]->country_GetOwner() == this) {
					/* Print out a line confirming the possibility to perform this fortify */
					cout << collectionOfCountries[x]->country_GetName() << " (" << collectionOfCountries[x]->country_GetNumArmies() << " units) may fortify " << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
				}
			}
		}
	}

	/* Prompt the user if they wish to perform a fortification*/
	int fortifyInput = 0;
	cout << endl;
	cout << "Do you wish to fortify? Enter 0 for no and 1 for yes." << endl;
	cin >> fortifyInput;

	if(fortifyInput == 1){
		string fromCountry = "";
		string toCountry = "";

		/* Prompt the player to enter the name of the attack country then the name of the defending country (did not implement error checking, therefore the strings must be enter appropriately */
		cout << "Which country do you wish to fortify from?" << endl;
		cin >> fromCountry;

		cout << "Which country do you wish to fortify to?" << endl;
		cin >> toCountry;

		/* Creating a vector that holds all the countries on a map */
		vector<Country *> vectorOfAllCountries = currentMap->map_GetAllCountries();

		/* Loop through all the countries in the vector */
		for(unsigned int i = 0; i < vectorOfAllCountries.size();i++) {
			/* Find the first country (index i) */
			if(fromCountry == vectorOfAllCountries[i]->country_GetName()) {
				/* Loop through all the countries in the vector again */
				for(unsigned int j = 0; j < vectorOfAllCountries.size();j++) {
					/* Find the second country (index j) */
					if(toCountry == vectorOfAllCountries[j]->country_GetName()) {

						bool fortifyNumberFlag = false;

						while (!fortifyNumberFlag) {

							int numOfArmiesToMove = 0;
							cout << "How many army units would you like to move? (There are " << vectorOfAllCountries[i]->country_GetNumArmies() << " units on " << vectorOfAllCountries[i]->country_GetName() << ")" << endl;
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

/* Function that adds a country to a player's collection of countries */
void Player::addCountry(Country *currentCountry){
	collectionOfCountries.push_back(currentCountry);
}

/* Function that removes a country from a player's collection of countries */
void Player::removeCountry(Country *currentCountry){
	for(unsigned int x = 0; x < collectionOfCountries.size();x++){
		if(currentCountry->country_GetName() == collectionOfCountries[x]->country_GetName())
			collectionOfCountries.erase(collectionOfCountries.begin() + x);
	}
}

/* ********************* Daniel's exchange algorithm ********************* */
int Player::exchange(Map *currentMap) {

	/* Display player's hand */

	cout << "My current hand:" << endl;
	cout << endl;

	for(int w = 0; w < myHand.getHandOfCards().size();w++) {
		myHand.getHandOfCards()[w]->printType();
	}

	/* Initialize variables to count the number of each card type in a player's hand */
	int infantry = 0;
	int cav = 0;
	int art = 0;

	/* Counting the number of each card type in a player's hand */
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

	/* If there are at least 3 infantry cards */
	if (infantry >= 3) {
		int count = 0; // counter used to count to 3 cards to exchange
		/* Loop through the player's hand */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			/* Find the infantry cards in the player's hand */
			if (myHand.getHandOfCards()[i]->getType() == INFANTRY) {
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]); // removing the card from the player's hand
				infantry = infantry - 1;
				count++;
				if (count == 3)
					break;
			}
		}
		currentMap->setsTraded++; // increment the global amount of sets traded
		cout << "Successfully traded cards for " << 5 * currentMap->setsTraded << " units!" << endl;
		return 5 * currentMap->setsTraded; // return 5 * the global number of sets traded
	}

	/* If there are at least 3 Cavalry cards */
	if (cav >= 3) {
		int count = 0; // counter used to count to 3 cards to exchange
		/* Loop through the player's hand */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			/* Find the Cavalry cards in the player's hand */
			if (myHand.getHandOfCards()[i]->getType() == CAVALRY) {
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]); // removing the card from the player's hand
				cav = cav - 1;
				count++;
				if (count == 3)
					break;
			}
		}
		currentMap->setsTraded++; // increment the global amount of sets traded
		cout << "Successfully traded cards for " << 5 * currentMap->setsTraded << " units!" << endl;
		return 5 * currentMap->setsTraded; // return 5 * the global number of sets traded
	}

	/* If there are at least 3 Artillery cards */
	if (art >= 3) {
		int count = 0; // counter used to count to 3 cards to exchange
		/* Loop through the player's hand */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			/* Find the Artillery cards in the player's hand */
			if (myHand.getHandOfCards()[i]->getType() == ARTILLERY) {
				/* Find the Artillery cards in the player's hand */
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]); // removing the card from the player's hand
				art = art - 1;
				count++;
				if (count == 3)
					break;
			}
		}
		currentMap->setsTraded++; // increment the global amount of sets traded
		cout << "Successfully traded cards for " << 5 * currentMap->setsTraded << " units!" << endl;
		return 5 * currentMap->setsTraded; // return 5 * the global number of sets traded
	}
	/* If there are at least 1 of each type of card */
	if (art >= 1 && cav >= 1 && infantry >= 1) {
		/* Remove the first Artillery card */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			if (myHand.getHandOfCards()[i]->getType() == ARTILLERY) {
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				art = art - 1;
				break;
			}
		}
		/* Remove the first Cavalry card */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			if (myHand.getHandOfCards()[i]->getType() == CAVALRY) {
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				cav = cav - 1;
				break;
			}
		}
		/* Remove the first Infantry card */
		for (int i = 0; i < myHand.getNumberOfCards(); i++) {
			if (myHand.getHandOfCards()[i]->getType() == INFANTRY) {
				myHand.removeCardFromHand(myHand.getHandOfCards()[i]);
				infantry = infantry - 1;
				break;
			}
		}
		currentMap->setsTraded++; // increment the global amount of sets traded
		cout << "Successfully traded cards for " << 5 * currentMap->setsTraded << " units!" << endl;
		return 5 * currentMap->setsTraded; // return 5 * the global number of sets traded
	}
	return 0;
}

