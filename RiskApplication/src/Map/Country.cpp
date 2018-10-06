
#define COUNTRY_LOCAL
#include "Country.h"

Country::Country()
{


}


string Country::country_GetName(void)
{
	/** Returns a copy of the country name */
	return string(this->countryName);
}
