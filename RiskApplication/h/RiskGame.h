/*
 * RISK_GAME.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_RISK_GAME_H_
#define H_RISK_GAME_H_

#include "Utilities.h"
#include "Directory.h"
#include "UserInterface.h"
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Deck.h"
using namespace std;

class RiskGame {

public:
	RiskGame();
	~RiskGame();
	void riskGame_start(void);

private:
	void riskGame_initializeGame(void);
	void riskGame_playGame(void);
	void riskGame_closeGame(void);
	void riskGame_playerTurn(void);

	/** Stores the map associated with the current game */
	Map * map;

	/** Holds instance to the players in the game */
	vector<Player *> players;

	/** Holds the game deck */
	Deck * deck;

	/** Number of card sets traded */
	int numCardSetsTraded;

	/** This should be changed depending on where game is compiled
	 * */
	string pathToMapFiles = "C://Users//Anthony Andreoli//Desktop//Concordia//2018 - FALL//COMP 345//REPOSITORY//COMP345//RiskApplication//MapFiles/";
	string pathToLoadedMap;
	string mapFileExtension = ".map";



};

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

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
 * exposed to other source files where RISK_GAME_LOCAL isn't defined.
 * */
#ifdef RISK_GAME_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/
#define	MIN_NUM_PLAYERS		2
#define MAX_NUM_PLAYERS		6
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



#endif /* H_RISK_GAME_H_ */
