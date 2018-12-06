/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCSV.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CCSV.
* 					The class CCSV is implement the persistent feature using
* 					the CPersistanceStorage abstract class's interfaces.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Own Include Files
#include "CCSV.h"
#include "CPOI.h"

//Namespaces
using namespace std;

//Macros
//#define RUN_TEST_CASE

//Class constant variables
const std::string CCSV::delimiters(",;");


/**
 * Constructor
 */
CCSV::CCSV()
{
	this->lineCounter = 0;
}

/**
 * Destructor
 */
CCSV::~CCSV()
{
	// do nothing
}



/**
* Set the name of the media to be used for persistent storage.
* The exact interpretation of the name depends on the implementation
* of the component.
*
* @param name the media to be used
* @returnval void
*/
void CCSV::setMediaName(string name)
{
	this->mediaName = name;
}


/**
* Write the data to the persistent storage.
*
* @param waypointDb the data base with way points
* @param poiDb the database with points of interest
* @return true if the data could be saved successfully
*/
bool CCSV::writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
{
	bool			ret = true;
	ofstream 		fileStream;
	string 			fileName;

	fileName = this->mediaName + "-wp.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Write Waypoints
	fileStream.open(fileName.c_str(), ofstream::out);

	cout << "=======================================================\n";
	cout << "INFO: Waypoint Database backup request\n";

	// is the open successful?
	if (!fileStream.fail())
	{
		Wp_Map_t		Waypoints;
		Wp_Map_Itr_t 	itr;
		string			name;
		double 			latitude, longitude;

		Waypoints = waypointDb.getWpsFromDatabase();

		for (itr = Waypoints.begin(); itr != Waypoints.end(); ++(itr))
		{
			// assuming all the elements in Database is valid
			itr->second.getAllDataByReference(name, latitude, longitude);

			fileStream << name << "; ";
			fileStream << latitude << "; ";
			fileStream << longitude << "\n";

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "WARNING: Error writing a Waypoint into the file.\n" << itr->second << endl;
				ret = false;
			}
		}
	}
	else
	{
		fileStream.clear();
		cout << "WARNING: Error opening the file to write - " << fileName << endl;
		ret = false;
	}

	fileStream.flush();
	fileStream.close();

	cout << "=======================================================\n";

	fileName = this->mediaName + "-poi.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Write Point of Interests
	fileStream.open(fileName.c_str(), ofstream::out);

	cout << "=======================================================\n";
	cout << "INFO: POI Database backup request\n";

	// is the open successful?
	if (!fileStream.fail())
	{
		Poi_Map_t		Pois;
		Poi_Map_Itr_t 	itr;
		CPOI::t_poi		type;
		string			name, description, typeName;
		double 			latitude, longitude;

		Pois = poiDb.getPoisFromDatabase();

		for (itr = Pois.begin(); itr != Pois.end(); ++(itr))
		{
			// assuming all the elements in Database is valid
			itr->second.getAllDataByReference(name, latitude, longitude, type, description);
			typeName = itr->second.getPoiTypeName();

			fileStream << typeName << "; ";
			fileStream << name << "; ";
			fileStream << description << "; ";
			fileStream << latitude << "; ";
			fileStream << longitude << "\n";

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "WARNING: Error writing a POI into the file.\n" << itr->second << endl;
				ret = false;
			}
		}
	}
	else
	{
		fileStream.clear();
		cout << "WARNING: Error opening the file to write - " << fileName << endl;
		ret = false;
	}

	fileStream.flush();
	fileStream.close();

	cout << "=======================================================\n";

	return ret;
}


