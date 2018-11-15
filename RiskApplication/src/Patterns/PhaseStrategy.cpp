
#define PHASE_STRATEGY_LOCAL
#include "PhaseStrategy.h"
#include "Player.h"
#include "RiskGame.h"

/** Implement the following functions for Human attacks,
 * reinforcements and fortifications
 * */
void HumanPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	cout << "IN HumanPhaseStrategy::phaseStrategy_Attack()" << endl;

	return;
}

void HumanPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	return;
}

void HumanPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	return;
}

/** Implement the following functions for Aggressive attacks,
 * reinforcements and fortifications
 * */
void AggressivePhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{

	return;
}

void AggressivePhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	return;
}

void AggressivePhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	return;
}

/** Implement the following functions for Benevolent attacks,
 * reinforcements and fortifications
 * */
void BenevolentPhaseStrategy::phaseStrategy_Attack(Player * p, RiskGame * rg)
{
	return;
}

void BenevolentPhaseStrategy::phaseStrategy_Reinforce(Player * p, RiskGame * rg)
{
	return;
}

void BenevolentPhaseStrategy::phaseStrategy_Fortify(Player * p, RiskGame * rg)
{
	return;
}

