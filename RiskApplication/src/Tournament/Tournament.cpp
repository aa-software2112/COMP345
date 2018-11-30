
#define TOURNAMENT_LOCAL
#include "Tournament.h"
#include "Country.h"
#include "Player.h"

/** Constructor */
Tournament::Tournament(void)
{

	/** Stores the number of players in the tournament */
	this->tournamentPlayers = 0;

	/** Stores the number of games to be player per map -
	 * the same value across all maps
	 * */
	this->gamesPerMap = 0;

	this->numMaps = 0;

	this->numPlayers = 0;

	this->numTurns = 0;

	this->currentMap = NULL;

	this->gamesLeftForCurrentMap = 0;

}

/** Sets the number of games per map */
void Tournament::tournament_setGamesPerMap(UINT numberGames)
{
	if (numberGames < MIN_NUM_GAMES)
	{
		this->gamesPerMap = MIN_NUM_GAMES;
	}
	else if (numberGames > MAX_NUM_GAMES)
	{
		this->gamesPerMap = MAX_NUM_GAMES;
	}
	else
	{
		this->gamesPerMap = numberGames;
	}
}

/** Sets the number of total maps */
void Tournament::tournament_setNumMaps(UINT numMaps)
{
	if (numMaps < MIN_NUM_MAPS)
	{
		this->numMaps = MIN_NUM_MAPS;
	}
	else if (numMaps > MAX_NUM_MAPS)
	{
		this->numMaps = MAX_NUM_MAPS;
	}
	else
	{
		this->numMaps = numMaps;
	}
}

/** Sets the number of total turns */
void Tournament::tournament_setNumTurns(UINT numTurns)
{
	if (numTurns < MIN_NUM_TURNS)
	{
		this->numTurns = MIN_NUM_TURNS;
	}
	else if (numTurns > MAX_NUM_TURNS)
	{
		this->numTurns = MAX_NUM_TURNS;
	}
	else
	{
		this->numTurns = numTurns;
	}
}




/** Sets the number of players */
void Tournament::tournament_setNumPlayers(UINT numPlayers)
{
	if (numPlayers < MIN_NUM_PLYRS)
	{
		this->numPlayers = MIN_NUM_PLYRS;
	}
	else if (numPlayers > MAX_NUM_PLYRS)
	{
		this->numPlayers = MAX_NUM_PLYRS;
	}
	else
	{
		this->numPlayers = numPlayers;
	}
}

/** Adds the next map to be played (only if maximum wasn't reached) */
void Tournament::tournament_addMap(Map *nextMap)
{
	if ((this->unplayedMaps.size() < MAX_NUM_MAPS) && (nextMap != NULL))
	{
		this->unplayedMaps.push_back(nextMap);
	}
}

/** Adds a player */
void Tournament::tournament_addPlayer(Player *player)
{
	if ((this->players.size() < MAX_NUM_PLYRS) && (player != NULL))
	{
		this->players.push_back(player);
	}
}

/** Sets the current map as played */
void Tournament::tournament_setMapAsPlayed(void)
{
	if (this->currentMap != NULL)
	{
		/** Sets the current map as played */
		this->playedMaps.push_back(this->currentMap);
	}
}

/** True if all maps have been played on, false otherwise */
bool Tournament::tournament_allMapsPlayed(void)
{
	return this->unplayedMaps.size() == 0;
}

bool Tournament::tournament_allMapsSelected(void)
{

	return this->unplayedMaps.size() == this->numMaps;

}

bool Tournament::tournament_allPlayersSet(void)
{
	return this->players.size() == this->numPlayers;


}


/** Sets up the data necessary before the start of all the games
 * of a current map
 * 1. Set the number of remaining games to the "games per map"
 */
void Tournament::tournament_pregamesSetup(void)
{
	this->gamesLeftForCurrentMap = this->gamesPerMap;

	cout << "Pregame Setup: Num Games To Play: " << this->gamesLeftForCurrentMap << endl;
}

/** Checks if all the games were played in the current round */
bool Tournament::tournament_allGamesPlayed(void)
{
	return this->gamesLeftForCurrentMap == 0;
}

