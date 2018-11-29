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
#include "Subject.h"
#include "Observer.h"
#include "GameStatisticsObserver.h"
#include "Tournament.h"
using namespace std;

class RiskGame: public Observer {

public:
	RiskGame();
	~RiskGame();
	void riskGame_start(void);
	vector<Player *> riskGame_getPlayers(void);
	Map* riskGame_getMap();
	Deck* riskGame_getDeck();
	int riskGame_getCardSetsTraded();
	void riskGame_incrementCardSetsTraded();
	bool riskGame_checkWinner();
	void riskGame_showStateOfGame();
	void riskGame_showStateOfPlayer(Player* currentPlayer);

	/* Temporarily making these functions public to create drivers */
	void riskGame_initializeGame(void);
	void riskGame_playGame(void);
	void riskGame_closeGame(void);
	bool riskGame_playerTurn(Player* currentPlayer);

	/** Tournament functions */
	void riskGame_tournamentInitializeGame(void);
	void riskGame_tournamentPlayGame(void);
	void riskGame_tournamentCloseGame(void);

	void riskGame_giveAllCountriesToPlayer(Player *currentPlayer);
	void riskGame_giveAllCountriesButOneToPlayer(Player *firstPlayer, Player *anotherPlayer);

	virtual void observer_Update(void);
	void riskGame_setSubject(Player *subject);
	void riskGame_removeObserver(Player *subject);

	/** Create the observer, and set its subject - the game's map */
	GameStatisticsObserver statsObserver;

	/** This should be changed depending on where game is compiled
	 * */
	string pathToMapFiles;
private:
	/** The reference to the player subject */
	Player *subject;

	/** Stores the map associated with the current game */
	Map * map;

	/** Holds instance to the players in the game */
	vector<Player *> players;

	/** Holds the game deck */
	Deck * deck;

	/** Number of card sets traded */
	int numCardSetsTraded;

	/** Tournament object */
	Tournament *tournament;

	/** Boolean that tracks the staet of game - either tournament, or non-tournament */
	bool playingTournament = false;

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
