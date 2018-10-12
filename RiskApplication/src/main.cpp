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

int main()
{
	/************************************************
	 *
	 * Map Loader & Graph
	 *
	 ***********************************************/

	/** Change this path to comply with your filesystem (make sure there is a trailing forward slash) */
	string basePathToMapFolder = "C:\\Users\\Anthony Andreoli\\Desktop\\Concordia\\2018 - FALL\\COMP 345\\REPOSITORY\\COMP345\\RiskApplication\\MapFiles/";

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
	if ( (newMap = p.mapLoader_LoadMap(mapFiles[1])) == NULL)
	{
		print("Could not parse file");
		return 0;
	}

	/** Map is of valid format */
	print("Map is valid!");

	/** Display the number of continents */

	print("Map connected?");
	if (newMap->map_IsConnected())
	{
		print("MAP CONNECTED\n");
	}
	else
	{
		print("MAP NOT CONNECTED\n");
	}

	if(newMap->map_AllContinentsConnectedSubgraphs())
	{
		print("ALL CONTINENTS CONNECTED SUBGRAPHS\n");
	}
	else
	{
		print("CONTINENTS NOT ALL CONNECTED SUBGRAPHS\n");
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
	tempPlayer.myDRF.rollDice(1);
	cout << tempPlayer.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer.myDRF.resultsRolled[2] << endl;

	cout << "First player rolls 2 dice" << endl;
	tempPlayer.myDRF.rollDice(2);
	cout << tempPlayer.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer.myDRF.resultsRolled[2] << endl;

	cout << "First player rolls 3 dice" << endl;
	tempPlayer.myDRF.rollDice(3);
	cout << tempPlayer.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer.myDRF.resultsRolled[2] << endl;

	tempPlayer.myDRF.printPlayerDiceStatistics();

	Player tempPlayer2("DiceTester2");

	cout << "Second player rolls 1 die" << endl;
	tempPlayer2.myDRF.rollDice(1);
	cout << tempPlayer2.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[2] << endl;

	cout << "Second player rolls 2 dice" << endl;
	tempPlayer2.myDRF.rollDice(2);
	cout << tempPlayer2.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[2] << endl;

	cout << "Second player rolls 3 dice" << endl;
	tempPlayer2.myDRF.rollDice(3);
	cout << tempPlayer2.myDRF.resultsRolled[0] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[1] << endl;
	cout << tempPlayer2.myDRF.resultsRolled[2] << endl;

	tempPlayer2.myDRF.printPlayerDiceStatistics();


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
			player1.addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player1);
			rotate++;
		} else if (rotate == 1)
		{
			player2.addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player2);
			rotate++;
		}
		else if (rotate == 2) {
			player3.addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player3);
			rotate++;
		}
		else {
			player4.addCountry(allCountries[z]);
			allCountries[z]->country_SetOwner(&player4);
			rotate = 0;
		}
	}
	cout << "For Player 1: " << endl;
	for(unsigned int p = 0; p < player1.collectionOfCountries.size(); p++){
		cout << *(player1.collectionOfCountries[p]) << endl;
	}

	cout << "For Player 2: " << endl;
	for(unsigned int p = 0; p < player2.collectionOfCountries.size(); p++){
		cout << *(player2.collectionOfCountries[p]) << endl;
	}

	/* Changing the number of armies on the first 3 countries so we can test attacking */
	allCountries[0]->country_SetNumArmies(5);
	allCountries[1]->country_SetNumArmies(1);
	allCountries[2]->country_SetNumArmies(1);

	/* Showing the current state of the board (Name of country, number of armies on it and owner) */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->playerName << endl;
	}

	cout << endl;
	cout << endl;

	/* Test the attack function */ /********************************* FIX BUGS IN HERE */
	player1.attack(newMap);


	cout << endl;
	cout << endl;

	/* Show the state of the board after the attack */
	for(unsigned int z = 0; z < allCountries.size(); z++){
		cout << allCountries[z]->country_GetName() << " has " << allCountries[z]->country_GetNumArmies() << " armies and belongs to " << allCountries[z]->country_GetOwner()->playerName << endl;
	}



	/************************************************
	 *
	 * 					Cards (Deck/Hand)
	 *
	 ***********************************************/

	/** Put driver code here */

	/* Creating a deck */
	cout << endl;
	cout << "************************** TESTING CARDS **************************" << endl << endl;
	Deck newDeck(allCountries.size());

	/* Printing type of each card in deck */
	for (int i = 0; i < newDeck.get_numCards(); i++) {

		newDeck.get_deck()[i].printType();

	}

	cout << endl;

	/* Print out the number of cards in the deck */
	cout << "Deck has " << newDeck.get_numCards() << " cards" << endl;

	cout << endl;

	cout << "Drawing top card..." << endl;

	/* Draw the top card of the deck and print out its type */
	newDeck.draw().printType();

	cout << endl;

	/* Print out the new number of cards in the deck after drawing the top card */
	cout << "Deck has " << newDeck.get_numCards() << " cards" << endl;

	/* Manually adding the first 6 cards to player1's hand (not drawing)*/
	player1.myHand.addCardToHand(&newDeck.get_deck()[0]);
	player1.myHand.addCardToHand(&newDeck.get_deck()[1]);
	player1.myHand.addCardToHand(&newDeck.get_deck()[2]);
	player1.myHand.addCardToHand(&newDeck.get_deck()[3]);
	player1.myHand.addCardToHand(&newDeck.get_deck()[4]);
	player1.myHand.addCardToHand(&newDeck.get_deck()[5]);

	/* Display the current cards in player1's hand */
	cout << endl;
	cout << "Player1's hand: " << endl;
	for(unsigned int d = 0; d < player1.myHand.getHandOfCards().size();d++) {
		player1.myHand.getHandOfCards()[d]->printType();
	}
	cout << endl;
	/* Testing the exchange function (trading in cards for armies), this will check the player's
	 * hand for a matching set and will return an integer (number of armies given) based on the total number of sets handed in during the game (variable stored in Map for now) */
	cout << "From player1's current hand, they receive " << player1.exchange(newMap) << " army units." << endl;

	return 0;
}



