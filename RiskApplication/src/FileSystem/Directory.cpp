
#define DIRECTORY_LOCAL
#include "Directory.h"


/**
 * Returns all the files with a given extension to the set directory
 */
vector<string> * Directory::directory_GetAllFilesInDirectory(string& directoryPath, string& extension)
{

	/** Make sure there is a forward slash at end of directory */
	if (directoryPath[directoryPath.length() - 1] != FORWARD_SLASH)
	{
		directoryPath.push_back(FORWARD_SLASH);
	}

	/** Opens a stream to directory */
	DIR *directory = opendir(directoryPath.c_str());

	/** Where list of files in directory are stored */
	vector<string> * allFiles = new vector<string>;

	/** Current filename variable */
	string currFilename;

	/** Where each directory entry is stored */
	struct dirent *direntFile;

	/** Check if directory was found */
	if (directory != NULL)
	{
		/** Keep going until all entries were found */
		while ((direntFile = readdir(directory)) != NULL)
		{
			/** Store the filename */
			currFilename = direntFile->d_name;

			/** Check if extension was found */
			if (stringContains(currFilename, extension))
			{

				/** Store the file as a valid file
				 * Note: Full path is stored
				 * */
				allFiles->push_back(directoryPath + currFilename);

			}
		}

	}
	else
	{

		/** Close the directory for good measure */
		closedir(directory);

		return NULL;
	}


	/** Close the directory for good measure */
	closedir(directory);

	return allFiles;

}
