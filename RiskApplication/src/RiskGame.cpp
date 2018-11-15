
#define RISK_GAME_LOCAL
#include "RiskGame.h"


/** Set the subject that the observer will listen to;
 *
 * in this case, everytime a new player is making a move, the subject should be set
 * using this function (we need this since we can only have one subject per observer)
 *  */
void RiskGame::riskGame_setSubject(Player *subject)
{
	this->subject = subject;

	this->subject->subject_Attach(this);

}

/** This is the function that is called by the player subject in order
 * to view the state of they player's phase; note the example print statement below
 */
void RiskGame::observer_Update()
{

	cout << this->subject->player_getPlayerName() << endl;
	cout << "In Risk Game Observer: observer_Update()" << endl;
}

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

vector <Player*> RiskGame::riskGame_getPlayers(void)
{
	return this->players;
}

Deck* RiskGame::riskGame_getDeck()
{
	return this->deck;
}

Map* RiskGame::riskGame_getMap()
{
	return this->map;
}

int RiskGame::riskGame_getCardSetsTraded()
{
	return this->numCardSetsTraded;
}

void RiskGame::riskGame_incrementCardSetsTraded()
{
	this->numCardSetsTraded++;
	cout << "The number of card sets traded has incremented. It is now " << numCardSetsTraded << "." <<endl;
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

bool RiskGame::riskGame_checkWinner()
{
	for(unsigned int  i = 0; i < players.size(); i++)
	{
		if(players[i]->player_getMyCountries().size() == this->map->map_GetNumCountries())
			return true;
	}
	return false;
}

bool RiskGame::riskGame_playerTurn(Player* currentPlayer)
{
	/**
	 *  This is where a single player is to take a turn
	 * calling reinforce, attack, and fortification phases -
	 * to be called from the riskGame_playGame() function
	 */
	if(riskGame_checkWinner())
		return true;

	currentPlayer->player_reinforce(this);
	currentPlayer->player_attack(this);
	currentPlayer->player_fortify(this);

	return false;
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

	/** Keep loading maps until a valid one is chosen */
	while(true)
	{
		string mapSelectionString = "Select a map file to load... ";

		int index = UserInterface::userInterface_getIndexOfList((*listOfMapFiles), mapSelectionString);

		this->pathToLoadedMap = (*listOfMapFiles)[index];

		MapLoader mapLoader;

		/** Load the map */
		if ( (this->map = mapLoader.mapLoader_LoadMap(this->pathToLoadedMap)) == NULL)
		{
			print("Could not parse file");
			continue;
		}

		/** Check that map is connected */
		if (!this->map->map_IsValidMap())
		{
			print("MAP IS INVALID - NOT CONNECTED (either whole or subgraph)");
			continue;
		}
		else
		{
			print("MAP IS VALID - CONNECTED, AND ALL CONTINENTS' SUBGRAPHS ARE CONNECTED");
			break;
		}
	}

	/** Destruct */

	delete listOfMapFiles;
	listOfMapFiles = NULL;

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

	print("Deck Size: " + std::to_string(this->deck->deck_getDeckSize()));

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
	cout << "Number of players: " << std::to_string(players.size()) << endl << endl;


	/**
	 *************************
	 *************************
	 *   PLAYER TURN ORDER   *
	 *************************
	 *************************
	 */

	/**Randomize the order of play of the players*/
	srand(time(NULL));

	/** Automatically shuffles the iterator */
	random_shuffle(players.begin(), players.end());


	/**Display the order of all players */
	for(unsigned int i = 0; i < players.size(); i ++){
		cout << "Player #" << i + 1 << " will be " << players[i]->player_getPlayerName() << endl;
	}

	/**
	 *************************
	 *************************
	 *    ASSIGN COUNTRIES   *
	 *************************
	 *************************
	 */

	/** Stores the total number of countries in the map */
	int numCountryLeft = this->map->map_GetNumCountries();

	/** Stores all the countries in the map as a vector */
	vector<Country *> allCountries = this->map->map_GetAllCountries();

	/** While there are not any countries left to assign,
	 * randomly assign countries to each player one by one in a round-robin fashion
	 * */
	while(numCountryLeft != 0){

		for(unsigned int i = 0; i < players.size(); i ++)
		{
			/** All country assignments are done - break */
			if(numCountryLeft == 0)
				break;

			/** Randomly choose the next country to assign to players[i] */
			int countryIndex = rand() % allCountries.size();

			/**
			 * Set owner of country,
			 * Add Country to set of Countries a player owns,
			 * Start the country with 1 army
			 * Remove the country from the list of countries to allocate
			 */
			allCountries[countryIndex]->country_SetOwner(players[i]);
			players[i]->player_addCountry(allCountries[countryIndex]);
			allCountries[countryIndex]->country_SetNumArmies(1);
			allCountries.erase(allCountries.begin()+countryIndex);
			numCountryLeft --;
		}
	}

	cout << endl;

	/** Display owner of each country
	 * The proof of concept is in how the owner (player) is called (through the country itself)
	 * */
	for(int m = 0; m < map->map_GetNumCountries(); m++)
	{
		cout << this->map->map_GetAllCountries()[m]->country_GetName() << " belongs to " << this->map->map_GetAllCountries()[m]->country_GetOwner()->player_getPlayerName() << endl;
	}

	cout << endl;

	/**
	 * Display each player's countries - these
	 * are the set of countries stored within each player -
	 * they should match the previous output
	 *  */
	for(unsigned int i = 0; i < players.size(); i ++)
	{
		cout << players[i]->player_getPlayerName() << "'s Countries: " << endl;

		/** Get all countries owned by the current players[i] */
		vector <Country*> currentPlayerCountries = players[i]->player_getMyCountries();

		/** Display all countries */
		for(unsigned int i = 0; i < currentPlayerCountries.size();i++) {
			cout << currentPlayerCountries[i]->country_GetName() << endl;
		}

		cout << endl << endl;
	}


	/**
	 *************************
	 *************************
	 *    PREPARE ARMIES     *
	 *************************
	 *************************
	 */

	/** The number of armies for each player */
	UINT A;

	/** A boolean array describing when a given player is done placing their armies */
	bool* placedArmiesFlag;

	/** Allocating the number of armies necessary for each player */
	switch(players.size()){
	case 2: A = 40;
			placedArmiesFlag = new bool(2);
			break;
	case 3: A = 35;
			placedArmiesFlag = new bool(3);
			break;
	case 4: A = 30;
			placedArmiesFlag = new bool(4);
			break;
	case 5: A = 25;
			placedArmiesFlag = new bool(5);
			break;
	case 6: A = 20;
			placedArmiesFlag = new bool(6);
			break;
	default: cout << "Error! Invalid number of players.";
			break;
	}

	/** Place army in round-robin fashion */
	bool donePlacingArmies = false;

	while(!donePlacingArmies)
	{
		donePlacingArmies = true;

		/**
		 * Iterate over each player, and add a single army to a country
		 * of their choice
		 */
		for(unsigned int i = 0; i < players.size(); i++)
		{
			/**
			 * If the player has not added "A" number of armies yet,
			 * prompt them to add another one to their set of countries
			 */
			if(players[i]->player_getTotalNumberArmies() - players[i]->player_getMyCountries().size() < A - players[i]->player_getMyCountries().size())
			{
				/**
				 * Display current state of user's countries & armies
				 */
				cout << players[i]->player_getPlayerName() << "'s turn (You have " << A - players[i]->player_getTotalNumberArmies() << " unit(s) left to place!):" << endl;


				for(unsigned int g = 0; g < players[i]->player_getMyCountries().size(); g++)
				{

					cout << "[" << g << "] " << players[i]->player_getMyCountries()[g]->country_GetName() << " Number of Armies: " << players[i]->player_getMyCountries()[g]->country_GetNumArmies() << endl;

				}

				cout << endl;

				/** Prompt user for which country to add an army to */
				string armyPlacing = "Which country would you like to place armies on? (Enter index) ";

				int countryIndex = UserInterface::userInterface_getIntegerBetweenRange(armyPlacing, 0, players[i]->player_getMyCountries().size() - 1);

				/** Add a single army to player's country*/
				players[i]->player_getMyCountries()[countryIndex]->country_SetNumArmies(players[i]->player_getMyCountries()[countryIndex]->country_GetNumArmies() + 1);
			}
			/** Player is done adding armies - set boolean */
			else
			{
				placedArmiesFlag[i] = true;
			}

		}

		/** Check if all players are done */
		for(unsigned int j = 0; j < players.size(); j++)
		{
			if(placedArmiesFlag[j] == false)
				donePlacingArmies = false;
		}

	}

	/** Destruct */
	delete [] placedArmiesFlag;
	placedArmiesFlag = NULL;

	/** Print each player's countries with the number of army placed */
	for(unsigned int i = 0; i < players.size(); i++)
	{
		int armyPlaced = 0;

		cout << players[i]->player_getPlayerName() << ": " << endl;

		/** Get all countries */
		vector <Country*> currentPlayerCountries = players[i]->player_getMyCountries();

		/** Display all countries owned by player, with its number of armies */
		for(unsigned int i = 0; i < currentPlayerCountries.size(); i++)
		{
			cout << currentPlayerCountries[i]->country_GetName() << " - Number of Armies: " << currentPlayerCountries[i]->country_GetNumArmies() << endl;

			armyPlaced += currentPlayerCountries[i]->country_GetNumArmies();
		}

		/** Display that player has placed the right number of armies */
		cout << endl;
		cout << "Total number of army placed by " << players[i]->player_getPlayerName() << ": " << armyPlaced << endl << endl;
	}


}

/** This is the second function called from riskGame_startGame()
 *  to actually play the game of risk. For demo purposes, this function can be called
 *  on its own after the game has been initialized.
 *
 */
void RiskGame::riskGame_playGame(void)
{
	bool winnerFound = false;

	/**
	 *  Keep playing the game until a winner exists;
	 *  a single player owns all countries
	 * */
	while(!winnerFound)
	{
		/** A player takes their turn;
		 * if there is a winner before the player takes their turn,
		 * the game will end
		 */
		for(unsigned int i = 0; i < players.size(); i++)
		{
			winnerFound = riskGame_playerTurn(players[i]);
		}
	}

	/** Find the winning player based on the one with ownership of
	 * all countries */

	Player* winner;

	for(unsigned int j = 0; j < players.size(); j++)
	{
		/** The player that owns all countries is stored */
		if(players[j]->player_getMyCountries().size() == this->riskGame_getMap()->map_GetNumCountries())
		{
			winner = players[j];
			break;
		}

	}

	/** Display the winning player */
	cout << winner->player_getPlayerName() << " has won the game!";
}

/** Last function called from riskGame_startGame(), when game is over
 * (there was a winner) */
void RiskGame::riskGame_closeGame(void)
{
	delete this;
}

/** Displays for each country, its continent, number of armies, and owner */
void RiskGame::riskGame_showStateOfGame()
{

	cout << "Global board:" << endl << endl;

	for(int i = 0; i < this->map->map_GetNumCountries(); i++)
	{
		cout << "[" << i << "] " << this->map->map_GetAllCountries()[i]->country_GetName() << " (" << this->map->map_GetAllCountries()[i]->country_GetContinent()->continent_GetContinentName() << ") - " << this->map->map_GetAllCountries()[i]->country_GetNumArmies() << " army units - " << this->map->map_GetAllCountries()[i]->country_GetOwner()->player_getPlayerName() << endl;
	}

	cout << endl;
}

/** Displays for a given player its owned countries, their continents, number of armies,
 * and the player's name */
void RiskGame::riskGame_showStateOfPlayer(Player* currentPlayer)
{
	cout << currentPlayer->player_getPlayerName() << "'s personal board:" << endl << endl;

	for(unsigned int i = 0; i < currentPlayer->player_getMyCountries().size(); i++)
	{
		cout << "[" << i << "] " << currentPlayer->player_getMyCountries()[i]->country_GetName() << " (" << currentPlayer->player_getMyCountries()[i]->country_GetContinent()->continent_GetContinentName() << ") - " << currentPlayer->player_getMyCountries()[i]->country_GetNumArmies() << " army units - " << currentPlayer->player_getMyCountries()[i]->country_GetOwner()->player_getPlayerName() << endl;
	}

	cout << endl;
}

/** This is a function used for DEMOING purposes only;
 * it gives a single player ownership of all countries so that the functionality of
 * the "player turn" can be shown to allocate a winner immediately.
 */
void RiskGame::riskGame_giveAllCountriesToPlayer(Player* currentPlayer)
{
	/** Iterates over all players */
	for(unsigned int j = 0; j < players.size(); j++)
	{
		/** Iterates over all countries */
		for(unsigned int x = 0; x < map->map_GetNumCountries(); x++)
		{
			/** Removes ownership of all countries from every player */
			players[j]->player_removeCountry(map->map_GetAllCountries()[x]);
		}
	}

	/** Assign all countries to the current player */
	for(unsigned int i = 0; i < map->map_GetNumCountries(); i++)
	{
		currentPlayer->player_addCountry(map->map_GetAllCountries()[i]);
	}
}

/** This is a function used for DEMOING purposes only;
 * it gives a single player ownership of all countries except for one,
 * to show that the game will recognize that there has not been a winner yet
 */
void RiskGame::riskGame_giveAllCountriesButOneToPlayer(Player* firstPlayer, Player* anotherPlayer)
{
	/** Iterates over all players */
	for(unsigned int j = 0; j < players.size(); j++)
	{
		/** Iterates over all countries */
		for(unsigned int x = 0; x < map->map_GetNumCountries(); x++)
		{
			/** Removes ownership of all countries from every player */
			players[j]->player_removeCountry(map->map_GetAllCountries()[x]);
		}
	}


	/** Assign all countries to the current player except for one */
	for(unsigned int i = 0; i < map->map_GetNumCountries() - 1; i++)
	{
		firstPlayer->player_addCountry(map->map_GetAllCountries()[i]);
	}

	/** Assigning the last country to another player */
	anotherPlayer->player_addCountry(map->map_GetAllCountries()[map->map_GetNumCountries() - 1]);

}

