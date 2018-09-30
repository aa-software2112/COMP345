
#define FILE_CONTAINTER_LOCAL
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
		string * lRead;

		while((lRead = this->fileContainer_getNextLine()))
		{
			print(*lRead);

		}
	}


}

string * FileContainer::fileContainer_getNextLine(void) {

	if (this->operationMode == READ)
	{
		string * outputString = new string();

		if (getline(this->fileHandle, *outputString))
		{
			return outputString;
		}
	}

	return NULL;


}

FileContainer::fileOperation FileContainer::fileContainer_getMode(void)
{

	return this->operationMode;

}

void FileContainer::fileContainer_setMode(fileOperation argOperationMode)
{

	this->operationMode = argOperationMode;

}
