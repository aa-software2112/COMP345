/*
 * Player.cpp
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */
#include <iostream>
#include "Player.h"
#include "RiskGame.h"
#include "Continent.h"
#include "DiceRollingFacility.h"


ostream& operator<<(ostream& output, Player& p)
{
	/** TODO: Should add number of armies to be displayed */
	output << "Player: " << p.myName << endl;
	return output;

}

set<Continent *> * Player::player_getUniqueContinents(void)
{
	/** Set of continents */
	set<Continent *> * uniqueContinents = new set<Continent *>;

	/** Iterate over all countries */
	for(vector<Country*>::iterator it = myCollectionOfCountries.begin(); it<myCollectionOfCountries.end(); it++)
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
	myName = newName;
}

/* Getter function for the player's name */
string Player::player_getPlayerName() {
	return this->myName;
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
	return this->myCollectionOfCountries;
}

bool Player::player_checkCountryOwnership(Country* currentCountry)
{
	bool playerOwnsThisCountry = false;

	for(unsigned int i = 0; i < this->myCollectionOfCountries.size(); i++)
	{
		if(this->myCollectionOfCountries[i] == currentCountry)
			playerOwnsThisCountry = true;
	}

	return playerOwnsThisCountry;
}

/* Getter function for the sum of player's armies */
unsigned int Player::player_getTotalNumberArmies(void)
{
	int totalNumArmies = 0;

	for(unsigned int i = 0; i < this->myCollectionOfCountries.size(); i++)
	{
		totalNumArmies = this->myCollectionOfCountries[i]->country_GetNumArmies() + totalNumArmies;
	}

	return totalNumArmies;

}


/* reinforce();
 * The function current requires a Map* parameter because we stored a member called setsTraded inside of the Map Class
 * that will hold the global amount of card sets traded in. This member will eventually be moved to another class such as
 * Game, or anywhere else more appropriate later on.
 */
