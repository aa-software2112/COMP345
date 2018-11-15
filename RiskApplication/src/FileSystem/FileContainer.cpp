
#define FILE_CONTAINER_LOCAL
#include "FileContainer.h"

FileContainer::FileContainer(const string& argFilePath) {

	/** Set the fileExists property */
	FILE * file = fopen(argFilePath.c_str(), "r");

	this->filePath = argFilePath;

	if (file == NULL)
	{
		this->fileExists = false;
	}
	else
	{

		fclose(file);
		this->fileExists = true;

	}


	/** Default file operation is read */
	this->operationMode = READ;

}


bool FileContainer::fileContainer_exists(void) {

	return fileExists;

}

void FileContainer::fileContainer_openFileInMode(FileContainer::fileOperation operationMode) {

	if (this->fileContainer_exists())
	{

		if (operationMode == READ)
		{
			this->fileHandle.open(this->filePath.c_str(), fstream::in);
		}
		else if (operationMode == WRITE)
		{
			this->fileHandle.open(this->filePath.c_str(), fstream::out);
		}

		this->fileContainer_setMode(operationMode);

	}

	return;

}

void FileContainer::fileContainer_displayRemainingContents()
{
	if (this->fileContainer_getMode() == READ)
	{
		string lRead;

		while(this->fileContainer_getNextLine(lRead))
		{
			print(lRead);

		}
	}


}

/** Gets the next line and stores it in the reference passed in arg1,
 * Returns true if line was found, else false
 */
bool FileContainer::fileContainer_getNextLine(string& nextLine) {

	if (this->operationMode == READ)
	{

		if (getline(this->fileHandle, nextLine))
		{
			return true;
		}
	}

	return false;

}

FileContainer::fileOperation FileContainer::fileContainer_getMode(void)
{

	return this->operationMode;

}

void FileContainer::fileContainer_setMode(fileOperation argOperationMode)
{

	this->operationMode = argOperationMode;

}
