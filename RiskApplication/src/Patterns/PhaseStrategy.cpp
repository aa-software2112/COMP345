
#define PHASE_STRATEGY_LOCAL
#include "PhaseStrategy.h"
#include "Player.h"
#include "RiskGame.h"
#include "GameStatisticsObserver.h"


/** Implement the following functions for Random attacks,
 * reinforcements and fortifications
 * */
void RandomPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	return;
}

void RandomPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	return;
}

void RandomPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	return;
}

/** Implement the following functions for Cheater attacks,
 * reinforcements and fortifications
 * */
void CheaterPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	return;
}

void CheaterPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	return;
}

void CheaterPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	return;
}


/** Implement the following functions for Human attacks,
 * reinforcements and fortifications
 * */
void HumanPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	cout << "- HUMAN STRATEGY -" << endl;
	cout << "ATTACK PHASE" << endl;
	cout << "Attack Start" << endl;


	bool attacking = true; // flag variable needed to conduct continuous attacks
	bool capturedCountry = false; // flag variable needed to check if a player captured at least 1 country during their whole attack phase

	while (attacking){
		cout << "Here are your possible attacks:" << endl << endl;

		/* This outer loop will go through the player's collection of countries */
		for (unsigned int x = 0; x < p->myCollectionOfCountries.size();x++) {
			/* Checking if the current country has at least 2 armies on them to perform an attack */
			if(p->myCollectionOfCountries[x]->country_GetNumArmies() >= 2){

				/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
				vector<Country *> vectorOfAdjacentCountries = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->myCollectionOfCountries[x]);

				/* Loop through the adjacent countries */
				for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
					/* Check if the current country is an enemy country */
					if (vectorOfAdjacentCountries[y]->country_GetOwner() != p) {

						/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
						for(unsigned int a = 0; a < rg->riskGame_getMap()->map_GetAllCountries().size(); a++)
						{
							if(rg->riskGame_getMap()->map_GetAllCountries()[a] == p->myCollectionOfCountries[x])
							{
								/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
								for(unsigned int b = 0; b < rg->riskGame_getMap()->map_GetAllCountries().size(); b++)
								{
									if(rg->riskGame_getMap()->map_GetAllCountries()[b] == vectorOfAdjacentCountries[y]) {
										/* Print out a line confirming the possibility to perform this attack */
										cout << "[" << a << "] " << p->myCollectionOfCountries[x]->country_GetName() << " (" << p->myCollectionOfCountries[x]->country_GetNumArmies() << " units) may attack [" << b << "] "  << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
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
			vector<Country *> vectorOfAllCountries = rg->riskGame_getMap()->map_GetAllCountries();

			/* Print out the state of these countries */
			cout << endl;
			cout << "Attacking: " << vectorOfAllCountries[attackingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[attackingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[attackingCountryIndex]->country_GetOwner()->player_getPlayerName() << endl;
			cout << "Defending: " << vectorOfAllCountries[defendingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[defendingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[defendingCountryIndex]->country_GetOwner()->player_getPlayerName()  << endl;

			/* Variables sent to observers */
			p->attackingCountry = vectorOfAllCountries[attackingCountryIndex];
			p->attackedCountry = vectorOfAllCountries[defendingCountryIndex];
			p->attackingCountryArmies = vectorOfAllCountries[attackingCountryIndex]->country_GetNumArmies();
			p->attackedCountryArmies = vectorOfAllCountries[defendingCountryIndex]->country_GetNumArmies();

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
					cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

					p->attackOutcomeVictory = true;
					p->successfulInvasion = true;

					cout << endl;
					rg->riskGame_getMap()->subject_Notify();
					cout << endl;
				}
				else {
					cout << "The defender won the battle." << endl;
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

					p->attackOutcomeVictory = false;
				}
			}
			else if(numOfDiceAttacker == 1 && numOfDiceDefender == 2) {
				if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
					cout << "The attacker won the battle." << endl;
					defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);

					/* Variables sent to observers */
					p->attackOutcomeVictory = true;
					p->successfulInvasion = false;
				}
				else {
					cout << "The defender won the battle." << endl;
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

					/* Variables sent to observers */
					p->attackOutcomeVictory = false;
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
					cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

					/* Variables sent to observers */
					p->attackOutcomeVictory = true;
					p->successfulInvasion = true;

					cout << endl;
					rg->riskGame_getMap()->subject_Notify();
					cout << endl;
				}
				else {
					cout << "The defender won the battle." << endl;
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

					/* Variables sent to observers */
					p->attackOutcomeVictory = false;
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
					cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

					/* Variables sent to observers */
					p->attackOutcomeVictory = true;
					p->successfulInvasion = true;

					cout << endl;
					rg->riskGame_getMap()->subject_Notify();
					cout << endl;
				}
				else
				{
					/* Variables sent to observers */
					p->attackOutcomeVictory = false;
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
					cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

					/* Variables sent to observers */
					p->attackOutcomeVictory = true;
					p->successfulInvasion = true;

					cout << endl;
					rg->riskGame_getMap()->subject_Notify();
					cout << endl;
				}
				else {
					cout << "The defender won the battle." << endl;
					attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

					/* Variables sent to observers */
					p->attackOutcomeVictory = false;
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
					cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl << endl;
					capturedCountry = true;
					defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
					attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

					/* Variables sent to observers */
					p->attackOutcomeVictory = true;
					p->successfulInvasion = true;

					cout << endl;
					rg->riskGame_getMap()->subject_Notify();
					cout << endl;
				}
				else
				{
					/* Variables sent to observers */
					p->attackOutcomeVictory = false;
				}
			}
			/* Notifify all observers */
			p->subject_Notify();
		}
	}

	/* Draw if a country was captured during the attack phase */
	if(capturedCountry)
		p->myHand.hand_addCardToHand(rg->riskGame_getDeck()->deck_draw());

	cout << endl;
	cout << "Attack End" << endl << endl;
	return;
}

void HumanPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	cout << "- HUMAN STRATEGY -" << endl;
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

	for(unsigned int w = 0; w < p->myHand.hand_getHandOfCards().size();w++) {
		p->myHand.hand_getHandOfCards()[w]->card_printType();
	}

	cout << endl;

	/* Calculating the base amount of new armies at the start of the turn */
	int newArmiesCount = p->myCollectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* Put of all the unique continents where the player owns at least 1 country on into a vector */
	set<Continent *> setOfUniqueContinents = *p->player_getUniqueContinents();

	for(set<Continent *>::iterator it = setOfUniqueContinents.begin(); it != setOfUniqueContinents.end(); it++)
	{
		/* If this condition is true, that means player owns the current iterated continent */
		if((*(*it)).continent_playerOwnsContinent(p)) {
			int continentBonus = (*(*it)).continent_getBonusValue();	// get the bonus value from the respective continent object
			string continentName = (*(*it)).continent_GetContinentName();
			cout << "Reinforcement Army Bonus! " << continentBonus << " additional army units for completely controlling a continent - " << continentName << "." << endl;
			newArmiesCount = newArmiesCount + continentBonus;	// increment the player's new army count by the continent bonus
		}
	}

	cout << endl;

	/* If player's hand has 5 or more cards, they MUST exchange for armies */
	while(p->myHand.hand_getHandOfCards().size() > 4) {
		cout << "Forced Exchange Phase:" << endl;
		cout << "You have at least 5 cards in your hand, therefore you must trade in a set." << endl;
		newArmiesCount = newArmiesCount + p->myHand.hand_exchange(rg); // exchange(currentMap) will modify the hand of the player, thus decrementing their hand size

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
			newArmiesCount = newArmiesCount + p->myHand.hand_exchange(rg);
		}
		else if(exchangeAnswer == 2)
		{
			rg->riskGame_showStateOfPlayer(p);	// show player's board
		}
		else if(exchangeAnswer == 3)
		{
			rg->riskGame_showStateOfGame(); // show the whole board
		}
		else
		{
			exchangePhaseDoneFlag = true;
		}
	}

	/* This loop will run as long as the player did not place all their additional reinforcement units */
	while(newArmiesCount != 0){


		/* Variables sent to observers */
		p->totalReinforcementCount = newArmiesCount;

		cout << "List of my countries:" << endl << endl;

		/* Display the whole board */
		rg->riskGame_showStateOfGame();

		/* Printing out the player's collection of countries with their respective index in the player's collection */
		rg->riskGame_showStateOfPlayer(p);

		/* Prompt the player to enter the index of the country they would like to reinforce */

		string newArmyLocationMessage = "Where would you like place your new army unit(s)? (" + std::to_string(newArmiesCount) + " left) Enter the country index.";
		int newArmyLocationIndex = UserInterface::userInterface_getIntegerBetweenRange(newArmyLocationMessage, 0, p->myCollectionOfCountries.size());

		/* Prompt the player to enter the number of units they would like to place on this country */
		string newArmyAmountMessage = "How many army unit(s) would you like to place here? (" + std::to_string(newArmiesCount) + " unit(s) left!)";
		int newArmyAmountPlaced = UserInterface::userInterface_getIntegerBetweenRange(newArmyAmountMessage, 0, newArmiesCount);


		/* Variables sent to observers */
		p->reinforcingCountry = p->myCollectionOfCountries[newArmyLocationIndex];
		p->amountToReinforce = newArmyAmountPlaced;

		/* Add the armies to the appropriate country */
		p->myCollectionOfCountries[newArmyLocationIndex]->country_SetNumArmies(p->myCollectionOfCountries[newArmyLocationIndex]->country_GetNumArmies() + newArmyAmountPlaced);

		/* Decrement the number of new armies available*/
		newArmiesCount = newArmiesCount - newArmyAmountPlaced;

		/* Notify all observers */
		p->subject_Notify();
	}
	cout << endl;
	cout << "Reinforcement End" << endl << endl;
	return;
}

void HumanPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	cout << "- HUMAN STRATEGY -" << endl;
	cout << "FORTIFICATION PHASE" << endl;
	cout << "Fortification Start" << endl << endl;

	cout << "Here are your possible fortifications:" << endl;

	/* This outer loop will go through the player's collection of countries */
	for (unsigned int x = 0; x < p->myCollectionOfCountries.size();x++) {
		/* Checking if the current country has at least 2 armies on them to perform a fortify, needs to at least leave 1 army behind */
		if(p->myCollectionOfCountries[x]->country_GetNumArmies() >= 2){
			/* Using the map_GetCountriesAdjacentTo() function to create a vector that holds all adjacent countries to a specific country */
			vector<Country *> vectorOfAdjacentCountries = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->myCollectionOfCountries[x]);
			/* Loop through the adjacent countries */
			for (unsigned int y = 0; y < vectorOfAdjacentCountries.size(); y++) {
				/* Check if the current country is an ally country */
				if (vectorOfAdjacentCountries[y]->country_GetOwner() == p) {
					/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
					for(unsigned int a = 0; a < rg->riskGame_getMap()->map_GetAllCountries().size(); a++)
					{
						if(rg->riskGame_getMap()->map_GetAllCountries()[a] == p->myCollectionOfCountries[x])
						{
							/* Inner for loop needed to keep track of global shared/global indexes instead of personal indexes */
							for(unsigned int b = 0; b < rg->riskGame_getMap()->map_GetAllCountries().size(); b++)
							{
								if(rg->riskGame_getMap()->map_GetAllCountries()[b] == vectorOfAdjacentCountries[y]) {
									/* Print out a line confirming the possibility to perform this fortify */
									cout << "[" << a << "] " << p->myCollectionOfCountries[x]->country_GetName() << " (" << p->myCollectionOfCountries[x]->country_GetNumArmies() << " units) may fortify [" << b << "] " << vectorOfAdjacentCountries[y]->country_GetName() << " (" << vectorOfAdjacentCountries[y]->country_GetNumArmies() << " units)." << endl;
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
		vector<Country *> vectorOfAllCountries = rg->riskGame_getMap()->map_GetAllCountries();

		/* Variables sent to observers */
		p->fortifyingCountry = vectorOfAllCountries[fromCountry];
		p->fortifiedCountry = vectorOfAllCountries[toCountry];
		p->fortifyingCountryArmies = vectorOfAllCountries[fromCountry]->country_GetNumArmies();
		p->fortifiedCountryArmies = vectorOfAllCountries[toCountry]->country_GetNumArmies();

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
				/* Variables sent to observers */
				p->amountToFortify = numOfArmiesToMove;
			}
		}
		/* Notify all observers */
		p->subject_Notify();
	}

	cout << endl;
	cout << "Fortification End" << endl << endl;
	return;
}

/** Implement the following functions for Aggressive attacks,
 * reinforcements and fortifications
 * */
void AggressivePhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	cout << "- AGRESSIVE STRATEGY -" << endl;
	cout << "ATTACK PHASE" << endl;
	cout << "Attack Start" << endl;

	bool capturedCountry = false; // flag used to determine if a country was captured this turn
	bool attackPossible = true; // flag used to determine whether an attack is possible

	while(attackPossible)
	{
		attackPossible = false; // set to false by default

		/* This loop will change attackPossible to true if the current player can make any possible attack */
		for(int i = 0; i < p->myCollectionOfCountries.size(); i++)
		{
			if(p->myCollectionOfCountries[i]->country_GetNumArmies() > 1)
			{
				vector <Country *> adjacentCountries = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->myCollectionOfCountries[i]);

				for(int n = 0; n < adjacentCountries.size(); n++)
				{
					if(adjacentCountries[n]->country_GetOwner() != p)
					{
						attackPossible = true;
					}
				}
			}
		}

		/* If attackPossible is false, then the loop stops */
		if(!attackPossible)
			break;

		/* This loop will iterate through all the countries in the current player's collection */
		for(int r = 0; r < p->myCollectionOfCountries.size(); r++)
		{

			/* Get enemy adjacent countries to the player's strongest country */
			vector <Country *> adjacentCountriesToStrongest = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->player_getMyCountries()[r]);
			vector <Country *> adjacentCountriesToStrongestCOPY = adjacentCountriesToStrongest; // copy used to keep track of original indexes (due to deleting inside a vector)

			for(int i = 0; i < adjacentCountriesToStrongestCOPY.size(); i ++)
			{
				/* If an adjacent country is current owned by the same player */
				if(adjacentCountriesToStrongestCOPY[i]->country_GetOwner() == p)
				{
					/* Find the respective country inside the original vector */
					for(int m = 0; m < adjacentCountriesToStrongest.size(); m++)
					{
						if(adjacentCountriesToStrongestCOPY[i] == adjacentCountriesToStrongest[m])
						{
							/* Erase that country from the original vector (this will be used to iterate through all the countries to attack) */
							adjacentCountriesToStrongest.erase(adjacentCountriesToStrongest.begin() + m);
						}
					}
				}
			}

			/* Keep attacking until, the current country has no more countries to attack or if the current country doesn't have enough armies to perform the attack  */
			while(adjacentCountriesToStrongest.size() != 0 && p->player_getMyCountries()[r]->country_GetNumArmies() > 1)
			{
				int globalIndexOfStrongest; // this will hold the global index of the strongest country

				/* This loop will find the global index of the strongest country */
				for(int i = 0; i < rg->riskGame_getMap()->map_GetAllCountries().size(); i++){
					if(rg->riskGame_getMap()->map_GetAllCountries()[i] == p->player_getMyCountries()[r])
					{
						globalIndexOfStrongest = i;
					}
				}

				int attackingCountryIndex = globalIndexOfStrongest;
				int defendingCountryIndex;

				/* Find and set the current defending country's global index*/
				for(int i = 0; i < rg->riskGame_getMap()->map_GetAllCountries().size(); i++){
					if(rg->riskGame_getMap()->map_GetAllCountries()[i] == adjacentCountriesToStrongest[0])
					{
						defendingCountryIndex = i;
					}
				}

				cout << "Attacking global Index: " << attackingCountryIndex << endl;
				cout << "Defending global Index: " << defendingCountryIndex << endl;

				/* Create a vector that will hold all countries in the game */
				vector<Country *> vectorOfAllCountries = rg->riskGame_getMap()->map_GetAllCountries();

				/* Print out the state of these countries */
				cout << endl;
				cout << "Attacking: " << vectorOfAllCountries[attackingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[attackingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[attackingCountryIndex]->country_GetOwner()->player_getPlayerName() << endl;
				cout << "Defending: " << vectorOfAllCountries[defendingCountryIndex]->country_GetName() << " has " << vectorOfAllCountries[defendingCountryIndex]->country_GetNumArmies() << " armies and belongs to " << vectorOfAllCountries[defendingCountryIndex]->country_GetOwner()->player_getPlayerName()  << endl;

				/* Variables sent to observers */
				p->attackingCountry = vectorOfAllCountries[attackingCountryIndex];
				p->attackedCountry = vectorOfAllCountries[defendingCountryIndex];
				p->attackingCountryArmies = vectorOfAllCountries[attackingCountryIndex]->country_GetNumArmies();
				p->attackedCountryArmies = vectorOfAllCountries[defendingCountryIndex]->country_GetNumArmies();

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
					cout << "Attacker will roll 3 dice (REMINDER: " + std::to_string(attackingCountry->country_GetNumArmies()) + " units on your country)" << endl << endl;
					numOfDiceAttacker = 3;
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
						cout << "Attacker would like to move 1 unit from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << endl;
						numOfArmiesToMove = 1;

						defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
						attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
						defendingCountry->country_SetNumArmies(numOfArmiesToMove);
						cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
						capturedCountry = true;
						defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
						attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

						p->attackOutcomeVictory = true;
						p->successfulInvasion = true;

						/* Notify GameStatisticsObserver */
						cout << endl;
						rg->riskGame_getMap()->subject_Notify();
						cout << endl;
						}
					else {
						cout << "The defender won the battle." << endl;
						attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

						p->attackOutcomeVictory = false;
					}
				}
				else if(numOfDiceAttacker == 1 && numOfDiceDefender == 2) {
					if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
						cout << "The attacker won the battle." << endl;
						defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);

						/* Variables sent to observers */
						p->attackOutcomeVictory = true;
						p->successfulInvasion = false;
					}
					else {
						cout << "The defender won the battle." << endl;
						attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

						/* Variables sent to observers */
						p->attackOutcomeVictory = false;
					}
				}
				else if(numOfDiceAttacker == 2 && numOfDiceDefender == 1) {
					if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
						cout << "The attacker won the battle." << endl;
						cout << "The defender has no more units on their country." << endl;

						/* Note: Attacker's must leave behind at least 1 unit */
						cout << "Attacker would like to move 1 unit from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << endl;
						numOfArmiesToMove = 1;


						defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
						attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
						defendingCountry->country_SetNumArmies(numOfArmiesToMove);
						cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
						capturedCountry = true;
						defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
						attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

						/* Variables sent to observers */
						p->attackOutcomeVictory = true;
						p->successfulInvasion = true;

						/* Notify GameStatisticsObserver */
						cout << endl;
						rg->riskGame_getMap()->subject_Notify();
						cout << endl;
					}
					else {
						cout << "The defender won the battle." << endl;
						attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

						/* Variables sent to observers */
						p->attackOutcomeVictory = false;
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
							cout << "Attacker would like to move 1 unit from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << endl;
							numOfArmiesToMove = 1;

							defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
							attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
							defendingCountry->country_SetNumArmies(numOfArmiesToMove);
							cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
							capturedCountry = true;
							defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
							attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

							/* Variables sent to observers */
							p->attackOutcomeVictory = true;
							p->successfulInvasion = true;

							/* Notify GameStatisticsObserver */
							cout << endl;
							rg->riskGame_getMap()->subject_Notify();
							cout << endl;
							}
							else
							{
								/* Variables sent to observers */
								p->attackOutcomeVictory = false;
							}
						}
						else if(numOfDiceAttacker == 3 && numOfDiceDefender == 1) {
							if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
								cout << "The attacker won the battle." << endl;
								cout << "The defender has no more units on their country." << endl;

								/* Note: Attacker's must leave behind at least 1 unit */
								cout << "Attacker would like to move 1 unit from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << endl;
								numOfArmiesToMove = 1;

								defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
								attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
								defendingCountry->country_SetNumArmies(numOfArmiesToMove);
								cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl;
								capturedCountry = true;
								defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
								attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

								/* Variables sent to observers */
								p->attackOutcomeVictory = true;
								p->successfulInvasion = true;

								/* Notify GameStatisticsObserver */
								cout << endl;
								rg->riskGame_getMap()->subject_Notify();
								cout << endl;
							}
							else {
								cout << "The defender won the battle." << endl;
								attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);

								/* Variables sent to observers */
								p->attackOutcomeVictory = false;
							}
						}
					else if (numOfDiceAttacker == 3 && numOfDiceDefender == 2) {
						p->attackOutcomeVictory = true;
						if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[0] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[0]) {
							cout << "The attacker won the first battle." << endl;
							defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
						}
						else {
							cout << "The defender won the first battle." << endl;
							attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
							/* Variables sent to observers */
							p->attackOutcomeVictory = false;
						}

						if(attackingCountry->country_GetOwner()->myDRF.resultsRolled[1] > defendingCountry->country_GetOwner()->myDRF.resultsRolled[1]){
							cout << "The attacker won the second battle." << endl;
							defendingCountry->country_SetNumArmies(defendingCountry->country_GetNumArmies() - 1);
						}
						else {
							cout << "The defender won the second battle." << endl;
							attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - 1);
							/* Variables sent to observers */
							p->attackOutcomeVictory = false;
						}

						if(defendingCountry->country_GetNumArmies() == 0) {
							cout << " gg..." << endl;
							cout << "The defender has no more units on their country." << endl;

							/* Note: Attacker's must leave behind at least 1 unit */
							cout << "Attacker would like to move 1 unit to move from " << attackingCountry->country_GetName() << " to " << defendingCountry->country_GetName() << endl;
							numOfArmiesToMove = 1;

							defendingCountry->country_SetOwner(attackingCountry->country_GetOwner());
							attackingCountry->country_SetNumArmies(attackingCountry->country_GetNumArmies() - numOfArmiesToMove);
							defendingCountry->country_SetNumArmies(numOfArmiesToMove);
							cout << p->myName << " now owns " << defendingCountry->country_GetName() << "." << endl << endl;
							defendingCountry->country_GetOwner()->player_removeCountry(defendingCountry);
							attackingCountry->country_GetOwner()->player_addCountry(defendingCountry);

							/* Variables sent to observers */
							p->attackOutcomeVictory = true;
							p->successfulInvasion = true;

							/* Notify GameStatisticsObserver */
							cout << endl;
							rg->riskGame_getMap()->subject_Notify();
							cout << endl;
						}
				}
				/* Get enemy adjacent countries to the player's strongest country */
				adjacentCountriesToStrongest = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->player_getMyCountries()[r]);

				vector <Country *> adjacentCountriesToStrongestCOPY2 = adjacentCountriesToStrongest;
				for(int i = 0; i < adjacentCountriesToStrongestCOPY2.size(); i ++)
				{
					if(adjacentCountriesToStrongestCOPY2[i]->country_GetOwner() == p)
					{
						for(int m = 0; m < adjacentCountriesToStrongest.size(); m++)
						{
							if(adjacentCountriesToStrongestCOPY2[i] == adjacentCountriesToStrongest[m])
							{
								adjacentCountriesToStrongest.erase(adjacentCountriesToStrongest.begin() + m);
							}
						}
					}
				}
				/* Notify all observers */
				p->subject_Notify();
			}
		}
	}

	/* Draw if a country was captured during the attack phase */
	if(capturedCountry)
		p->myHand.hand_addCardToHand(rg->riskGame_getDeck()->deck_draw());

	cout << endl;
	cout << "Attack End" << endl << endl;
}

void AggressivePhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	cout << "- AGGRESSIVE STRATEGY -" << endl;
	cout << "REINFORCEMENT PHASE:" << endl;

	cout << "Reinforcement Start" << endl;

	/* Calculating the base amount of new armies at the start of the turn */
	int newArmiesCount = p->myCollectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* Put of all the unique continents where the player owns at least 1 country on into a vector */
	set<Continent *> setOfUniqueContinents = *p->player_getUniqueContinents();

	for(set<Continent *>::iterator it = setOfUniqueContinents.begin(); it != setOfUniqueContinents.end(); it++)
	{
		/* If this condition is true, that means player owns the current iterated continent */
		if((*(*it)).continent_playerOwnsContinent(p)) {
			int continentBonus = (*(*it)).continent_getBonusValue();	// get the bonus value from the respective continent object
			string continentName = (*(*it)).continent_GetContinentName();
			cout << "Reinforcement Army Bonus! " << continentBonus << " additional army units for completely controlling a continent - " << continentName << "." << endl;
			newArmiesCount = newArmiesCount + continentBonus;	// increment the player's new army count by the continent bonus
		}
	}

	cout << endl;

	cout << "Exchange Phase:" << endl;
	/* Exchange if it is possible */
	newArmiesCount = newArmiesCount + p->myHand.hand_autoExchange(rg);
	cout << endl;

	/*Find the strongest country */
	/* Index (Country) with the highest amount of armies */
	int maxIndex = 0;
	/* Iterate until we find a country with an amount of armies higher than the current max index */
	for(int i = 1; i < p->player_getMyCountries().size(); i++)
	{
		if(p->player_getMyCountries()[i]->country_GetNumArmies() > p->player_getMyCountries()[maxIndex]->country_GetNumArmies())
			maxIndex = i;
	}

	/* Variables sent to observers */
	p->totalReinforcementCount = newArmiesCount;

	/* Display the whole board */
	rg->riskGame_showStateOfGame();

	/* Printing out the player's collection of countries with their respective index in the player's collection */
	rg->riskGame_showStateOfPlayer(p);
	/* Variables sent to observers */
	p->reinforcingCountry = p->myCollectionOfCountries[maxIndex];
	p->amountToReinforce = newArmiesCount;

	/* Add the armies to the appropriate country */
	p->myCollectionOfCountries[maxIndex]->country_SetNumArmies(p->myCollectionOfCountries[maxIndex]->country_GetNumArmies() + newArmiesCount);

	/* Notify all observers */
	p->subject_Notify();

	cout << endl;
	cout << "Reinforcement End" << endl << endl;

	return;
}

void AggressivePhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	bool fortyingPossible = false;
	cout << "- AGGRESSIVE STRATEGY -" << endl;
	cout << "FORTIFICATION PHASE" << endl;
	cout << "Fortification Start" << endl << endl;
	/* Find the strongest country */
	/* Index (Country) with the highest amount of armies */
	int maxIndex = 0;
	/* Iterate until we find a country with an amount of armies higher than the current max index */
	for(int i = 1; i < p->player_getMyCountries().size(); i++)
	{
		if(p->player_getMyCountries()[i]->country_GetNumArmies() > p->player_getMyCountries()[maxIndex]->country_GetNumArmies())
			maxIndex = i;
	}

	/* This vector will store all adjacent countries of the strongest one */
	vector <Country *> adjacentCountriesToStrongest = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(p->player_getMyCountries()[maxIndex]);

	for(int i = 0; i < adjacentCountriesToStrongest.size(); i ++)
	{
		/* Filter out the countries that are not owned by the same player */
		if(adjacentCountriesToStrongest[i]->country_GetOwner() == p)
		{
			/* Filter out the countries that do not have enough units to send */
			if(adjacentCountriesToStrongest[i]->country_GetNumArmies() > 2)
			{
				/* Algorithm to transfer units from one country to another */
				p->fortifyingCountryArmies = adjacentCountriesToStrongest[i]->country_GetNumArmies();
				p->fortifiedCountryArmies = p->player_getMyCountries()[maxIndex]->country_GetNumArmies();
				p->player_transferMaxArmy(adjacentCountriesToStrongest[i], p->player_getMyCountries()[maxIndex]);
				p->fortifyingCountry = adjacentCountriesToStrongest[i];
				p->fortifiedCountry = p->player_getMyCountries()[maxIndex];
				cout << "Successfully sent " << (adjacentCountriesToStrongest[i]->country_GetNumArmies() - 1)  << " army units from " << adjacentCountriesToStrongest[i]->country_GetName() << " to " << p->player_getMyCountries()[maxIndex]->country_GetName();
				/* Variables sent to observers */
				p->amountToFortify = adjacentCountriesToStrongest[i]->country_GetNumArmies() - 1;
				/* Notify all observers */
				p->subject_Notify();
				fortyingPossible = true;
				break; // can only fortify once
			}
		}
	}
	if(fortyingPossible ==  false){
		cout << "NO FORTIFICATION POSSIBLE!" << endl << endl;

	}

	cout << endl;
	cout << "Fortification End" << endl << endl;

	return;
}