void Player::player_reinforce(RiskGame* currentGame){
	cout << "REINFORCEMENT PHASE:" << endl;

	cout << "Reinforcement Start" << endl;

	/* Temporarily giving players cards */

	/*
	myHand.addCardToHand(currentGame->riskGame_getDeck()->deck_getDeck()[0]);
	myHand.addCardToHand(currentGame->riskGame_getDeck()->deck_getDeck()[1]);
	myHand.addCardToHand(currentGame->riskGame_getDeck()->deck_getDeck()[2]);
	myHand.addCardToHand(currentGame->riskGame_getDeck()->deck_getDeck()[3]);
	myHand.addCardToHand(currentGame->riskGame_getDeck()->deck_getDeck()[4]);
	*/

	/* Display player's hand */
	cout << endl;
	cout << "Current Hand:" << endl;

	for(unsigned int w = 0; w < myHand.hand_getHandOfCards().size();w++) {
		myHand.hand_getHandOfCards()[w]->card_printType();
	}

	cout << endl;

	/* Calculating the base amount of new armies at the start of the turn */
	int newArmiesCount = myCollectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* Put of all the unique continents where the player owns at least 1 country on into a vector */
	set<Continent *> setOfUniqueContinents = *this->player_getUniqueContinents();

	for(set<Continent *>::iterator it = setOfUniqueContinents.begin(); it != setOfUniqueContinents.end(); it++)
	{
		/* If this condition is true, that means player owns the current iterated continent */
		if((*(*it)).continent_playerOwnsContinent(this)) {
			int continentBonus = (*(*it)).continent_getBonusValue();	// get the bonus value from the respective continent object
			string continentName = (*(*it)).continent_GetContinentName();
			cout << "Reinforcement Army Bonus! " << continentBonus << " additional army units for completely controlling a continent - " << continentName << "." << endl;
			newArmiesCount = newArmiesCount + continentBonus;	// increment the player's new army count by the continent bonus
		}
	}

	cout << endl;

	/* If player's hand has 5 or more cards, they MUST exchange for armies */
	while(myHand.hand_getHandOfCards().size() > 4) {
		cout << "Forced Exchange Phase:" << endl;
		cout << "You have at least 5 cards in your hand, therefore you must trade in a set." << endl;
		newArmiesCount = newArmiesCount + this->player_getMyHand()->hand_exchange(currentGame); // exchange(currentMap) will modify the hand of the player, thus decrementing their hand size

	}

	cout << endl;


	bool exchangePhaseDoneFlag = false;	// flag used to keep exchanging until a player wishes not to

	while(!exchangePhaseDoneFlag)
	{
		cout << "Optional Exchange Phase:" << endl;

		/* Prompt the user whether he wants to exchange cards or not */
		string exchangeMessage = "Would you like to exchange a set of cards?\nEnter 0, for no\nEnter 1, for yes\nEnter 2, to see your personal board\nEnter 3 to see the global board";
		int exchangeAnswer = UserInterface::userInterface_getIntegerBetweenRange(exchangeMessage, 0, 3);

		if(exchangeAnswer == 1)
		{
			newArmiesCount = newArmiesCount + this->player_getMyHand()->hand_exchange(currentGame);
		}
		else if(exchangeAnswer == 2)
		{
			currentGame->riskGame_showStateOfPlayer(this);	// show player's board
		}
		else if(exchangeAnswer == 3)
		{
			currentGame->riskGame_showStateOfGame(); // show the whole board
		}
		else
		{
			exchangePhaseDoneFlag = true;
		}
	}

	/* This loop will run as long as the player did not place all their additional reinforcement units */
	while(newArmiesCount != 0){
		cout << "List of my countries:" << endl << endl;

		/* Display the whole board */
		currentGame->riskGame_showStateOfGame();

		/* Printing out the player's collection of countries with their respective index in the player's collection */
		currentGame->riskGame_showStateOfPlayer(this);

		/* Prompt the player to enter the index of the country they would like to reinforce */

		string newArmyLocationMessage = "Where would you like place your new army unit(s)? (" + std::to_string(newArmiesCount) + " left) Enter the country index.";
		int newArmyLocationIndex = UserInterface::userInterface_getIntegerBetweenRange(newArmyLocationMessage, 0, myCollectionOfCountries.size());

		/* Prompt the player to enter the number of units they would like to place on this country */
		string newArmyAmountMessage = "How many army unit(s) would you like to place here? (" + std::to_string(newArmiesCount) + " unit(s) left!)";
		int newArmyAmountPlaced = UserInterface::userInterface_getIntegerBetweenRange(newArmyAmountMessage, 0, newArmiesCount);

		/* Add the armies to the appropriate country */
		myCollectionOfCountries[newArmyLocationIndex]->country_SetNumArmies(myCollectionOfCountries[newArmyLocationIndex]->country_GetNumArmies() + newArmyAmountPlaced);

		/* Decrement the number of new armies available*/
		newArmiesCount = newArmiesCount - newArmyAmountPlaced;
	}
	cout << endl;
	cout << "Reinforcement End" << endl << endl;
}

/* attack();
 * The player's attack() function
 */
