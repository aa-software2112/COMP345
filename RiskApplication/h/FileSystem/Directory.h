/*
 * template.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_DIRECTORY_H_
#define H_DIRECTORY_H_

#include "Utilities.h"
#include <string>
#include <vector>
#include <dirent.h>
using namespace std;

/** Class used to get all files in a given directory
 * This is implemented as a static class
 *  */
class Directory {

	public:
		static vector<string> * directory_GetAllFilesInDirectory(string& directoryPath, string& extension);

	private:

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
 * exposed to other source files where TEMPLATE_LOCAL isn't defined.
 * */
#ifdef DIRECTORY_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/
#define FORWARD_SLASH 		'/'
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



#endif /* H_DIRECTORY_H_ */
