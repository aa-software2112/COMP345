
#define CONTINENT_LOCAL
#include "Continent.h"

Continent::Continent(string continentName, int bonusValue)
{
	this->continentName = continentName;
	this->bonusValue = bonusValue;

}

ostream &operator<<(ostream& strm, const Continent& continent)
{

	strm << "CONTINENT_NAME: " << continent.continentName << " BONUS_VALUE: " << continent.bonusValue << "\n" ;
	return strm;

}
