
#include "GameStatisticsObserver.h"
#define GAME_STATISTICS_OBSERVER_LOCAL
#include "Player.h"

void GameStatisticsObserver::gameStatObs_setSubject(Map *m)
{

	/** Sets the subject that this observer will monitor */
	this->subject = m;

	/** Sets the observer in the subject */
	this->subject->subject_Attach(this);

	cout << "Set subject!" << endl;

}

/** Function should call the appropriate map function that will
 * obtain necessary map function in order to display the player
 * ownership of the entire map
 */
void GameStatisticsObserver::observer_Update(void)
{
	/** Obtain the player:country map */
	map<Player *, vector<Country *> *> * playerToCountryMap = this->subject->map_GetPlayerToCountryMapping();

	/** Tracks the total countries in play */
	int totalCountries = 0;

	/** Stores the total countries per player */
	map<Player *, int> playerCountriesOwned;

	/** Iterate through the playerToCountryMap, and extract the percentages */
	/** Iterate through each country */
	for(map<Player *, vector<Country *> *>::iterator it = (*playerToCountryMap).begin(); it != (*playerToCountryMap).end(); it++)
	{
		/** Store the number of countries owned by player */
		playerCountriesOwned[it->first] = it->second->size();

		/** Store the number of total countries */
		totalCountries += it->second->size();

	}

	/** Values to be used everytime the function is called */
	int nameWidth = 10;
	int percentWidth = 6;
	int numDecimals = 2;

	std::setprecision(numDecimals);

	cout << std::setw(nameWidth) << "Player|" << std::setw(percentWidth) << "%" << "\n";

	/** Display the ownership of each player */
	for(map<Player *, int>::iterator it = playerCountriesOwned.begin(); it != playerCountriesOwned.end(); it++)
	{
		cout << std::setw(nameWidth) << it->first->player_getPlayerName() + "|" << std::setw(percentWidth) << (((double) it->second)/totalCountries)*100 << "\n";

	}

	/** If there is only one player, display the winning message
	 */
	if (playerToCountryMap->size() == 1)
	{
		cout << "Congratulations, you are the last remaining player! You won!" << endl;
	}




}

