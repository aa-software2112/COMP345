
#define FILE_READER_LOCAL
#include "FileReader.h"

FileReader::FileReader(const string& argPathToFile)
{

	this->file = new FileContainer(argPathToFile);

	this->file->fileContainer_openFileInMode(FileContainer::fileOperation::READ);

}

bool FileReader::fileReader_findLineContaining(string& stringToFind)
{

	string nextLineRead;

	while(this->file->fileContainer_getNextLine(nextLineRead))
	{
		if (nextLineRead.find(stringToFind, 0) != string::npos)
		{
			//print("Found text: " + stringToFind + " in text file line: "  + nextLineRead);
			return true;
		}

	}

	return false;


}

bool FileReader::fileReader_getStringUntilLineContaining(string& stringBuffer, string& stringToStopAt)
{

	string nextLineRead;

	/** Iterate while data exists */
	while(this->file->fileContainer_getNextLine(nextLineRead))
	{
		/** Line does not contain ending string */
		if (nextLineRead.find(stringToStopAt, 0) == string::npos)
		{
			/** Add current string to buffer */
			stringBuffer += (nextLineRead + "\n");
		}
		else
		{
			/** The string to stop at was found */
			return true;
		}

	}

	/** The string to stop at was not found */
	return false;





}
