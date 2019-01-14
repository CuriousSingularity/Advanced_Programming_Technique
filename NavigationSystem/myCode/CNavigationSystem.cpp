/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNavigationSystem.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CNavigationSystem.
* 					The class CNavigationSystem is used for Navigation which
* 					has a GPS Sensor, Route and a Database.
*
****************************************************************************/

//System Include Files
#include <iostream>

//Own Include Files
#include "CNavigationSystem.h"
#include "CCSV.h"
#include "CJsonPersistence.h"

//Namespaces
using namespace std;

#define CSV						0
#define JSON					1

//#define CONFIG_PERSISTENCE_STORAGE		CSV
#define CONFIG_PERSISTENCE_STORAGE		JSON


//Method Implementations
/**
 * Constructor
 */
CNavigationSystem::CNavigationSystem()
{
	// Do nothing
}


/**
 * Get the Poi Database
 * returnval@ CPoiDatabase&	- Reference to the POI Database
 */
CPoiDatabase& CNavigationSystem::getPoiDatabase()
{
	return this->m_PoiDatabase;
}


/**
 * Get the Waypoint Database
 * returnval@ CWpDatabase&	- Reference to the Waypoint Database
 */
CWpDatabase& CNavigationSystem::getWpDatabase()
{
	return this->m_WpDatabase;
}


/**
 * Add waypoints and POIs to create custom route
 * @returnval void
 */
void CNavigationSystem::enterRoute()
{
	cout << "=======================================================\n";
	cout << "INFO: Add Waypoints and POI to the Route\n";
	cout << "=======================================================\n";

#ifdef RUN_TEST_ROUTE_OPERATOR_ASSIGNMENT
	CRoute testRoute;
	testRoute = this->m_route;
	this->m_route = testRoute;
#endif

	// add waypoints
	this->m_route.addWaypoint("Berliner Alle"	);
	this->m_route.addWaypoint("Rheinstrasse"     );
	this->m_route.addWaypoint("Neckarstrasse"    );

	// add POIs
	this->m_route.addPoi("HDA BuildingC10"	, "Berliner Alle"	);
	this->m_route.addPoi("Aral Tankst."		, "Rheinstrasse"	);
	this->m_route.addPoi("Starbucks"		, "Neckarstrasse"	);

//	this->m_route += "Landskronstrasse";
//	this->m_route += "SushiRestaurant";

#ifdef RUN_TEST_CASE_NON_EXIST_WAYPOINT
    testCaseNonExistingWaypoint();
#endif

#ifdef RUN_TEST_CASE_NON_EXIST_POI
	testCaseNonExistingPOI();
	this->m_route += "";
#endif

#ifdef RUN_TEST_ROUTE_OPERATOR_ADDITION
	CRoute testRoute_extended;

	// connect the database
	testRoute_extended.connectToPoiDatabase(&this->m_PoiDatabase);
	testRoute_extended.connectToWpDatabase(&this->m_WpDatabase);

	testRoute_extended.addWaypoint("Bessunger"		);
	testRoute_extended.addWaypoint("FriedrichStrasse");
	testRoute_extended.addWaypoint("Katharinen Str.");
	testRoute_extended.addWaypoint("Wartehalle"		);

	testRoute_extended.addPoi("Aral Tankstelle"	, "Bessunger"	);
	testRoute_extended.addPoi("Church Holy"		, "FriedrichStrasse"	);
	testRoute_extended.addPoi("Thessaloniki"	, "Wartehalle");

	cout << "Route1: \n";
	this->m_route.print();

	cout << "Route2: \n";
	testRoute_extended.print();

	// combine the routes
	this->m_route = this->m_route + testRoute_extended;

	cout << "Combined Route: \n";
	this->m_route.print();

#endif
}


/**
 * Print all the waypoints and POIs of the custom route
 * @returnval void
 */
void CNavigationSystem::printRoute()
{
	this->m_route.print();
}


/**
 * Print the Distance between current position and a closest POI
 * @returnval void
 */
void CNavigationSystem::printDistanceCurPosNextPoi()
{
	CPOI poi;
	CPOI::t_poi type = CPOI::DEFAULT_POI;
	string name, description;
	double distance = 0, latitude = 0, longitude = 0;

	CWaypoint currentPosition;
	currentPosition = this->m_GPSSensor.getCurrentPosition();

	// check if the GPS current location is valid
	currentPosition.getAllDataByReference(name, latitude, longitude);

	if (!name.empty())
	{
		distance = this->m_route.getDistanceNextPoi(currentPosition, poi);

		// check if the POI is valid
		poi.getAllDataByReference(name, latitude, longitude, type, description);

		if (type != CPOI::DEFAULT_POI)
		{
			cout << "Distance to next POI = " << distance << " Kms (approx.)\n\n" << poi << endl;
		}
		else
		{
			cout << "WARNING: Can not compute the distance.\n";
		}
	}
	else
	{
		cout << "WARNING: Invalid Sensor data.\n";
	}
}


