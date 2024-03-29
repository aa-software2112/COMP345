
#define USER_INTERFACE_LOCAL
#include "UserInterface.h"

const string UserInterface::header = "********************\n**** INPUT VALUE ***\n********************";



int UserInterface::userInterface_getIntegerBetweenRange(string& messageToDisplay, int smallestValue, int largestValue)
{

	int newestInteger;

	do {

		newestInteger = UserInterface::userInterface_getInteger(messageToDisplay);

	}while(   (newestInteger < smallestValue) || (newestInteger > largestValue) );

	return newestInteger;

}

/** This function will automatically force the user to give a value
 * within the indexable range of the vector
 */
int UserInterface::userInterface_getIndexOfList(vector<string>& list, string& messageToDisplay)
{

	/** Display options */
	printWithIndex(list);

	return UserInterface::userInterface_getIntegerBetweenRange(messageToDisplay, 0, (int)(list.size() - 1));


}

int  UserInterface::userInterface_getInteger(string& messageToDisplay)
{
	bool integerValid = false;

	string inputContainer;
	int returnInteger = 0;

	/** Display message */
	print(messageToDisplay);

	/** Get an integer */
	while(!integerValid)
	{
		/** Prompt user */
		cout << ">";
		cin >> inputContainer;

		/** Found a numeric value */
		if (isNumeric(inputContainer))
		{
			returnInteger = (int) strtol(inputContainer.c_str(), NULL, 10);

			integerValid = true;
		}

	}


	return returnInteger;
}

string UserInterface::userInterface_getString(string& messageToDisplay)
{
	/** Display message */
	print(messageToDisplay);

	string inputContainer;

	cin >> inputContainer;

	return inputContainer;
}

void UserInterface::userInterface_displayInputHeader(void)
{
	print(UserInterface::header);

}
