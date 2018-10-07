
#define COUNTRY_LOCAL
#include "Country.h"


Country::Country(void)
{
	/** Country now points to a continent */
	this->parentContinent = NULL;

	/** Store the x & y coordinate of the country */
	this->xCoordinate = 0;

	this->yCoordinate = 0;

	this->numArmies = 0;

	/** Store the country name */
	this->countryName = "";

}

Country::Country(string countryName) // @suppress("Class members should be properly initialized")
{
	/** Country now points to a continent */
	this->parentContinent = NULL;

	/** Store the x & y coordinate of the country */
	this->xCoordinate = 0;

	this->yCoordinate = 0;

	this->numArmies = 0;


	/** Store the country name */
	this->countryName = countryName;
}


Country::Country(Continent *linkContinent, string countryName, UINT xCoordinate, UINT yCoordinate )
{
	/** Country now points to a continent */
	this->parentContinent = linkContinent;
	this->parentContinent->continent_AddLinkToCountry(this);

	/** Store the x & y coordinate of the country */
	this->xCoordinate = xCoordinate;

	this->yCoordinate = yCoordinate;

	/** Store the country name */
	this->countryName = countryName;

	this->numArmies = 0;

}


string Country::country_GetName(void)
{
	/** Returns a copy of the country name */
	return string(this->countryName);
}

void Country::country_SetNumArmies(UINT numArmies)
{
	this->numArmies = numArmies;
}

void Country::country_SetXCoordinate(UINT x)
{
	this->xCoordinate = x;
}

void Country::country_SetYCoordinate(UINT y)
{
	this->yCoordinate = y;
}

void Country::country_SetContinent(Continent * linkContinent)
{

	this->parentContinent = linkContinent;
	this->parentContinent->continent_AddLinkToCountry(this);

}

ostream &operator<<(ostream& strm, const Country& country)
{

	strm << "COUNTRY_NANE: " << country.countryName << " (x, y): " << "(" << \
			country.xCoordinate << ","  << country.yCoordinate << ") CONTINENT: " << (*(country.parentContinent)).continent_GetContinentName() << " ARMIES: " << \
			country.numArmies << "\n" ;
	return strm;

}

