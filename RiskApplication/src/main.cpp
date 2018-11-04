/*
 * main.cpp
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */
#include <iostream>

#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "DiceRollingFacility.h"
#include "Country.h"
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
#include "RiskGame.h"

/**
 * Code contains all the driver functions used in demonstrating assignment 1
 * **/
int assignment1Driver(void)
{


	/************************************************
	 *
	 * Map Loader & Graph
	 *
	 ***********************************************/

	/** Change this path to comply with your filesystem (make sure there is a trailing forward slash) */
	string basePathToMapFolder = "C:/Users/Rainily/Documents/GitHub/COMP345/RiskApplication/MapFiles/";

	string mapFiles[] = {basePathToMapFolder + "World.map", \
							basePathToMapFolder + "Annys World.map", \
							basePathToMapFolder + "MissingMapSection.map", \
							basePathToMapFolder + "MissingXCoordinate.map", \
							basePathToMapFolder + "MissingContinent.map", \
							basePathToMapFolder + "RandomText.map", \
							basePathToMapFolder + "Caribbean.map", \
							basePathToMapFolder + "Grill's Galaxy.map" \
						};

	MapLoader p;

	Map * newMap;

	/** Load the map */
	if ( (newMap = p.mapLoader_LoadMap(mapFiles[0])) == NULL)
	{
		print("Could not parse file");
		return 0;
	}

	/** Map is of valid format */
	print("Map is valid!");

	/** Display the number of continents */

	print("Map connected?");

	if (!newMap->map_IsValidMap())
	{
		print("MAP IS INVALID - NOT CONNECTED (either whole or subgraph)");
		return 0;
	}
	else
	{
		print("MAP IS VALID - CONNECTED, AND ALL CONTINENTS' SUBGRAPHS ARE CONNECTED");
	}


	/** Pull all countries - allCountries contains pointers to Country objects, so
	 * any editing you perform on these countries (with setters) will be directly
	 * changed in the graph countries (which is what we want). Aka these Country objects are exactly
	 * the same ones from the graph
	 * */
	vector<Country *> allCountries = newMap->map_GetAllCountries();

	print("********ALL COUNTRIES********");
	for (UINT i = 0; i<allCountries.size(); i++)
	{
		cout << *(allCountries[i]) << endl;
	}


	/** Pull adjacent countries */
	if (allCountries.size() > 0)
	{
		/** Pick a country you want to get adjacency of - say country at index 0 */
		Country * someCountry = allCountries[0];

		/** Get adjacent countries */
		vector<Country *> adjacentCountries = newMap->map_GetCountriesAdjacentTo(someCountry);

		print("********ADJACENT COUNTRIES ********");
		cout << "Countries Adjacent to " << *someCountry << " are:" << endl;

		for (UINT i = 0; i<adjacentCountries.size(); i++)
		{

			/** Before army set */
			cout << *(adjacentCountries[i]) << endl;

			/** Note the number of armies changing because of use of pointers */
			(*(adjacentCountries[i])).country_SetNumArmies(99);

			/** After army set */
			cout << *(adjacentCountries[i]) << endl;

		}


	}

	/************************************************
	 *
	 * 						Dice
	 *
	 ***********************************************/

	/** Put driver code here */
	cout << endl;
	cout << "************************** TESTING DICE **************************" << endl << endl;

	Player tempPlayer("DiceTester");

	cout << "First player rolls 1 die" << endl;
	tempPlayer.player_getMyDRF()->diceRollingFacility_rollDice(1);
	cout << tempPlayer.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[2] << endl;

	cout << "First player rolls 2 dice" << endl;
	tempPlayer.player_getMyDRF()->diceRollingFacility_rollDice(2);
	cout << tempPlayer.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[2] << endl;

	cout << "First player rolls 3 dice" << endl;
	tempPlayer.player_getMyDRF()->diceRollingFacility_rollDice(3);
	cout << tempPlayer.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer.player_getMyDRF()->resultsRolled[2] << endl;

	tempPlayer.player_getMyDRF()->diceRollingFacility_printPlayerDiceStatistics();

	Player tempPlayer2("DiceTester2");

	cout << "Second player rolls 1 die" << endl;
	tempPlayer2.player_getMyDRF()->diceRollingFacility_rollDice(1);
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[2] << endl;

	cout << "Second player rolls 2 dice" << endl;
	tempPlayer2.player_getMyDRF()->diceRollingFacility_rollDice(2);
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[2] << endl;

	cout << "Second player rolls 3 dice" << endl;
	tempPlayer2.player_getMyDRF()->diceRollingFacility_rollDice(3);
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[0] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[1] << endl;
	cout << tempPlayer2.player_getMyDRF()->resultsRolled[2] << endl;

	tempPlayer2.player_getMyDRF()->diceRollingFacility_printPlayerDiceStatistics();


	/************************************************
	 *
	 *						Player
	 *
	 ***********************************************/

	/** Put driver code here */
	cout << endl;
	cout << "************************** TESTING PLAYER **************************" << endl << endl;

	/* Creating 4 different players */
	Player player1("Rey");
	Player player2("Joy");
	Player player3("Anthony");
	Player player4("Daniel");


	/* Assigning every country to a player */
	int rotate = 0;
	for(unsigned int z = 0; z < allCountries.size(); z++){

		allCountries[z]->country_SetNumArmies(1); // Initiating the number of armies of each country to 1

		if(rotate == 0) {
			player1.player_addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player1);
			rotate++;
		} else if (rotate == 1)
		{
			player2.player_addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player2);
			rotate++;
		}
		else if (rotate == 2) {
			player3.player_addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player3);
			rotate++;
		}
		else {
			player4.player_addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player4);
			rotate = 0;
		}
	}

	cout << endl;
	cout << "Player 1's countries:" << endl;
	for(unsigned int p = 0; p < player1.player_getMyCountries().size(); p++){
		cout << *(player1.player_getMyCountries()[p]) << endl;
	}

	cout << endl;
	cout << "Player 2's countries:" << endl;
	for(unsigned int p = 0; p < player2.player_getMyCountries().size(); p++){
		cout << *(player2.player_getMyCountries()[p]) << endl;
	}

	/* Changing the number of armies on the first 3 countries so we can test attacking */
	allCountries[0]->country_SetNumArmies(5);
	allCountries[1]->country_SetNumArmies(3);
	allCountries[2]->country_SetNumArmies(3);

	/* Showing the current state of the board (Name of country, number of armies on it and owner) */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->player_getPlayerName() << endl;
	}

	cout << endl;
	cout << endl;

	/* Creating a deck to add cards to my hand */
	Deck testPlayerDeck(allCountries.size());

	/* Manually adding the first 6 cards to player1's hand (not drawing) to test the reinforce function (has to trade cards for armies at the start) */

	player1.player_getMyHand()->hand_addCardToHand(testPlayerDeck.deck_getDeck()[0]);
	player1.player_getMyHand()->hand_addCardToHand(testPlayerDeck.deck_getDeck()[1]);
	player1.player_getMyHand()->hand_addCardToHand(testPlayerDeck.deck_getDeck()[2]);
	player1.player_getMyHand()->hand_addCardToHand(testPlayerDeck.deck_getDeck()[3]);
	player1.player_getMyHand()->hand_addCardToHand(testPlayerDeck.deck_getDeck()[4]);


	/* Test the reinforce function */
	//player1.reinforce(newMap);

	/* Showing the current state of the board (Name of country, number of armies on it and owner) */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->player_getPlayerName() << endl;
	}

	/* Test the attack function */
	//player1.attack(newMap);

	/* Showing the current state of the board (Name of country, number of armies on it and owner) */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->player_getPlayerName() << endl;
	}

	cout << endl;

	/* Changing the owner and number of army units of certain countries to test the fortify function */

	allCountries[15]->country_SetOwner(&player1);
	allCountries[16]->country_SetOwner(&player1);
	allCountries[17]->country_SetOwner(&player1);
	allCountries[18]->country_SetOwner(&player1);

	allCountries[15]->country_SetNumArmies(5);
	allCountries[16]->country_SetNumArmies(5);
	allCountries[17]->country_SetNumArmies(5);
	allCountries[18]->country_SetNumArmies(5);

	/* Test the fortify function */
	//player1.fortify(newMap);

	cout << endl;
	cout << endl;

	/* Show the state of the board after the attack */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->player_getPlayerName() << endl;
	}



	/************************************************
	 *
	 * 					Cards (Deck/Hand)
	 *
	 ***********************************************/

	/** Put driver code here */

	cout << endl;
	cout << "************************** TESTING CARDS **************************" << endl << endl;

	/* Creating a deck */
	Deck newDeck(allCountries.size());

	/* Printing type of each card in deck */
	for (int i = 0; i < newDeck.deck_getDeckSize(); i++) {

		newDeck.deck_getDeck()[i]->card_printType();

	}

	cout << endl;

	/* Print out the number of cards in the deck */
	cout << "Deck has " << newDeck.deck_getDeckSize() << " cards" << endl;

	cout << endl;

	cout << "Drawing top card..." << endl;

	/* Draw the top card of the deck and print out its type */
	newDeck.deck_draw()->card_printType();

	cout << endl;

	/* Print out the new number of cards in the deck after drawing the top card */
	cout << "Deck has " << newDeck.deck_getDeckSize() << " cards" << endl;

	/* Manually adding the first 6 cards to player1's hand (not drawing)*/
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[0]);
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[1]);
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[2]);
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[3]);
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[4]);
	player4.player_getMyHand()->hand_addCardToHand(newDeck.deck_getDeck()[5]);

	/* Display the current cards in player1's hand */
	cout << endl;
	cout << "Player4's hand: " << endl;
	for(unsigned int d = 0; d < player4.player_getMyHand()->hand_getHandOfCards().size();d++) {
		player4.player_getMyHand()->hand_getHandOfCards()[d]->card_printType();
	}
	cout << endl;
	/* Testing the exchange function (trading in cards for armies), this will check the player's
	 * hand for a matching set and will return an integer (number of armies given) based on the total number of sets handed in during the game (variable stored in Map for now) */
	//cout << "From player1's current hand, they receive " << player4.exchange(newMap) << " army units." << endl;

	return 0;

}