/** Implement the following functions for Benevolent attacks,
 * reinforcements and fortifications
 * */
void BenevolentPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	cout << "- BENEVOLENT STRATEGY -" << endl;
	cout << "ATTACK PHASE:" << endl;
	cout << "Attack Start" << endl << endl;

	/* A benevolent strategist does not attack */
	cout << "As a benevolent strategist, you do not wish to attack at this time." << endl;

	cout << endl;
	cout << "Attack End " << endl << endl;
	return;
}

void BenevolentPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	cout << "- BENEVOLENT STRATEGY -" << endl;
	cout << "REINFORCEMENT PHASE:" << endl;
	cout << "Reinforcement Start" << endl << endl;

	/* Display player's hand */
	cout << "Current Hand: " << endl;

	for (unsigned int b = 0; b < p->myHand.hand_getHandOfCards().size(); b++){
		p->myHand.hand_getHandOfCards()[b]->card_printType();
	}

	cout << endl;

	/* Calculating the base amount of new armies at the start of the turn */
	int newArmiesCount = p->myCollectionOfCountries.size() / 3;

	/* Players receive at least 3 armies per turn */
	if(newArmiesCount < 3)
		newArmiesCount = 3;

	/* Put of all the unique continents where the player owns at least 1 country on into a vector */
	set<Continent *> setOfUniqueContinents = *p->player_getUniqueContinents();

	for(set<Continent *>::iterator it = setOfUniqueContinents.begin(); it != setOfUniqueContinents.end(); it++)
	{
		/* If this condition is true, that means player owns the current iterated continent */
		if((*(*it)).continent_playerOwnsContinent(p)) {
			int continentBonus = (*(*it)).continent_getBonusValue();	// get the bonus value from the respective continent object
			string continentName = (*(*it)).continent_GetContinentName();
			cout << "Reinforcement Army Bonus! " << continentBonus << " additional army units for completely controlling a continent - " << continentName << "." << endl;
			newArmiesCount = newArmiesCount + continentBonus;	// increment the player's new army count by the continent bonus
		}
	}

	cout << endl;

	cout << "Exchange Phase:" << endl;
	/* Exchange if it is possible */
	newArmiesCount = newArmiesCount + p->myHand.hand_autoExchange(rg);
	cout << endl;

	/* This loop will run as long as the player did not place all their additional reinforcement units */
	while(newArmiesCount != 0){

		/* Variables sent to observers */
		p->totalReinforcementCount = newArmiesCount;

		unsigned int minNumOfArmies = p->myCollectionOfCountries[0]->country_GetNumArmies();	// smallest minNumOfArmies is 1 by default

		/* Code block that calculates the smallest number of army units on one country in the player's collection */
		for(unsigned int i = 1; i < p->myCollectionOfCountries.size(); i++)
		{
			if (p->myCollectionOfCountries[i]->country_GetNumArmies() < minNumOfArmies)
			{
				minNumOfArmies = p->myCollectionOfCountries[i]->country_GetNumArmies();
			}
		}

		/* Code block that adds 1 unit to the first occurrence of country that has the minimum amount of army units */
		for(unsigned int i = 0; i < p->myCollectionOfCountries.size(); i++)
		{
			if (p->myCollectionOfCountries[i]->country_GetNumArmies() == minNumOfArmies)
			{
				cout << p->myCollectionOfCountries[i]->Country::country_GetName() + " is the weakest country." << endl;
				newArmiesCount--;
				cout << "Placing one army unit on " << p->myCollectionOfCountries[i]->country_GetName() << ". (" << newArmiesCount <<  " left to place)";
				p->myCollectionOfCountries[i]->country_SetNumArmies(p->myCollectionOfCountries[i]->country_GetNumArmies() + 1);

				/* Variables sent to observers */
				p->reinforcingCountry = p->myCollectionOfCountries[i];
				p->amountToReinforce = 1;
				break;
			}
		}

		/* Notify all observers */
		p->subject_Notify();
	}

	cout << endl;
	cout << "Reinforcement End" << endl << endl;

	return;
}

void BenevolentPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	cout << "- BENEVOLENT STRATEGY -" << endl;
	cout << "FORTIFICATION PHASE" << endl;
	cout << "Fortification Start" << endl << endl;

	vector<Country *> vectorOfAllWeakestCountries; // this vector will hold all the "weakest" countries

	unsigned int minNumOfArmies = 1;

	/* Code block that calculates the smallest number of army units on one country in the player's collection */
	for(unsigned int i = 0; i < p->myCollectionOfCountries.size(); i++)
	{
		if (p->myCollectionOfCountries[i]->country_GetNumArmies() < minNumOfArmies)
		{
			minNumOfArmies = p->myCollectionOfCountries[i]->country_GetNumArmies();
		}
	}

	/* Code block that will add all the weakest countries in a player's collection into vectorOfAllWeakestCountries */
	for(unsigned int i = 0; i < p->myCollectionOfCountries.size(); i++)
	{
		if (p->myCollectionOfCountries[i]->country_GetNumArmies() == minNumOfArmies)
		{
			vectorOfAllWeakestCountries.push_back(p->myCollectionOfCountries[i]);
		}
	}

	/* "Comparison" Algorithm */

	for(unsigned int x = 0; x < vectorOfAllWeakestCountries.size(); x++)
	{
		/* This vector will hold all adjacent countries of a specific country */
		vector<Country *> vectorOfAdjacentCountries = rg->riskGame_getMap()->map_GetCountriesAdjacentTo(vectorOfAllWeakestCountries[x]);

		for(int y = 0; y < vectorOfAdjacentCountries.size(); y++)
		{
			/* Verify that the current adjacent country is owned by the same player */
			if(vectorOfAdjacentCountries[y]->country_GetOwner() == p)
			{
				/* Condition that decides whether a unit should be sent from this (adjacent) country to the original country */
				if(vectorOfAllWeakestCountries[x]->country_GetNumArmies() < vectorOfAdjacentCountries[y]->country_GetNumArmies() - 1)
				{
					/* Variables sent to observers */
					p->fortifyingCountry = vectorOfAdjacentCountries[y];
					p->fortifiedCountry = vectorOfAllWeakestCountries[x];
					p->fortifyingCountryArmies = vectorOfAdjacentCountries[y]->country_GetNumArmies();
					p->fortifiedCountryArmies = vectorOfAllWeakestCountries[x]->country_GetNumArmies();
					p->amountToFortify = 1;

					vectorOfAllWeakestCountries[x]->country_SetNumArmies(vectorOfAllWeakestCountries[x]->country_GetNumArmies() - 1);
					vectorOfAdjacentCountries[y]->country_SetNumArmies(vectorOfAdjacentCountries[y]->country_GetNumArmies() + 1);

					/* Notify all observers */
					p->subject_Notify();
					return;
				}
			}
		}
	}
}





