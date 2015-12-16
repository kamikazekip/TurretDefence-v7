#include "Version.h"
#include "global.h"

static Version* instance;

Version::Version()
{
	versionFile = assetBasePath + "Version/version.ini";

	string line;
	int lineNumber = 0;

	ifstream myfile( versionFile );
	if( myfile.is_open() )
	{
		while( getline( myfile, line ) )
		{
			string delimiter = " ";
			size_t pos = 0;
			int counter = 0;
			std::string token;
			while( (pos = line.find( delimiter )) != std::string::npos )
			{
				token = line.substr( 0, pos );
				line.erase( 0, pos + delimiter.length() );
				if( counter == 0 )
					majorVersion = stoi( token );
				else if( counter == 1 )
				{
					minorVersion = stoi( token );
					revision = stoi( line );
				}
				counter++;
			}
			lineNumber++;
		}
		myfile.close();
		revision++;

		ofstream myfile( versionFile );
		if( myfile.is_open() )
		{
			myfile << majorVersion << " " << minorVersion << " " << revision;
			myfile.close();
		}
		else 
			cout << "Unable to open version file for writing!";
		revision--;
	}
	else
		cout << "Unable to open version file!\n";
}

/* Singleton */
Version* Version::getInstance()
{
	if( !instance )
		instance = new Version();
	return instance;
}

Version::~Version()
{

}

std::string Version::getVersion()
{
	ostringstream oss;
	oss << "Version " << majorVersion << "." << minorVersion << "." << revision;
	return oss.str();
}

std::string Version::getYorkVersion()
{
	ostringstream oss;
	oss << "ÒVERSION!!" << majorVersion << "." << minorVersion << "." << revision << "Ó" ;
	return oss.str();
}

extern __declspec(dllexport) void Version_Quit()
{
	delete instance; instance = nullptr;
}