void Player::player_attack(RiskGame* currentGame){

	cout << "ATTACK PHASE" << endl;
	cout << "Attack Start" << endl;


	bool attacking = true; // flag variable needed to conduct continuous attacks
	bool capturedCountry = false; // flag variable needed to check if a player captured at least 1 country during their whole attack phase

	while (attacking){
		cout << "Here are your possible attacks:" << endl << endl;

		/* This outer loop will go through the player's collection of countries */
		for (unsigned int x = 0; x < myCollectionOfCountries.size();x++) {
			/* Checking if the current country has at least 2 armies on them to perform an attack */
			if(myCollectionOfCountries[x]->country_GetNumArmies() >= 2){

				/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
				vector<Country *> vectorOfAdjacentCountries = currentGame->riskGame_getMap()->map_GetCountriesAdjacentTo(myCollectionOfCountries[x]);

				/* Loop through the adjacent countries */
				for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
					/* Check if the current country is an enemy country */
					if (vectorOfAdjacentCountries[y]->country_GetOwner() != this) {

						/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
						for(unsigned int a = 0; a < currentGame->riskGame_getMap()->map_GetAllCountries().size(); a++)
						{
							if(currentGame->riskGame_getMap()->map_GetAllCountries()[a] == myCollectionOfCountries[x])
							{
								/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
								for(unsigned int b = 0; b < currentGame->riskGame_getMap()->map_GetAllCountries().size(); b++)
								{
									if(currentGame->riskGame_getMap()->map_GetAllCountries()[b] == vectorOfAdjacentCountries[y]) {
										/* Print out a line confirming the possibility to perform this attack */
										cout << "[" << a << "] " << myCollectionOfCountries[x]->country_GetName() << " (" << myCollectionOfCountries[x]->country_GetNumArmies() << " units) may attack [" << b << "] "  << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
									}
								}
							}
						}
					}
				}
			}
		}

		cout << endl;

		/* Prompt the player if they want to perform an attack */

		string attackMessage = "Do you wish to attack? Enter 0 for no or 1 for yes.";
		int attackInput = UserInterface::userInterface_getIntegerBetweenRange(attackMessage, 0, 1);

		if(attackInput == 0){
			attacking = false;
		}
		else {
			int attackingCountryIndex;
			int defendingCountryIndex;

			/* Prompt the user for the attacking country index and the defending country index (did not implement error checking for this, there they must enter the appropriate indexes) */
			cout << "Which country do you wish to attack with? Enter its index." << endl;
			cin >> attackingCountryIndex;

			cout << "Which country do you wish to attack? Enter its index." << endl;
			cin >> defendingCountryIndex;

			/* Create a vector that will hold all countries in the game */
			vector<Country *> vectorOfAllCountries = currentGame->riskGame_getMap()->map_GetAllCountries();

			/* Print out the state of these countries */
			cout << endl;
			cout << "Attacking: " << vectorOfAllCountries[attackingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[attackingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[attackingCountryIndex]->country_GetOwner()->player_getPlayerName() << endl;
			cout << "Defending: " << vectorOfAllCountries[defendingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[defendingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[defendingCountryIndex]->country_GetOwner()->player_getPlayerName()  << endl;

			/* Preparing variables to perform the attacking process */

			Country* attackingCountry = vectorOfAllCountries[attackingCountryIndex];
			Country* defendingCountry = vectorOfAllCountries[defendingCountryIndex];
			int numOfDiceAttacker;
			int numOfDiceDefender;

			/* Prompting the attacking player how many dice they wish to roll */
			if(attackingCountry->country_GetNumArmies() == 2) {
				cout << endl;
				cout << "The attacker can only roll one die, as they only have two army units on the attacking country." << endl << endl;;
				numOfDiceAttacker = 1;
			}
			else {
				string attackDiceMessage = "Attacker, how many dice would you like to roll? Enter 1, 2 or 3. (REMINDER: " + std::to_string(attackingCountry->country_GetNumArmies()) + " units on your country)";
				numOfDiceAttacker = UserInterface::userInterface_getIntegerBetweenRange(attackDiceMessage, 1, 3);
			}

			/* Roll the appropriate number of dice in the attacking player's DiceRollingFacility object */
			attackingCountry->country_GetOwner()->myDRF.diceRollingFacility_rollDice(numOfDiceAttacker);

			/* Prompting the defending player how many dice they wish to roll */
			if(defendingCountry->country_GetNumArmies() == 1) {
				cout << endl;
				cout << "The defender can only roll one die, as they only have one army unit on the defending country." << endl << endl;;
				numOfDiceDefender = 1;
			}
			else {
				string defendDiceMessage = "Defender, how many dice would you like to roll? Enter 1, or 2. (REMINDER: " + std::to_string(defendingCountry->country_GetNumArmies()) + " units on your country)";

				numOfDiceDefender = UserInterface::userInterface_getIntegerBetweenRange(defendDiceMessage, 1, 2);

			}

			/* Roll the appropriate number of dice in the attacking player's DiceRollingFacility object */
			defendingCountry->country_GetOwner()->myDRF.diceRollingFacility_rollDice(numOfDiceDefender);

			/* Print out the dice rolling results */
			cout << endl;
			cout << "************************** DICE ROLL **************************" << endl << endl;
			cout << endl;
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
			/* This outer if/else if algorithm determines which code block to run depending on the number of dice rolled by the attacker and defender */
			if(numOfDiceAttacker == 1 && numOfDiceDefender == 1) {
				if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
					cout << "The attacker won the battle." << endl;
					cout << "The defender has no more units on their country." << endl;

					/* Note: Attacker's must leave behind at least 1 unit */
					cout << "Attacker, how many army units would you like to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << "? You can move up to " << attackingCountry->country_GetNumArmies() - 1 << " units." << endl;
					cin >> numOfArmiesToMove;

					defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
					defendingCountry->country_SetNumArmies(numOfArmiesToMove);
					cout << myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);
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

					/* Note: Attacker's must leave behind at least 1 unit */
					cout << "Attacker, how many army units would you like to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << "? You can move up to " << attackingCountry->country_GetNumArmies() - 1 << " units." << endl;
					cin >> numOfArmiesToMove;


					defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
					defendingCountry->country_SetNumArmies(numOfArmiesToMove);
					cout << myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);
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

					/* Note: Attacker's must leave behind at least 1 unit */
					cout << "Attacker, how many army units would you like to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << "? You can move up to " << attackingCountry->country_GetNumArmies() - 1 << " units." << endl;
					cin >> numOfArmiesToMove;

					defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
					defendingCountry->country_SetNumArmies(numOfArmiesToMove);
					cout << myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);
				}
			}
			else if(numOfDiceAttacker == 3 && numOfDiceDefender == 1) {
				if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
					cout << "The attacker won the battle." << endl;
					cout << "The defender has no more units on their country." << endl;

					/* Note: Attacker's must leave behind at least 1 unit */
					cout << "Attacker, how many army units would you like to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << "? You can move up to " << attackingCountry->country_GetNumArmies() - 1 << " units." << endl;
					cin >> numOfArmiesToMove;

					defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
					defendingCountry->country_SetNumArmies(numOfArmiesToMove);
					cout << myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);
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

					/* Note: Attacker's must leave behind at least 1 unit */
					cout << "Attacker, how many army units would you like to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << "? You can move up to " << attackingCountry->country_GetNumArmies() - 1 << " units." << endl;
					cin >> numOfArmiesToMove;

					defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
					defendingCountry->country_SetNumArmies(numOfArmiesToMove);
					cout << myName << " now owns " << defendingCountry->country_GetName() << "." << endl << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);
				}
			}
		}
	}

	/* Draw if a country was captured during the attack phase */
	if(capturedCountry)
		this->player_getMyHand()->hand_addCardToHand(currentGame->riskGame_getDeck()->deck_draw());

	cout << endl;
	cout << "Attack End" << endl << endl;
}

