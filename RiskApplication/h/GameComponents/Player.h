/*
 * Player.h
 *
 *  Created on: Oct 8, 2018
 *      Author: Rainily
 */

#ifndef RISKAPPLICATION_H_PLAYER_H_
#define RISKAPPLICATION_H_PLAYER_H_

#include <vector>
#include <set>
#include "Utilities.h"
using namespace std;
#include "PhaseStrategy.h"
#include "RiskGame.h"
#include "Country.h"
#include "Map.h"
#include "DiceRollingFacility.h"
#include "Card.h"
#include "Hand.h"
#include "Subject.h"

class Continent;
class RiskGame;

enum phaseType {
	REINFORCE = 0,
	ATTACK = 1,
	FORTIFY = 2
};

/** The player is a subject of some observer; note,
 * you may need to add a few variables to preserve the state of
 * the current phase (to help the observer know what to print);
 * keep it basic (words from Paquet himself)
 *  */
class Player: public Subject {
	public:
		/* Constructors */
		Player();
		Player(string name);

		string player_getPlayerName();
		DiceRollingFacility* player_getMyDRF();
		Hand* player_getMyHand();
		std::vector<Country*> player_getMyCountries();

		/* Returns the total number of armies owned by a player */
		unsigned int player_getTotalNumberArmies(void);
		/* Returns whether a country belongs to a player */
		bool player_checkCountryOwnership(Country* currentCountry);
		/* Returns a set of all unique continents that have countries owned by player */
		set<Continent *> * player_getUniqueContinents(void);
		/* Returns the player who own's a specific country */
		Player player_returnOwner(Country *currentCountry);

		/* Functions called during a player's turn */
		void player_reinforce(RiskGame* currentGame);
		void player_attack(RiskGame* currentGame);
		void player_fortify(RiskGame* currentGame);

		/* Mutators for the player's collection of countries */
		void player_addCountry(Country *newCountry);
		void player_removeCountry(Country *newCountry);
		void player_transferMaxArmy(Country *fromCountry, Country *toCountry);

		/** For setting the strategy of this player */
		void player_setPhaseStrategy(PhaseStrategy *phaseStrategy);

		/** This is an example of how you would attack with the strategy,
		 * you can delete it once you're done with understanding the concept
		 */
		void player_exampleAttackWithStrategy(RiskGame * rg);
		PhaseStrategy* player_getPhaseStrategy();


		void player_setCurrentPhase(phaseType phase);
		phaseType player_getCurrentPhase();


		friend ostream& operator<<(ostream& output, Player& p);

		/** Made a friend so that they may access all attributes of the player,
		 * including private ones
		 */
		friend HumanPhaseStrategy;
		friend AggressivePhaseStrategy;
		friend BenevolentPhaseStrategy;

		/** Members used to hold information that will be passed during phases
		 *
		 */

		// Reinforce
		int totalReinforcementCount;
		Country* reinforcingCountry;
		int amountToReinforce;

		// Attack
		Country* attackingCountry;
		Country* attackedCountry;
		int attackingCountryArmies;
		int attackedCountryArmies;
		bool attackOutcomeVictory;
		bool successfulInvasion;

		// Fortify
		Country* fortifyingCountry;
		Country* fortifiedCountry;
		int fortifyingCountryArmies;
		int fortifiedCountryArmies;
		int amountToFortify;

	private:
		PhaseStrategy *player_PhaseStrategy;
		string myName;	// holds player's name
		DiceRollingFacility myDRF;	// holds player's own dice rolling facility
		Hand myHand;	// holds player's hand of cards
		vector<Country*> myCollectionOfCountries; // holds player's collection of countries
		phaseType currentPhase;
};



#endif /* RISKAPPLICATION_H_PLAYER_H_ */
