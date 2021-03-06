#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Version
{
private:
	/* Singleton */
	Version();
	Version( Version const& );
	void operator=(Version const&);

	/* Variables */
	string versionFile;
	int majorVersion;
	int minorVersion;
	int revision;

public:
	/* Singleton */
	static Version* getInstance();
	std::string getVersion();
	std::string getYorkVersion();
	~Version();
};

extern __declspec(dllexport) void Version_Quit();