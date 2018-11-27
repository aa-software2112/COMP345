
#define TOURNAMENT_LOCAL
#include "Tournament.h"

/** Sets the number of games per map */
void Tournament::tournament_setGamesPerMap(int numberGames)
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

/** Adds the next map to be played (only if maximum wasn't reached) */
void Tournament::tournament_addMap(Map *nextMap)
{
	if (this->maps.size() < MAX_NUM_MAPS)
	{
		this->maps.push_back(nextMap);
	}
}

