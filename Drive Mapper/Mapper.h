#ifndef MAPPER
#define MAPPER

#pragma comment(lib, "mpr.lib")
#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h>
#include <strsafe.h>
#include <ctime> 
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;
//Class used to generate and remove drive mappings.
//Class reads the username and code and attempts to map to corresponding home folders, project folders.
//finally, opens the project folder's Datasets.txt and maps drives to each line of the file not starting with //.

class Mapper
{
private:
	string username;
	string password;
	const string databaseFile = "I:\\Datasets.txt";
	const string serverName = "\\\\SSC-MGID-NAS\\";
	const int projectDigits = 3;
	//Default constructor
public:
	//Default constructor, sets the username and pass of the mapper
	Mapper(string user, string pass);

	//Returns a list of each drive
	static string getDriveList();

	//For each character, check if not C or D
	bool isMapped();

	//Determines if the user is valid in the system or not
	bool validateLogon();

	//Sets all three drive mappings
	string setMappings(char driveLetterHome, char driveLetterProject, char driveLetterData);

	DWORD setMapping(char driveLetter, string remoteShare, NETRESOURCE&nr, DWORD dwFlags);

	//Get the datasets list from the file in the project
	vector<string> getDatabaseList();

	string mapProject(char driveLetter, NETRESOURCE&nr, DWORD dwFlags);
	string mapDatabases(char driveLetter, NETRESOURCE&nr, DWORD dwFlags);

};

#endif