/**
* Fill the databases with the data from persistent storage. If
* merge mode is MERGE, the content in the persistent storage
* will be merged with any content already existing in the data
* bases. If merge mode is REPLACE, already existing content
* will be removed before inserting the content from the persistent
* storage.
*
* @param waypointDb the the data base with way points
* @param poiDb the database with points of interest
* @param mode the merge mode
* @return true if the data could be read successfully
*/
bool CCSV::readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode)
{
	bool			ret = true;
	ifstream 		fileStream;
	string 			fileName;

	fileName = this->mediaName + "-wp.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Read Waypoints
	fileStream.open(fileName.c_str(), ifstream::in);

	// is the open successful?
	if (!fileStream.fail())
	{
		string			readLine;

		this->lineCounter = 0;

		cout << "=======================================================\n";
		if (mode == CCSV::MERGE)
		{
			cout << "INFO: Waypoint Database Merge Request.\n";
		}
		else if (mode == CCSV::REPLACE)
		{
			waypointDb.resetWpsDatabase();
			cout << "INFO: Waypoint Database Replace Request.\n";
		}
		else
		{
			cout << "ERROR: Waypoint Database Unknown MergeMode Request.\n";
			return false;
		}

		cout << "=======================================================\n";

		while (!fileStream.eof())
		{
			getline(fileStream, readLine, '\n');
			this->lineCounter++;

			if (readLine.length() == 0)
			{
				// empty line - ignore them
				cout << "ERROR: Empty line in line " << this->lineCounter << "\n";
				continue;
			}

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "ERROR: Reading a waypoint from the file - " << fileName << endl;
				ret = false;
			}
			else
			{
				string			name;
				double 			latitude = (LATITUDE_MAX + 1), longitude = (LONGITUDE_MAX  + 1);	// set to invalid values

				if (!this->parserEachLine(readLine, name, latitude, longitude))
				{
					continue;
				}

				CWaypoint wp(name, latitude, longitude);

				if (!wp.getName().empty())
				{
					waypointDb.addWaypoint(wp);
				}
				else
				{
					cout << "ERROR: Invalid Waypoint in line " << this->lineCounter << ": " << readLine << "\n";
				}
			}
		}
	}
	else
	{
		fileStream.clear();
		cout << "WARNING: Error opening the file to read - " << fileName << endl;
		ret = false;
	}

	fileStream.close();

	fileName = this->mediaName + "-poi.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Read POIs
	fileStream.open(fileName.c_str(), ifstream::in);

	// is the open successful?
	if (!fileStream.fail())
	{
		string			readLine;

		this->lineCounter = 0;

		cout << "=======================================================\n";

		if (mode == CCSV::MERGE)
		{
			cout << "INFO: POI Database Merge Request.\n";
		}
		else if (mode == CCSV::REPLACE)
		{
			poiDb.resetPoisDatabase();
			cout << "INFO: POI Database Replace Request.\n";
		}
		else
		{
			cout << "ERROR: POI Database Unknown MergeMode Request.\n";
			return false;
		}

		cout << "=======================================================\n";

		while (!fileStream.eof())
		{
			getline(fileStream, readLine, '\n');
			this->lineCounter++;

			if (readLine.length() == 0)
			{
				// empty line - ignore them
				cout << "ERROR: Empty line in line " << this->lineCounter << "\n";
				continue;
			}

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "ERROR: Reading a POI from the file - " << fileName << endl;
				ret = false;
			}
			else
			{
				CPOI::t_poi		type;
				string			name, description;
				double 			latitude = (LATITUDE_MAX + 1), longitude = (LONGITUDE_MAX  + 1);	// set to invalid values

				if (!this->parserEachLine(readLine, type, name, description, latitude, longitude))
				{
					continue;
				}

				CPOI poi(type, name, description, latitude, longitude);

				if (!poi.getName().empty())
				{
					poiDb.addPoi(poi);
				}
				else
				{
					cout << "ERROR: Invalid Waypoint in line " << this->lineCounter << ": " << readLine << "\n";
				}
			}
		}
	}
	else
	{
		fileStream.clear();
		cout << "WARNING: Error opening the file to read - " << fileName << endl;
		ret = false;
	}

	fileStream.close();

	return ret;
}


/**
 * Extract number from the string
 * @param const string &str		-	string				(IN)
 * @param double &number		-	Number to return 	(OUT)
 * @returnval bool				- 	Success - true or Failure - false
 */
bool CCSV::extractNumberFromString(const std::string &str, double &number)
{
	bool 			isNumber = false;

	if (!str.empty())
	{
		unsigned int index = 0;

		// remove all the leading spaces and tabs
		while ((str[index] == ' ') || (str[index] == '\t'))
		{
			index++;
		}

		for (unsigned int decPointCount = 0; index < str.length(); ++index)
		{
			// check if the string contains only numbers and maybe a .
			if (!((str[index] >= '0' && str[index] <= '9') || (str[index] == '.' && !decPointCount++)))
			{
				isNumber = false;
				break;
			}
			else
			{
				isNumber = true;
			}
		}

		if (isNumber)
		{
			stringstream	ss(str);

			// extract the number
			ss >> number;
		}
	}

	return isNumber;
}