/** Checks if there are turns left */
bool Tournament::tournament_turnsLeft(void)
{
	cout << "Number of turns played: " << this->currentGame->game_getTurnsPlayed() << endl;
	cout << "Number of turns total: " << this->numTurns << endl;


	return this->currentGame->game_getTurnsPlayed() < this->numTurns;
}

/** Checks if some player has won the game */
bool Tournament::tournament_winnerExists(void)
{
	return this->currentGame->game_winnerExists();
}

/** Sets the winning player */
void Tournament::tournament_setWinner(Player *winner)
{
	this->currentGame->game_setWinner(winner);
}

/** A turn was played, set appropriate values */
void Tournament::tournament_turnPlayed(void)
{
	this->currentGame->game_incrementTurnsPlayed();
}

/** Returns the current map */
Map * Tournament::tournament_getCurrentMap(void)
{
	return this->currentMap;
}

/** Ends the current game
 * 1. Sets the game as a "draw" if there was no winner
 * 2. Stores the current game in the vector of games
 * 3. Resets all players
 * 4. Resets the map
 * */
void Tournament::tournament_endGame(void)
{
	cout << "Ending game" << endl;

	/** Sets draw if there was no winner */
	this->currentGame->game_setDrawOrWinner();

	cout << "Set draw or winnder done" << endl;

	/** Stores the current game */
	games.push_back(this->currentGame);

	cout << "Pushed game to list" << endl;

	/** 1. Resets all the players
	 * 2. Resets Map
	 *
	 */
	for(UINT p = 0; p<this->players.size(); p++)
	{
		this->players[p]->player_Reset();

		cout << "Reset player " << p << endl;
	}

	this->currentMap->map_Reset();

	cout << "Reset map" << endl;

	/** Decrement remaining games to be played */
	this->gamesLeftForCurrentMap--;

	cout << "Decremented games left to play" << endl;

}

/** Start a new game
 * 1. Create a new game
 * 2. Set the new game as the current game
 * 3. Assign all countries of map to each player
 * 4. Assign all armies
 */
