
#define TOURNAMENT_LOCAL
#include "Tournament.h"

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
