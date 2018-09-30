/*
 * FILE_CONTAINER.h
 *
 *  Created on: Sep. 23, 2018
 *      Author: Anthony Andreoli
 */

#ifndef H_FILE_CONTAINER_H_
#define H_FILE_CONTAINER_H_

#include <fstream>
#include "Utilities.h"
using namespace std;

class FileContainer {
	public:
		enum fileOperation {
			READ = 0,
			WRITE = 1,
		};
		/** Constructor **/
		FileContainer(const string& argFilePath);
		void fileContainer_openFileInMode(fileOperation operationMode);
		void fileContainer_displayRemainingContents(void);
		bool fileContainer_getNextLine(string& nextLine);
		bool fileContainer_exists();

	private:
		void fileContainer_setMode(fileOperation argOperationMode);
		fileOperation fileContainer_getMode(void);
		fileOperation operationMode;
		fstream fileHandle;
		string filePath;
		bool fileExists;


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
 * exposed to other source files where FILE_CONTAINER_LOCAL isn't defined.
 * */
#ifdef FILE_CONTAINER_LOCAL


/***************************************************************
 * 						PRIVATE DEFINITIONS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE TYPEDEFS
 ***************************************************************/

/***************************************************************
 * 						PRIVATE GLOBALS
 ***************************************************************/
/** The string returned from fileContainer_getNextLine() when EOF is reached */
#define NO_VALUE	"_NV_"

/***************************************************************
 * 						PRIVATE FUNCTIONS
 ***************************************************************/


#endif



#endif /* H_FILE_CONTAINER_H_ */