void Tournament::tournament_startNewGame(void)
{

	/** Create the new game */
	Game * newGame = new Game(this->currentMap, this->gamesPerMap - this->gamesLeftForCurrentMap + 1);

	/** Store it as the current game */
	this->currentGame = newGame;


	/**
	 *************************
	 *************************
	 *    ASSIGN COUNTRIES   *
	 *************************
	 *************************
	 */

	/** Stores the total number of countries in the map */
	int numCountryLeft = this->currentMap->map_GetNumCountries();

	/** Stores all the countries in the map as a vector */
	vector<Country *> allCountries = this->currentMap->map_GetAllCountries();

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

	/**
	 *************************
	 *************************
	 *    PREPARE ARMIES     *
	 *************************
	 *************************
	 */

	/** The number of armies for each player */
	int A;

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


	cout << "Number of armies to place: " << A << endl;

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

			cout << "Total armies for player: " << players[i]->player_getTotalNumberArmies();
			cout << "Number of countries for player: " << players[i]->player_getMyCountries().size();



			/**
			 * If the player has not added "A" number of armies yet,
			 * prompt them to add another one to their set of countries
			 */
			if(players[i]->player_getTotalNumberArmies() - players[i]->player_getMyCountries().size() < A)
			{
				/**
				 * Display current state of user's countries & armies
				 */
				cout << players[i]->player_getPlayerName() << "'s turn (You have " << A - (players[i]->player_getTotalNumberArmies() - players[i]->player_getMyCountries().size()) << " unit(s) left to place!):" << endl;


				for(unsigned int g = 0; g < players[i]->player_getMyCountries().size(); g++)
				{

					cout << "[" << g << "] " << players[i]->player_getMyCountries()[g]->country_GetName() << " Number of Armies: " << players[i]->player_getMyCountries()[g]->country_GetNumArmies() << endl;

				}

				cout << endl;

				/** Prompt user for which country to add an army to */
				string armyPlacing = "Which country would you like to place armies on? (Enter index) ";

				/** Randomly select a country to set an army in */
				int countryIndex = rand() % players[i]->player_getMyCountries().size();

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




}



/**
 * This function is responsible for loading the next map to
 * be played on
 */
void Tournament::tournament_loadNextMap(void)
{
	if (this->unplayedMaps.size() > 0)
	{
		/** Add the next unplayed map to the current map */
		this->currentMap = this->unplayedMaps.front();

		/** Remove the map from the unplayed vector */
		this->unplayedMaps.erase(this->unplayedMaps.begin());

		cout << "Moving to next map" << endl;
	}

}

/** This function displays the outcome of all the games
 * played in the tournament. The following steps are required
 * to display the appropriate match statistics
 * 0. Display a row representing the "Game #" by using the "gamesPerMap" variable (see assignment for table with this row as a reference)
 * 1. Iterate over all maps
 * 	1.1 Display the map name
 * 2. For each map, iterate over the number of games per map
 * (i.e. for the first map, if the number of games per map is 3, display games 0 -> 2,
 * and for the second map, display games 3 - > 5, and so on)
 * 3. For each game display
 * 	3.1 The player's behavior that won (if winner != NULL)
 * 	3.2 "DRAW" if there was no winner (winner == NULL)
 *
 */
void Tournament::tournament_displayTournament(void)
{

	cout << "Displaying tournament" << endl;

	const char dash = '-';
	const char space = ' ';
	const int width1 = 40;
	const int width2 = 15;
	/** 0. Display the first row here <Blank Spaces> <Game 1> <Game 2> ... <Game this->gamesPerMap> */

	cout << "\n+"<< setw(width1+this->gamesPerMap*width2 + this->gamesPerMap*2 + 3) << setfill(dash)<<"+\n"<< left << setw(width1+2) << setfill(space) << "|";
	for (unsigned int i=1; i<=gamesPerMap; i++){
		cout << left << setw(width2)  << "| GAME " << i << setfill(space) << " ";
	}
	cout << "|\n"<< setw(width1+this->gamesPerMap*width2 + this->gamesPerMap*2 + 2)<< setfill(dash) << "+";
	cout << "+" << endl;

	/** 1. Iterate over all maps */
	for (UINT mapIndex = 0; mapIndex < this->playedMaps.size(); mapIndex++)
	{
		/** Use this map for displaying purposes */
		Map * mapToDisplay = this->playedMaps[mapIndex];

		/** 1.1 Display the map name here (use function in map class --> map_GetMapName())
		 * Must be displayed as the row name (see the assignment table as a reference)
		 * */
		cout << "| "<< left << setw(width1) << setfill(space) << mapToDisplay-> map_GetMapName();

		/** The first game of the current map */
		UINT gameNumber = mapIndex*this->gamesPerMap;

		/** 2. Iterate over all games for the given map */
		for( ; gameNumber < mapIndex*this->gamesPerMap + this->gamesPerMap; gameNumber++)
		{

			/** The game to display */
			Game * gameToDisplay = this->games[gameNumber];

			/** 3, 3.1, 3.2,
			 * use both gameToDisplay-> game_wasADraw() to see if game was a draw, otherwise use
			 * gameToDisplay->game_getWinner() to get the player and display its behavior
			 *
			 * If you use game_getWinner(), you will get a player (if there was a winner), and using this player,
			 * call player->player_behaviorName() to get the string associated with the behavior type {AGGRESSIVE, CHEATER, ...}
			 *
			 * Display the player's behavior that won - or display DRAW here
			 *
			 * */
			if (gameToDisplay->game_wasADraw()==true){
				cout << "| " << left << setw(width2) << setfill(space) << "DRAW";
			}
			else
				cout << "| " << left << setw(width2) << setfill(space) << gameToDisplay->game_getWinner()->player_behaviorName();
		}
		cout << "|"<< endl;
	}
	cout << setw(width1+this->gamesPerMap*width2 + this->gamesPerMap*2 + 2) << setfill(dash) << "+";
	cout << "+" << endl;





}