/* fortify();
 * The player's fortify function
 */
void Player::player_fortify(RiskGame* currentGame){

	cout << "FORTIFICATION PHASE" << endl;
	cout << "Fortification Start" << endl << endl;

	cout << "Here are your possible fortifications:" << endl;

	/* This outer loop will go through the player's collection of countries */
	for (unsigned int x = 0; x < myCollectionOfCountries.size();x++) {
		/* Checking if the current country has at least 2 armies on them to perform a fortify, needs to at least leave 1 army behind */
		if(myCollectionOfCountries[x]->country_GetNumArmies() >= 2){
			/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
			vector<Country *> vectorOfAdjacentCountries = currentGame->riskGame_getMap()->map_GetCountriesAdjacentTo(myCollectionOfCountries[x]);
			/* Loop through the adjacent countries */
			for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
				/* Check if the current country is an ally country */
				if (vectorOfAdjacentCountries[y]->country_GetOwner() == this) {
					/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
					for(unsigned int a = 0; a < currentGame->riskGame_getMap()->map_GetAllCountries().size(); a++)
					{
						if(currentGame->riskGame_getMap()->map_GetAllCountries()[a] == myCollectionOfCountries[x])
						{
							/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
							for(unsigned int b = 0; b < currentGame->riskGame_getMap()->map_GetAllCountries().size(); b++)
							{
								if(currentGame->riskGame_getMap()->map_GetAllCountries()[b] == vectorOfAdjacentCountries[y]) {
									/* Print out a line confirming the possibility to perform this fortify */
									cout << "[" << a << "] " << myCollectionOfCountries[x]->country_GetName() << " (" << myCollectionOfCountries[x]->country_GetNumArmies() << " units) may fortify [" << b << "] " << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
								}
							}
						}
					}
				}
			}
		}
	}

	cout << endl;

	/* Prompt the user if they wish to perform a fortification*/

	string fortifyMessage = "Do you wish to fortify? Enter 0 for no or 1 for yes.";
	int fortifyInput = UserInterface::userInterface_getIntegerBetweenRange(fortifyMessage, 0, 1);

	if(fortifyInput == 1){
		int fromCountry;
		int toCountry;

		/* Prompt the player to enter the index of the attack country then the index of the defending country (did not implement error checking for this, there they must enter the appropriate indexes) */
		cout << "Which country do you wish to fortify from?" << endl;
		cin >> fromCountry;

		cout << "Which country do you wish to fortify to?" << endl;
		cin >> toCountry;

		/* Creating a vector that holds all the countries on a map */
		vector<Country *> vectorOfAllCountries = currentGame->riskGame_getMap()->map_GetAllCountries();


		/* PERSONAL NOTE: this whole section should be able to be redone using the UI class */
		bool fortifyNumberFlag = false;

		while (!fortifyNumberFlag) {
			int numOfArmiesToMove = 0;
			cout << "How many army units would you like to move? (There are " << vectorOfAllCountries[fromCountry]->country_GetNumArmies() << " units on " << vectorOfAllCountries[fromCountry]->country_GetName() << ")" << endl;
			cin >> numOfArmiesToMove;

			if(numOfArmiesToMove < 0) {
				cout << "Invalid entry. Please enter a number greater or equal to 0." << endl;
			}
			else if (numOfArmiesToMove == 0) {
				cout << "You have entered 0, therefore no armies were moved." << endl;
			}
			else if (numOfArmiesToMove >= vectorOfAllCountries[fromCountry]->country_GetNumArmies()) {
				cout << "Invalid entry. You must leave at least 1 army unit behind." << endl;
			}
			else {
				vectorOfAllCountries[fromCountry]->country_SetNumArmies(vectorOfAllCountries[fromCountry]->country_GetNumArmies() - numOfArmiesToMove);
				vectorOfAllCountries[toCountry]->country_SetNumArmies(vectorOfAllCountries[toCountry]->country_GetNumArmies() + numOfArmiesToMove);
				fortifyNumberFlag = true;
				cout << "Successfully sent " << numOfArmiesToMove << " army units from " << vectorOfAllCountries[fromCountry]->country_GetName() << " to " << vectorOfAllCountries[toCountry]->country_GetName();
			}
		}
	}
	cout << endl;
	cout << "Fortification End" << endl << endl;
}

/* Function that adds a country to a player's collection of countries */
void Player::player_addCountry(Country *currentCountry){
	myCollectionOfCountries.push_back(currentCountry);
	currentCountry->country_SetOwner(this);
}

/* Function that removes a country from a player's collection of countries */
void Player::player_removeCountry(Country *currentCountry){
	for(unsigned int x = 0; x < myCollectionOfCountries.size();x++){
		if(currentCountry == myCollectionOfCountries[x])
			myCollectionOfCountries.erase(myCollectionOfCountries.begin() + x);
	}
}


