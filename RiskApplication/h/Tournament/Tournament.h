/*
 * TOURNAMENT.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_TOURNAMENT_H_
#define H_TOURNAMENT_H_

#include <vector>
#include <set>
#include "Utilities.h"
using namespace std;

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/
class Game;
class Player;
class Map;

class Tournament
{

public:
	Tournament();
	~Tournament();

	void tournament_setGamesPerMap(UINT numberGames);

	void tournament_setNumTurns(UINT numTurns);

	void tournament_addMap(Map *nextMap);

	void tournament_addPlayer(Player *player);

	void tournament_setNumMaps(UINT numMaps);

	void tournament_setNumPlayers(UINT numPlayers);

	bool tournament_allMapsSelected(void);

	bool tournament_allPlayersSet(void);

	bool tournament_allMapsPlayed(void);

	void tournament_loadNextMap(void);

	void tournament_pregamesSetup(void);

	/** Threshold values */
	const UINT MIN_NUM_MAPS = 1;
	const UINT MAX_NUM_MAPS = 5;

	const UINT MIN_NUM_PLYRS = 2;
	const UINT MAX_NUM_PLYRS = 4;

	const UINT MIN_NUM_TURNS = 10;
	const UINT MAX_NUM_TURNS = 50;

	const UINT MIN_NUM_GAMES = 1;
	const UINT MAX_NUM_GAMES = 5;


	class Game
	{
		Game(Map *map, int gameNumber)
		{
			/** The map playing on */
			this->mapPlayed = map;

			/** No winner yet */
			this->winner = NULL;

			/** Store the game id - gameId/TotalNumberGamesPerMap */
			this->gameId = gameNumber;

			/** Stores the number of turns currently played in a single game */
			this->turnsPlayed = 0;

		}

	private:
		Map *mapPlayed;
		Player *winner;
		int turnsPlayed;
		int gameId;


	};

private:
	/** Stores all the games played */
	vector<Tournament::Game *> games;

	/** Stores all the maps to be played on */
	vector<Map *> unplayedMaps;

	/** Maps that have been completely played on (over all turns) */
	vector<Map *> playedMaps;

	/** Current game being played */
	Tournament::Game * currentGame;

	/** The current map being played on */
	Map * currentMap;

	/** All players in tournament */
	vector<Player *> players;

	/** Stores the number of players in the tournament */
	UINT tournamentPlayers;

	/** Stores the number of maps */
	UINT numMaps;

	/** Stores the number of games to be player per map -
	 * the same value across all maps
	 * */
	UINT gamesPerMap;

	/** Stores the maximum number of turns in a game */
	UINT maxNumTurns;

	/** Stores the number of players */
	UINT numPlayers;

	/** Stores the total number of turns per game */
	UINT numTurns;

	/** Stores the number of games remaining to be played */
	UINT gamesLeftForCurrentMap;


};

/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where TOURNAMENT_LOCAL isn't defined.
 * */
#ifdef TOURNAMENT_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_TOURNAMENT_H_ */