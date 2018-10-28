
#define RISK_GAME_LOCAL
#include "RiskGame.h"

RiskGame::RiskGame()
{
	this->map = NULL;

	this->deck = NULL;

	numCardSetsTraded = 0;

}

RiskGame::~RiskGame()
{

	delete this->map;
	delete this->deck;

	this->map = NULL;
	this->deck = NULL;
}

/** All steps of the game are called from here - the only public API
 * available to the user
 * */
void RiskGame::riskGame_start(void)
{
	/** Intermediary code may be added if necessary */

	this->riskGame_initializeGame();

	this->riskGame_playGame();

	this->riskGame_closeGame();
}

void riskGame_playerTurn(void)
{
	/**
	 *  This is where a single player is to take a turn
	 * calling reinforce, attack, and fortification phases -
	 * to be called from the riskGame_playGame() function
	 */


}

void RiskGame::riskGame_initializeGame(void)
{
	/**
	 *************************
	 *************************
	 * 		MAP SELECTION	 *
	 *************************
	 *************************
	 */

	vector<string> * listOfMapFiles = Directory::directory_GetAllFilesInDirectory(this->pathToMapFiles, this->mapFileExtension);

	string mapSelectionString = "Select a map file to load... ";

	int index = UserInterface::userInterface_getIndexOfList((*listOfMapFiles), mapSelectionString);

	this->pathToLoadedMap = (*listOfMapFiles)[index];

	/** Destruct */

	delete listOfMapFiles;
	listOfMapFiles = NULL;

	/**
	 *************************
	 *************************
	 * 		MAP LOADING  	 *
	 *************************
	 *************************
	 */

	MapLoader mapLoader;

	/** Load the map */
	if ( (this->map = mapLoader.mapLoader_LoadMap(this->pathToLoadedMap)) == NULL)
	{
		print("Could not parse file");
		return;
	}

	/** Check that map is connected */
	if (!this->map->map_IsValidMap())
	{
		print("MAP IS INVALID - NOT CONNECTED (either whole or subgraph)");
		return;
	}
	else
	{
		print("MAP IS VALID - CONNECTED, AND ALL CONTINENTS' SUBGRAPHS ARE CONNECTED");
	}

	/**
	 *************************
	 *************************
	 *    PLAYER CREATION    *
	 *************************
	 *************************
	 */

	string numPlayersMessage = "Select a number of player [" + std::to_string(MIN_NUM_PLAYERS) +  " - " + std::to_string(MAX_NUM_PLAYERS) + "] ...";

	int numPlayers = UserInterface::userInterface_getIntegerBetweenRange(numPlayersMessage, MIN_NUM_PLAYERS, MAX_NUM_PLAYERS);

	string playerNameMessage;

	/** Create all players and get their names */
	for (int i = 0; i<numPlayers; i++)
	{
		playerNameMessage = "Select a name for player " + std::to_string(i+1) + " ...";

		this->players.push_back(new Player(  UserInterface::userInterface_getString(playerNameMessage)  ));
	}

	/**
	 *************************
	 *************************
	 *     DECK CREATION     *
	 *************************
	 *************************
	 */

	/** Create the deck */
	this->deck = new Deck(this->map->map_GetNumCountries());

	/** Display number of countries and deck size (they should be equal) */
	print("Number of countries: " + std::to_string(this->map->map_GetNumCountries()));

	print("Deck Size: " + std::to_string(this->deck->get_numCards()));

	print ("Deck Cards:");

	cout << *(this->deck) << endl;


	/**
	 *************************
	 *************************
	 *   OUTPUT... PROOF OF  *
	 *   CONCEPT             *
	 *************************
	 *************************
	 */

	/** Return size of player vector */
	print("Number of players: " + std::to_string(players.size()));

	/** Display all players */
	for(vector<Player *>::iterator it = players.begin(); it<players.end(); it++)
	{
		cout << "\t" << *(*it);

	}


	/**
	 *************************
	 *************************
	 *   PLAYER TURN ORDER   *
	 *************************
	 *************************
	 */


	/**
	 *************************
	 *************************
	 *    ASSIGN COUNTRIES   *
	 *************************
	 *************************
	 */



	/**
	 *************************
	 *************************
	 *    PREPARE ARMIES     *
	 *************************
	 *************************
	 */




}

void RiskGame::riskGame_playGame(void)
{

}

void RiskGame::riskGame_closeGame(void)
{

}


