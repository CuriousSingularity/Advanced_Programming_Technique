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

//Namespaces
using namespace std;

//Macros
//#define RUN_TEST_CASE

/**
 * Constructor
 */
CCSV::CCSV()
{
	// do nothing
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

	fileName = this->mediaName + "write-wp.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Write Waypoints
	fileStream.open(fileName.c_str(), ofstream::out);

	// is the open successful?
	if (!fileStream.fail())
	{
		Wp_Map_t		Waypoints;
		Wp_Map_Itr_t 	itr;
		string			name;
		double 			latitude, longitude;

		waypointDb.getWpsFromDatabase(Waypoints);

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

	fileName = this->mediaName + "write-poi.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Write Point of Interests
	fileStream.open(fileName.c_str(), ofstream::out);

	// is the open successful?
	if (!fileStream.fail())
	{
		Poi_Map_t		Pois;
		Poi_Map_Itr_t 	itr;
		CPOI::t_poi		type;
		string			name, description, typeName;
		double 			latitude, longitude;

		poiDb.getPoisFromDatabase(Pois);

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

	fileName = this->mediaName + "read-wp.txt";
	fileStream.precision(10);
	fileStream.clear();

	// Read Waypoints
	fileStream.open(fileName.c_str(), ifstream::in);

	// is the open successful?
	if (!fileStream.fail())
	{
		string			readLine;

		while (!fileStream.eof())
		{
			getline(fileStream, readLine, '\n');

			if (readLine.length() == 0)
			{
				// empty line - ignore them
				cout << "WARNING: Empty line found, hence ignoring.\n";
				continue;
			}

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "WARNING: Error reading a waypoint from the file - " << fileName << endl;
				ret = false;
			}
			else
			{
				stringstream	ss(readLine);
				string			nameParsed, latitudeParsed, longitudeParsed;
				double 			latitude = (LATITUDE_MAX + 1), longitude = (LONGITUDE_MAX  + 1);	// set to invalid values

				getline(ss, nameParsed, ';');
				getline(ss, latitudeParsed, ';');
				getline(ss, longitudeParsed, '\n');

				ss.clear();
				ss.str("");

				ss << latitudeParsed;

				if (!latitudeParsed.empty())
				{
					ss >> latitude;

					ss.clear();
					ss.str("");
				}

				ss << longitudeParsed;

				if (!longitudeParsed.empty())
				{
					ss >> longitude;
					ss.clear();
					ss.str("");
				}

				CWaypoint wp(nameParsed, latitude, longitude);

				if (!wp.getName().empty())
				{
					waypointDb.addWaypoint(wp);
				}
				else
				{
					cout << "WARNING: Invalid waypoint found in the database, hence ignoring.\n";
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

bool extractNumberFromString(const std::string &str, double &number)
{
	bool ret = false;

	if (!str.empty())
	{
		for (unsigned int index = 0, decPointCount = 0; index < str.length(); ++index)
		{
			if (!((str[index] >= '0' && str[index] <= '9') || (str[index] == '.' && !decPointCount++)))
			{
				break;
			}
		}

		ret = true;
	}

	return true;
}
