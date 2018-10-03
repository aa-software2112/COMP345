

#define UTILITIES_LOCAL
#include "Utilities.h"

/** Prints a string */
void print(const std::string& str)
{

	std::cout << str << std::endl;

}

void print(std::vector<std::string> & vector)
{
	/** Parse results */
	for (std::vector<std::string>::iterator it = vector.begin(); it != vector.end(); it++)
	{
		std::cout << *it << "\n";
	}
}

/** Splits a string by delimiter and stores tokens in container vector */
void splitString(std::string& stringToSplit, std::string& delimiter, std::vector<std::string>& container)
{
	/** Clear the vector */
	container.erase(container.begin(), container.end());

	int startIndex = 0;
	int foundIndex = stringToSplit.find(delimiter, startIndex);

	while (foundIndex != std::string::npos)
	{
		/** Delimiter was found starting at foundIndex */
		container.push_back( stringToSplit.substr( startIndex, ( foundIndex - startIndex ) ) );

		startIndex = foundIndex + delimiter.length();

		foundIndex = stringToSplit.find(delimiter, startIndex);

	}


}
