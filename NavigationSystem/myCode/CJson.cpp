/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CJson.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CJson.
* 					The class CJson is implement the persistent feature using
* 					the CPersistanceStorage abstract class's interfaces.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Own Include Files
#include "CJson.h"
#include "CPOI.h"

using namespace std;

CJson::CJson()
{
	// Do nothing
}

CJson::~CJson()
{
	// Do nothing
}

/**
* Set the name of the media to be used for persistent storage.
* The exact interpretation of the name depends on the implementation
* of the component.
*
* @param name the media to be used
* @returnval void
*/
void CJson::setMediaName(string name)
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
bool CJson::writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb)
{
	bool			ret = true;
	ofstream 		fileStream;
	string 			fileName;

	fileName = this->mediaName;
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
		Poi_Map_t		Pois;
		CPOI::t_poi		type;
		string			name, description, typeName;
		double 			latitude, longitude;

		Waypoints = waypointDb.getWpsFromDatabase();

		// create waypoint object in the Json format
		fileStream << "{\n";
		fileStream << "\"waypoints\": [\n";

		for (Wp_Map_Itr_t itr = Waypoints.begin(); itr != Waypoints.end(); ++(itr))
		{
			// assuming all the elements in Database is valid
			itr->second.getAllDataByReference(name, latitude, longitude);

			fileStream << "\t{\n";
			fileStream << "\t\t\"name\": \"" << name << "\",\n";
			fileStream << "\t\t\"latitude\": " << latitude << ",\n";
			fileStream << "\t\t\"longitude\": " << longitude << "\n";

			// check if this is the last element in the database
			if (&(*itr) != &(*Waypoints.rbegin()))
			{
				fileStream << "\t},\n";
			}
			else
			{
				fileStream << "\t}\n";
			}

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "WARNING: Error writing a Waypoint into the file.\n" << itr->second << endl;
				ret = false;
			}
		}

		// end the waypoint object
		fileStream << "],\n";

		Pois = poiDb.getPoisFromDatabase();

		// create waypoint object in the Json format
		fileStream << "\"pois\": [\n";

		for (Poi_Map_Itr_t itr = Pois.begin(); itr != Pois.end(); ++(itr))
		{
			// assuming all the elements in Database is valid
			itr->second.getAllDataByReference(name, latitude, longitude, type, description);
			typeName = itr->second.getPoiTypeName();

			fileStream << "\t{\n";
			fileStream << "\t\t\"name\": \"" << name << "\",\n";
			fileStream << "\t\t\"latitude\": " << latitude << ",\n";
			fileStream << "\t\t\"longitude\": " << longitude << ",\n";
			fileStream << "\t\t\"type\": \"" << typeName << ",\n";
			fileStream << "\t\t\"description\": \"" << description << "\"\n";

			if (&(*itr) != &(*Pois.rbegin()))
			{
				fileStream << "\t},\n";
			}
			else
			{
				fileStream << "\t}\n";
			}

			if (fileStream.fail())
			{
				fileStream.clear();
				cout << "WARNING: Error writing a POI into the file.\n" << itr->second << endl;
				ret = false;
			}
		}

		// end the poi object
		fileStream << "]\n}\n";
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
bool CJson::readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode)
{
	bool			ret = true;
#if 0
	ifstream 		fileStream;
	string 			fileName;

	fileName = this->mediaName;
	fileStream.precision(10);
	fileStream.clear();

	// Read Waypoints
	fileStream.open(fileName.c_str(), ifstream::in);

	// is the open successful?
	if (!fileStream.fail())
	{
		CJsonScanner obj(fileStream);
			CJsonToken *ptr = 0;
			CJsonStringToken *ptoken = 0;

			do
			{
				ptr = obj.nextToken();

				cout << ptr->getType() << endl;

				ptoken = dynamic_cast<CJsonStringToken *>(ptr);

				if (ptoken)
				{
					cout << ptoken->getValue() << endl;
				}
			} while (ptr);

		cout << "=======================================================\n";
		if (mode == CJson::MERGE)
		{
			cout << "INFO: Waypoint Database Merge Request.\n";
		}
		else if (mode == CJson::REPLACE)
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

#if 0
			getline(fileStream, readLine, '\n');

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

				if (!this->parserEachLine(readLine, name, latitude, longitude, this->lineCounter))
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
#endif
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

				if (!this->parserEachLine(readLine, type, name, description, latitude, longitude, this->lineCounter))
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
#endif
	return ret;
}
