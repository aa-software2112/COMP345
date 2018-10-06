
#define CONTINENT_LOCAL
#include "Continent.h"

Continent::Continent(string continentName, int bonusValue)
{
	this->continentName = continentName;
	this->bonusValue = bonusValue;

}

void Continent::continent_AddLinkToCountry(Country * country)
{
	/** Country has not yet been linked to this continent */
	if (mapOfCountries.find(country->country_GetName()) == mapOfCountries.end())
	{
		mapOfCountries[country->country_GetName()] = country;
	}

}

ostream &operator<<(ostream& strm, const Continent& continent)
{

	strm << "CONTINENT_NAME: " << continent.continentName << " BONUS_VALUE: " << continent.bonusValue << "\n" ;
	return strm;

}

