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

//Namespaces
using namespace std;

//Method Implementations
/**
 * Constructor
 */
CNavigationSystem::CNavigationSystem()
{
	// Do nothing
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

	this->enterRoute();
	this->printRoute();
	this->printDistanceCurPosNextPoi();
}


/**
 * Add waypoints and POIs to create custom route
 * @returnval void
 */
void CNavigationSystem::enterRoute()
{
	// add waypoints
	this->m_route.addWaypoint("Berliner Alle"	);
	this->m_route.addWaypoint("Rheinstraße"     );
	this->m_route.addWaypoint("Neckarstraße"    );
//	this->m_route.addWaypoint("Landskronstraße" );
//	this->m_route.addWaypoint("Bessunger"       );
//	this->m_route.addWaypoint("FriedrichStraße" );
//	this->m_route.addWaypoint("Katharinen Str." );
//	this->m_route.addWaypoint("Wartehalle"      );

#ifdef RUN_TEST_CASE_NON_EXIST_WAYPOINT
    testCaseNonExistingWaypoint();
#endif

    this->printRoute();
	// add POIs
	this->m_route.addPoi("HDA BuildingC10"	, "Berliner Alle"	);
	this->m_route.addPoi("Aral Tankst."		, "Rheinstraße"		);
	this->m_route.addPoi("Starbucks"		, "Neckarstraße"	);
//	this->m_route.addPoi("SushiRestaurant"	);
//	this->m_route.addPoi("Aral Tankstelle"	);
//	this->m_route.addPoi("Church Holy"		);
//	this->m_route.addPoi("Thessaloniki"		);
//	this->m_route.addPoi("Church 7 Days"	);

	this->printRoute();

#ifdef RUN_TEST_CASE_NON_EXIST_POI
	testCaseNonExistingPOI();
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
			cout << "Distance to next POI = " << distance << " Kms (approx.)\n\n";
			poi.print();
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
 * TestCase to check if non existing POI is added to the route
 * @returnval void
 */
#ifdef RUN_TEST_CASE_NON_EXIST_POI
void CNavigationSystem::testCaseNonExistingPOI()
{
	//this->m_route.addPoi("My Chicken"		);
}
#endif


/**
 * TestCase to check if non existing Waypoint is added to the route
 * @returnval void
 */
#ifdef RUN_TEST_CASE_NON_EXIST_WAYPOINT
void CNavigationSystem::testCaseNonExistingWaypoint()
{
	this->m_route.addWaypoint("My Chicken"		);
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
