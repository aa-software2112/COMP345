/*
 * PHASE_STRATEGY.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_PHASE_STRATEGY_H_
#define H_PHASE_STRATEGY_H_

#include "Utilities.h"
using namespace std;

class RiskGame;
class Player;

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/
class PhaseStrategy {

	/** The methods to override (and provide a definition for) as this
	 * PhaseStrategy class is abstract
	 */
public:
	/** The player class "this" must be passed as an argument as this function is not
	 * part of the player class (it cannot access the members of player through this->player_attribute)
	 */
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg) = 0;
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg) = 0;
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg) = 0;

};

class RandomPhaseStrategy: public PhaseStrategy {

public:
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg);

};

class CheaterPhaseStrategy: public PhaseStrategy {

public:
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg);

};

class HumanPhaseStrategy: public PhaseStrategy {

public:
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg);

};

class AggressivePhaseStrategy: public PhaseStrategy {

public:
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg);

};

class BenevolentPhaseStrategy: public PhaseStrategy {

public:
	virtual void phaseStrategy_Attack(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Reinforce(Player * p, RiskGame * rg);
	virtual void phaseStrategy_Fortify(Player * p, RiskGame * rg);

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
 * exposed to other source files where PHASE_STRATEGY_LOCAL isn't defined.
 * */
#ifdef PHASE_STRATEGY_LOCAL


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



#endif /* H_PHASE_STRATEGY_H_ */
