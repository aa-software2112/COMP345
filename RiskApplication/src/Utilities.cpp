

#define UTILITIES_LOCAL
#include "Utilities.h"

void removeLeadingWhitespace(std::string& stringToParse)
{
	size_t firstIndexOfNonWhitespace = stringToParse.find_first_not_of(" ");

	/** Found a character that is a non-whitespace at the start of string */
	if (firstIndexOfNonWhitespace != std::string::npos)
	{
		stringToParse = stringToParse.substr(firstIndexOfNonWhitespace, (stringToParse.size() - firstIndexOfNonWhitespace));

	}

}


void removeTrailingWhitespace(std::string& stringToParse)
{
	size_t lastIndexOfNonWhitespace = stringToParse.find_last_not_of(" ");

	/** Found a character that is a non-whitespace at the end of the string */
	if (lastIndexOfNonWhitespace != std::string::npos)
	{
		stringToParse = stringToParse.substr(0, (lastIndexOfNonWhitespace + 1));

	}

}

void removeEdgeWhitespace(std::string& stringToParse)
{

	/** Removes leading and trailing whitespace */
	removeLeadingWhitespace(stringToParse);
	removeTrailingWhitespace(stringToParse);

}

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
    if (delimiter == "") return;

	/** Clear the vector */
	container.erase(container.begin(), container.end());

    /** temporary string */
    std::string tempString;

	int startIndex = 0;
	int foundIndex = stringToSplit.find(delimiter, startIndex);

	while (foundIndex != std::string::npos)
	{
	    /** Get string before newly found delimiter index */
		tempString = stringToSplit.substr( startIndex, ( foundIndex - startIndex ) );

        /** Remove all leading and trailing whitespace */
		removeEdgeWhitespace(tempString);

		/** Delimiter was found starting at foundIndex */
		container.push_back( tempString );

        /** The next index to start searching from */
		startIndex = foundIndex + delimiter.length();

        /** The next index where the delimiter is found */
		foundIndex = stringToSplit.find(delimiter, startIndex);


	}

	/** After last delimiter is found, the rest of the string should be added */
    tempString = stringToSplit.substr( startIndex, (stringToSplit.size() - startIndex) );

	removeEdgeWhitespace(tempString);

	container.push_back( tempString );

}

bool isNumeric(std::string& str)
{
    int i = -1;

    if (str[0] == NULL)
    {
    	return false;
    }

    /** Iterate while not EOS */
    while(str[++i] != '\0')
    {
    	/** Not a number */
        if ( (( (int)str[i] ) < ((int) '0') || ((int) str[i]) > ((int) '9') ) )
        {
            return false;
        }
    }

    return true;
}
