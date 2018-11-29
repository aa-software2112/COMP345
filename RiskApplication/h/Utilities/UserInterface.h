/*
 * USER_INTERFACE.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_USER_INTERFACE_H_
#define H_USER_INTERFACE_H_

#include "Utilities.h"
#include <vector>
#include <string>
using namespace std;

/** Implemented as a static class */
class UserInterface {

public:
	static int userInterface_getIntegerBetweenRange(string& messageToDisplay, int smallestValue, int largestValue);
	static int userInterface_getIndexOfList(vector<string>& list, string& messageToDisplay);
	static int userInterface_getInteger(string& messageToDisplay);
	static string userInterface_getString(string& messageToDisplay);
	static bool userInterface_getYesNo(string& messageToDisplay);
private:
	static void userInterface_displayInputHeader(void);
	const static string header;


};

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where USER_INTERFACE_LOCAL isn't defined.
 * */
#ifdef USER_INTERFACE_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_USER_INTERFACE_H_ */
