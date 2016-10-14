/*
MGID Network Drive Mapper
Bradley Hamelin, 5/20/2016
Programmed in C++ with Windows API
Class used to generate and remove drive mappings.
Class reads the username and code and attempts to map to corresponding home folders, project folders.
finally, opens the project folder's Datasets.txt and maps drives to each line of the file not starting with //.
*/

#include "Mapper.h"
using namespace std;

//Default constructor
Mapper::Mapper(string user, string pass)
{
	username = user;
	password = pass;
}

//Sets all mappings for the user
string Mapper::setMappings(char driveLetterHome, char driveLetterProject, char driveLetterData)
{
	//Initialize general settings
	DWORD dwRetVal;

	NETRESOURCE nr;
	DWORD dwFlags;

	// Zero out the NETRESOURCE struct
	memset(&nr, 0, sizeof(NETRESOURCE));

	// Assign our values to the NETRESOURCE structure.
	nr.dwType = RESOURCETYPE_ANY;
	nr.lpProvider = NULL;

	// Assign a value to the connection options
	dwFlags = CONNECT_UPDATE_PROFILE;

	string homeShare = serverName + username;
	//homeShare = "\\\\gamma\\testfolder\\bhamelin";

	//Set mapping to home folder
	dwRetVal = setMapping(driveLetterHome, homeShare, nr, dwFlags);
	if (dwRetVal != NO_ERROR)
	{
		return ("Logon Failed: Invalid Username/Password.");
	}

	//Set mapping to project folder
	string result = mapProject(driveLetterProject,nr,dwFlags);

	if (result != "Connection Successful")
	{
		return result;
	}
	
	//Get the database file, read into array of all relevant databases
	result = mapDatabases(driveLetterData, nr, dwFlags);
	
	if (result != "Connection Successful")
	{
		return result;
	}
	//All mapping proceeded successfully.
	return "Connection Successful";
}

//Maps the project folder to the set letter, by trying until the correct date is found.
string Mapper::mapProject(char driveLetter, NETRESOURCE&nr, DWORD dwFlags)
{
	//Generate userpass LPSTRs
	LPSTR user = const_cast<char *>(username.c_str());
	LPSTR pass = const_cast<char *>(password.c_str());

	//Parse project number from username
	std::size_t found = username.find_last_of("-");

	string projectNumber = username.substr(username.size() - projectDigits);

	//Determine the current year
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time
	int year = localTime->tm_year + 1900;

	//Remove the thousands and hundreds
	year = year % 1000;
	year = year % 100;

	//Create the final string using each year until 2016
	for (int x = year; x >= 16; x--)
	{
		ostringstream os;
		os << serverName << "Project" << to_string(x) << "-" << projectNumber;
		string projectFile = os.str();
		DWORD dwRetVal = setMapping(driveLetter, projectFile, nr, dwFlags);

		if (dwRetVal == NO_ERROR)
		{
			return "Connection Successful";
		}
	}
	//Didnt map; return false
	return "Logged on to Home folder successfully. Warning: Could not connect to Project folder. Please contact an administrator to resolve.";
}

//Maps the databases after the H drive has been mapped to, using the database.txt file
string Mapper::mapDatabases(char driveLetter, NETRESOURCE&nr, DWORD dwFlags)
{
	vector<string> databases = getDatabaseList();
	DWORD dwRetVal;
	int x = 0;
	//Map to each of the listed databases
	for (std::vector<string>::iterator it = databases.begin(); it != databases.end(); ++it) {
		dwRetVal = setMapping(driveLetter+x, serverName + *it, nr, dwFlags);
		x++;

		if (x >= 10)
			return "Logged on to Home and Project folders successfully. Warning: Too many datasets. Connected to the first ten in Datasets.txt. Please contact an aministrator to resolve.";

		if (dwRetVal != NO_ERROR)
		{
			return "Logged on to Home and Project folders successfully. Warning: Could not connect to dataset " + *it  +" in Datasets.txt. Please contact an administrator to resolve.";
		}
	}
	return "Connection Successful";
}

//Obtains the list of drives mapped from the windows API
string Mapper::getDriveList()
{
	DWORD dwSize = MAX_PATH;
	char szLogicalDrives[MAX_PATH] = { 0 };
	DWORD dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);

	string result;

	if (dwResult > 0 && dwResult <= MAX_PATH)
	{
		char* szSingleDrive = szLogicalDrives;
		while (*szSingleDrive)
		{
			result += szSingleDrive[0];

			// get the next drive
			szSingleDrive += strlen(szSingleDrive) + 1;
		}
		return result;
	}
	return NULL;
}

//Obtains the database list from the project folder
vector<string> Mapper::getDatabaseList()
{
	vector<string> databases;
	//Make sure file exists
	std::ifstream file(databaseFile);
	std::string str;
	if (file.good())
	{
		while (std::getline(file, str))
		{
			if (str.length() > 0 && str.at(0)!='#')
				databases.push_back(str);
		}
	}
	return databases;
}

DWORD Mapper::setMapping(char driveLetter, string remoteShare, NETRESOURCE&nr, DWORD dwFlags)
{
	//Generate userpass LPSTRs
	LPSTR user = const_cast<char *>(username.c_str());
	LPSTR pass = const_cast<char *>(password.c_str());

	//Generate drive LPSTRS
	string localShare(1, driveLetter);
	localShare.append(":");
	LPSTR localDrive = const_cast<char *>(localShare.c_str());
	LPSTR remoteDrive = const_cast<char *>(remoteShare.c_str());

	nr.lpLocalName = localDrive;
	nr.lpRemoteName = remoteDrive;

	// Call the WNetAddConnection2 function to assign
	DWORD dwRetVal = WNetAddConnection2(&nr, pass, user, dwFlags);
	return dwRetVal;
}


