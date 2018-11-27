/*
 * TOURNAMENT.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_TOURNAMENT_H_
#define H_TOURNAMENT_H_

#include <vector>
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
	Tournament()
	{

		/** Stores the number of players in the tournament */
		this->tournamentPlayers = 0;

		/** Stores the number of games to be player per map -
		 * the same value across all maps
		 * */
		this->gamesPerMap = 0;

		/** Stores the number of turns currently played in a single game */
		this->turnsPlayed = 0;

		/** Stores the maximum number of turns in a game */
		this->maxNumTurns = 0;

	}
	~Tournament();

	void tournament_setGamesPerMap(int numberGames);

	void tournament_addMap(Map *nextMap);


	/** Threshold values */
	const int MIN_NUM_MAPS = 1;
	const int MAX_NUM_MAPS = 5;

	const int MIN_NUM_PLAYERS = 2;
	const int MAX_NUM_PLAYERS = 4;

	const int MIN_NUM_TURNS = 10;
	const int MAX_NUM_TURNS = 50;

	const int MIN_NUM_GAMES = 1;
	const int MAX_NUM_GAMES = 5;


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

		}

	private:
		Map *mapPlayed;
		Player *winner;
		int gameId;


	};

private:
	/** Stores all the games played */
	vector<Tournament::Game *> games;

	/** Stores all the maps to be played on */
	vector<Map *> maps;

	/** Stores the number of players in the tournament */
	int tournamentPlayers;

	/** Stores the number of games to be player per map -
	 * the same value across all maps
	 * */
	int gamesPerMap;

	/** Stores the number of turns currently played in a single game */
	int turnsPlayed;

	/** Stores the maximum number of turns in a game */
	int maxNumTurns;


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
