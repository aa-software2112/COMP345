/*
 * FILE_READER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_FILE_READER_H_
#define H_FILE_READER_H_

#include <fstream>
#include "Utilities.h"
#include "FileContainer.h"
using namespace std;

class FileReader {
	public:
		FileReader(const string& argPathToFile);
		bool fileReader_findLineContaining(string& stringToFind);
		bool fileReader_getStringUntilLineContaining(string& stringBuffer, string& stringToStopAt);

	private:
		FileContainer * file;



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
 * exposed to other source files where FILE_READER_LOCAL isn't defined.
 * */
#ifdef FILE_READER_LOCAL


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



#endif /* H_FILE_READER_H_ */