/**
 * Creates Waypoint Database and Poi Database
 * @returnval void
 */
void CNavigationSystem::createDatabases()
{
	// add a waypoint
	this->m_WpDatabase.addWaypoint(CWaypoint("Berliner Alle", 49.866851, 8.634864));

	// add a POI
	this->m_PoiDatabase.addPoi(CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));
}


/**
 * Write the current content of Databases to files
 * @returnval void
 */
bool CNavigationSystem::writeToFile()
{
	bool 			ret = false;

#if (defined(CONFIG_PERSISTENCE_STORAGE) && (CONFIG_PERSISTENCE_STORAGE == CSV))

	CCSV 			csvDatabase;
	csvDatabase.setMediaName("Database");

	// write the current Databases' contents to files
	ret = csvDatabase.writeData(this->getWpDatabase(), this->getPoiDatabase());

#elif (defined(CONFIG_CONFIG_PERSISTENCE_STORAGE) && (CONFIG_CONFIG_PERSISTENCE_STORAGE == JSON))

	CJsonPersistence	jsonFormat;
	jsonFormat.setMediaName("Database1.json");
	ret = jsonFormat.writeData(this->getWpDatabase(), this->getPoiDatabase());

#else

#endif
	return ret;
}


/**
 * Read the Database content from file to Databases
 * @returnval void
 */
bool CNavigationSystem::readFromFile()
{
	bool 			ret = false;

#if (defined(CONFIG_PERSISTENCE_STORAGE) && (CONFIG_PERSISTENCE_STORAGE == CSV))

	CCSV 			csvDatabase;
	csvDatabase.setMediaName("Database");

	// write the current Databases' contents to files
	ret = csvDatabase.readData(this->getWpDatabase(), this->getPoiDatabase(), CCSV::REPLACE);

#elif (defined(CONFIG_PERSISTENCE_STORAGE) && (CONFIG_PERSISTENCE_STORAGE == JSON))

	CJsonPersistence		jsonFormat;
	jsonFormat.setMediaName("Database.json");

	// write the current Databases' contents to files
	ret = jsonFormat.readData(this->getWpDatabase(), this->getPoiDatabase(), CJsonPersistence::REPLACE);

#else

#endif

	return ret;
}


/**
 * Navigation System functionaliy's entry function
 * @returnval void
 */
void CNavigationSystem::run()
{
	// connect to the Database
#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_POI
	this->testCaseDatabaseNotAvailablePoi();
#else
	this->m_route.connectToPoiDatabase(&this->m_PoiDatabase);
#endif

#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_WAYPOINT
	this->testCaseDatabaseNotAvailableWaypoint();
#else
	this->m_route.connectToWpDatabase(&this->m_WpDatabase);
#endif

	// create the databases
	//this->createDatabases();

	// read the database files
	if (!this->readFromFile())
	{
		cout << "WARNING: Reading from the Database files was unsuccessful.\n";
	}

	// write to the file
	if (!this->writeToFile())
	{
		cout << "WARNING: Writing to the Database files was unsuccessful.\n";
	}

	cout << "Here1" << endl;
	this->m_PoiDatabase.print();
	this->m_WpDatabase.print();
	cout << "Here1" << endl;

	this->enterRoute();
	this->printRoute();
	this->printDistanceCurPosNextPoi();
}


/**
 * TestCase to check if non existing POI is added to the route
 * @returnval void
 */
#ifdef RUN_TEST_CASE_NON_EXIST_POI
void CNavigationSystem::testCaseNonExistingPOI()
{
	this->m_route.addPoi("HDA Mensa",	"Berliner Alle");
}
#endif


/**
 * TestCase to check if non existing Waypoint is added to the route
 * @returnval void
 */
#ifdef RUN_TEST_CASE_NON_EXIST_WAYPOINT
void CNavigationSystem::testCaseNonExistingWaypoint()
{
	this->m_route.addWaypoint("My Chicken");
}
#endif


/**
 * TestCase to check when POI database is not available
 * @returnval void
 */
#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_POI
void CNavigationSystem::testCaseDatabaseNotAvailablePoi()
{
	this->m_route.connectToPoiDatabase(0);
}
#endif


/**
 * TestCase to check when Waypoint database is not available
 * @returnval void
 */
#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_WAYPOINT
void CNavigationSystem::testCaseDatabaseNotAvailableWaypoint()
{
	this->m_route.connectToWpDatabase(0);
}
#endif
