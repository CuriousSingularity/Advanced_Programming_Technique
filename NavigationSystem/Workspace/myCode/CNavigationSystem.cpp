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
CNavigationSystem::CNavigationSystem() : m_route(8, 8)
{
	this->m_route.connectToPoiDatabase(&this->m_PoiDatabase);
}


/**
 * Navigation System functionaliy's entry function
 * @returnval void
 */
void CNavigationSystem::run()
{
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
	this->m_route.addWaypoint(CWaypoint("Berliner Alle", 			49.866851, 	8.634864));
	this->m_route.addWaypoint(CWaypoint("Rheinstraße", 				49.870267, 	8.633266));
	this->m_route.addWaypoint(CWaypoint("Neckarstraße", 			49.8717, 	8.644417));
	this->m_route.addWaypoint(CWaypoint("Landskronstraße", 			49.853308,	8.646835));
	this->m_route.addWaypoint(CWaypoint("Bessunger", 				49.846994,	8.646193));
	this->m_route.addWaypoint(CWaypoint("FriedrichStraße",	 		49.838545,	8.645571));
	this->m_route.addWaypoint(CWaypoint("Katharinen Str.", 			49.824827,	8.644529));
	this->m_route.addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));

#ifdef RUN_TEST_CASE_MORE_WAYPOINTS
	testCaseAddMoreWaypoints();
#endif

	// add POIs
	this->m_route.addPoi("HDA BuildingC10"	);
	this->m_route.addPoi("Aral Tankst."		);
	this->m_route.addPoi("Starbucks"		);
	this->m_route.addPoi("SushiRestaurant"	);
	this->m_route.addPoi("Aral Tankstelle"	);
	this->m_route.addPoi("Church Holy"		);
	this->m_route.addPoi("Thessaloniki"		);

#ifdef RUN_TEST_CASE_NON_EXIST_POI
	testCaseNonExistingPOI();
#endif

	this->m_route.addPoi("Church 7 Days"	);

#ifdef RUN_TEST_CASE_MORE_POIS
	testCaseAddMorePOIs();
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
 * TestCase to check if more waypoints are added when the memory is not available
 * @returnval void
 */
#ifdef RUN_TEST_CASE_MORE_WAYPOINTS
void CNavigationSystem::testCaseAddMoreWaypoints()
{
	this->m_route.addWaypoint(CWaypoint("PfungstädterStr",	 		49.817379,	8.644088));
	this->m_route.addWaypoint(CWaypoint("Büschelstraße", 			49.815069,	8.644614));
	this->m_route.addWaypoint(CWaypoint("Seeheimer Str.", 			49.813681,	8.646337));
	this->m_route.addWaypoint(CWaypoint("Heidelberger Landstrasse", 49.80687 ,	8.641321));
}
#endif


/**
 * TestCase to check if more POIs are added when the memory is not available
 * @returnval void
 */
#ifdef RUN_TEST_CASE_MORE_POIS
void CNavigationSystem::testCaseAddMorePOIs()
{
	this->m_route.addPoi("Ladestation"		);
	this->m_route.addPoi("El Quinto Vino"	);
}
#endif


/**
 * TestCase to check if POI is not available in Database
 * @returnval void
 */
#ifdef RUN_TEST_CASE_NON_EXIST_POI
void CNavigationSystem::testCaseNonExistingPOI()
{
	this->m_route.addPoi("My Chicken"		);
}
#endif