/**
 * Parse a line to get waypoint information such as name, latitude and longitude in order
 * @param const string &readLine	-	Each Line				(IN)
 * @param const string &name		-	name of waypoint		(OUT)
 * @param const double &latitude	-	latitude of waypoint	(OUT)
 * @param const double &longitude	-	longitude of waypoint	(OUT)
 * @returnval bool					- 	Success - true or Failure - false
 */
bool CCSV::parserEachLine(const string &readLine, std::string &name, double &latitude, double &longitude)
{
	bool			ret = true;

	// check if the one of the delimiters exists
	if (readLine.find_first_of(this->delimiters) != string::npos)
	{
		stringstream	ss(readLine);
		string			nameParsed, latitudeParsed, longitudeParsed;

		for (unsigned int index = 0; index < this->delimiters.length(); index++)
		{
			if (readLine.find_first_of(this->delimiters[index]) != string::npos)
			{
				getline(ss, nameParsed, 		this->delimiters[index]);
				getline(ss, latitudeParsed, 	this->delimiters[index]);
				getline(ss, longitudeParsed,	'\n');

				// remove leading spaces and tables
				nameParsed.erase(0, nameParsed.find_first_not_of(' '));
				nameParsed.erase(0, nameParsed.find_first_not_of('\t'));
				name = nameParsed;
				break;
			}
		}

		if ((!this->extractNumberFromString(latitudeParsed, latitude)) ||
			(!this->extractNumberFromString(longitudeParsed, longitude)) ||
			(nameParsed.empty()))
		{
			cout << "ERROR: Invalid or too few fields in line " << this->lineCounter << ": " << readLine << "\n";
			ret = false;
		}
	}
	else
	{
		cout << "ERROR: Could not find the delimiters in line " << this->lineCounter << ": " << readLine << "\n";
		ret = false;
	}

	return ret;
}


/**
 * Parse a line to get POI information such as type, name, description, latitude and longitude in order
 * @param const string &readLine	-	Each Line				(IN)
 * @param const t_poi &type			-	name of POI				(OUT)
 * @param const string &name		-	name of POI				(OUT)
 * @param const string &description	-	description of POI		(OUT)
 * @param const double &latitude	-	latitude of POI			(OUT)
 * @param const double &longitude	-	longitude of POI		(OUT)
 * @returnval bool					- 	Success - true or Failure - false
 */
bool CCSV::parserEachLine(const string &readLine, CPOI::t_poi &type, string &name, std::string &description, double &latitude, double &longitude)
{
	bool			ret = true;

	// check if the one of the delimiters exists
	if (readLine.find_first_of(this->delimiters) != string::npos)
	{
		stringstream	ss(readLine);
		string			typeParsed, nameParsed, descriptionParsed, latitudeParsed, longitudeParsed;

		for (unsigned int index = 0; index < this->delimiters.length(); index++)
		{
			if (readLine.find_first_of(this->delimiters[index]) != string::npos)
			{
				getline(ss, typeParsed, 		this->delimiters[index]);
				getline(ss, nameParsed, 		this->delimiters[index]);
				getline(ss, descriptionParsed,	this->delimiters[index]);
				getline(ss, latitudeParsed, 	this->delimiters[index]);
				getline(ss, longitudeParsed,	'\n');

				// remove leading spaces and tables
				nameParsed.erase(0, nameParsed.find_first_not_of(' '));
				nameParsed.erase(0, nameParsed.find_first_not_of('\t'));
				name 			= nameParsed;

				// remove leading spaces and tables
				descriptionParsed.erase(0, descriptionParsed.find_first_not_of(' '));
				descriptionParsed.erase(0, descriptionParsed.find_first_not_of('\t'));
				description 	= descriptionParsed;

				// remove leading spaces and tables
				typeParsed.erase(0, typeParsed.find_first_not_of(' '));
				typeParsed.erase(0, typeParsed.find_first_not_of('\t'));
				type			= CPOI::getPoiType(typeParsed);
				break;
			}
		}

		if ((!this->extractNumberFromString(latitudeParsed, latitude)) ||
			(!this->extractNumberFromString(longitudeParsed, longitude)) ||
			(CPOI::DEFAULT_POI == type) ||
			(nameParsed.empty()))
		{
			cout << "ERROR: Invalid or too few fields in line " << this->lineCounter << ": " << readLine << "\n";
			ret = false;
		}
	}
	else
	{
		cout << "ERROR: Could not find the delimiters in line " << this->lineCounter << ": " << readLine << "\n";
		ret = false;
	}

	return ret;
}
