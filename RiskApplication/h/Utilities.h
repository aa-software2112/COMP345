/*
 * UTILITIES.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_UTILITIES_H_
#define H_UTILITIES_H_

#include <iostream>
#include <vector>

/***************************************************************
 * 						PUBLIC DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC TYPEDEFS
 ***************************************************************/
typedef unsigned int UINT;
/***************************************************************
 * 						PUBLIC GLOBALS
 ***************************************************************/

/***************************************************************
 * 						PUBLIC FUNCTIONS
 ***************************************************************/
void print(const std::string& str);
void print(std::vector<std::string>& vector);
void printWithIndex(std::vector<std::string> & vector);
void splitString(std::string& stringToSplit, std::string& delimiter, std::vector<std::string>& container);
bool isNumeric(std::string& str);
bool stringContains(std::string& strToSearch, std::string& strToFind);

/** Include this at the top of source file that shares the
 * name with this header file; hides certain members that shouldn't be
 * exposed to other source files where UTILITIES_LOCAL isn't defined.
 * */
#ifdef UTILITIES_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/
void removeLeadingWhitespace(std::string& stringToParse);
void removeTrailingWhitespace(std::string& stringToParse);
void removeEdgeWhitespace(std::string& stringToParse);
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



#endif /* H_UTILITIES_H_ */
