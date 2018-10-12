
#define CONTINENT_LOCAL
#include "Continent.h"
#include "Country.h"

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

void Continent::continent_AddLinkToVertex(Graph<Country, string>::Vertex * vertex)
{
	/** Vertex not found */
	if (mapOfVerticesOfContinent.find( (*(*vertex).vertex_GetElementPtr()).country_GetName()) == mapOfVerticesOfContinent.end())
	{
		mapOfVerticesOfContinent[(*(*vertex).vertex_GetElementPtr()).country_GetName()] = vertex;

	}

}

UINT Continent::continent_GetNumberOfCountries(void)
{
	return mapOfCountries.size();
}

set<Graph<Country, string>::Vertex *> Continent::continent_GetVerticesAsSet(void)
{
	set<Graph<Country, string>::Vertex *> vertices;

	for (map<string,Graph<Country, string>::Vertex*>::iterator it=mapOfVerticesOfContinent.begin(); it!=mapOfVerticesOfContinent.end(); ++it)
	{
		vertices.insert((it->second));
	}

	return vertices;

}

void Continent::continent_DisplayCountries(void)
{
	for (map<string,Country*>::iterator it=mapOfCountries.begin(); it!=mapOfCountries.end(); ++it)
	{
		cout << (*(it->second)) << endl;
	}
}


string Continent::continent_GetContinentName(void)
{
	return this->continentName;
}

ostream &operator<<(ostream& strm, const Continent& continent)
{

	strm << "CONTINENT_NAME: " << continent.continentName << " BONUS_VALUE: " << continent.bonusValue << "\n" ;
	return strm;

}