enum Assignment2_PartToTest {
	GAME_START,
	GAME_STARTUP_PHASE,
	MAIN_GAME_LOOP,
	REINFORCEMENT_ATTACK_FORTIFICATION_PHASE
};

int main()
{
	/** Set the path to map files before running tests */
	RiskGame driver;

	driver.pathToMapFiles = "C:/Users/Anthony Andreoli/Desktop/Concordia/2018 - FALL/COMP 345/REPOSITORY/COMP345/RiskApplication/MapFiles";


	/** Select type of test */
	Assignment2_PartToTest partToTest = MAIN_GAME_LOOP;

	switch(partToTest)
	{

		/** Both tests are the same */
		case GAME_START ... GAME_STARTUP_PHASE:

		/* ***************************** PART 1 ***************************** */

		/* Driver for part 1 - Game Start:
		 * 1) Different valid maps can be loaded and their validity is verified (i.e. it is a connected graph, etc), and invalid maps are gracefully rejected
		 * 2) The right number of players is created, a deck with the right number of cards is created.
		 */

		/* ***************************** PART 2 ***************************** */

		/* Driver for part 2 - Startup Phase:
		 * 1) All countries in the map have been assigned to one and only one player
		 * 2) All players have eventually placed the right number of armies on their own countries after army placement is over.
		 */


			driver.riskGame_initializeGame();
			driver.riskGame_showStateOfGame();
			break;

		/* ***************************** PART 3 ***************************** */

		/* Driver for part 3 - Main Game Loop:
		 * 1) Every player gets turns in a round-robin fashion and that their reinforcement(), attack() and fortification() methods are called
		 * 2) The game ends when a player controls all the countries (the driver should explicitly give all the countries to one player.
		 */
		case MAIN_GAME_LOOP:

			driver.riskGame_initializeGame();

			/* Used to run the main game loop across all players once,
			 * (normally riskGame_playGame() would be called which would make the rotation loop until a winner is found */
			for(unsigned int i = 0; i < driver.riskGame_getPlayers().size(); i++)
			{
				driver.riskGame_playerTurn(driver.riskGame_getPlayers()[i]);
			}

			/* Assign all countries to the first player to trigger the win condition */
			driver.riskGame_giveAllCountriesToPlayer(driver.riskGame_getPlayers()[0]);
			driver.riskGame_playGame();

			break;

		/* ***************************** PART 4,5,6 ***************************** */

		/* Driver for part 4,5,6 - Reinforcement, Attack, Fortification Phase:
		 */

		case REINFORCEMENT_ATTACK_FORTIFICATION_PHASE:


			driver.riskGame_initializeGame();
			driver.riskGame_giveAllCountriesButOneToPlayer(driver.riskGame_getPlayers()[0], driver.riskGame_getPlayers()[1]);
			driver.riskGame_playGame();
			break;

		default:
			break;

	}
	//game.riskGame_start();

	return 0;
}



