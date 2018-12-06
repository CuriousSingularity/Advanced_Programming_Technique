/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNavigationSystem.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CNavigationSystem.
* 					The class CNavigationSystem is used for Navigation which
* 					has a GPS Sensor, Route and a Database.
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H

//System Include Files

//Own Include Files
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"

//Macros
//#define RUN_TEST_ROUTE_OPERATOR_ASSIGNMENT
//#define RUN_TEST_ROUTE_OPERATOR_ADDITION
//#define RUN_TEST_CASE_NON_EXIST_POI
//#define RUN_TEST_CASE_NON_EXIST_WAYPOINT
//#define RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_POI
//#define RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_WAYPOINT

class CNavigationSystem {
private:

	/**
	 * GPS sensor which feeds the current location
	 */
    CGPSSensor 		m_GPSSensor;

    /**
	 * Navigation System's current route
	 */
    CRoute 			m_route;

    /**
	 * The Database of points of interest
	 */
    CPoiDatabase 	m_PoiDatabase;

    /**
	 * The Database of waypoint
	 */
    CWpDatabase 	m_WpDatabase;

    /**
     * Get the Poi Database
     * returnval@ CPoiDatabase&	- Reference to the POI Database
     */
    CPoiDatabase& getPoiDatabase();

    /**
     * Get the Waypoint Database
     * returnval@ CWpDatabase&	- Reference to the Waypoint Database
     */
    CWpDatabase& getWpDatabase();

    /**
	 * Add waypoints and POIs to create custom route
	 * @returnval void
	 */
    void enterRoute();

    /**
	 * Print all the waypoints and POIs of the custom route
	 * @returnval void
	 */
    void printRoute();

    /**
	 * Print the Distance between current position and a closest POI
	 * @returnval void
	 */
	void printDistanceCurPosNextPoi();

    /**
	 * Creates Waypoint Database and Poi Database
	 * @returnval void
	 */
    void createDatabases();

    /**
	 * Write the current content of Databases to files
	 * @returnval void
	 */
	bool writeToFile();

	/**
	 * Read the Database content from file to Databases
	 * @returnval void
	 */
	bool readFromFile();

    /**
	 * TestCase to check if non existing POI is added to the route
	 * @returnval void
	 */
#ifdef RUN_TEST_CASE_NON_EXIST_POI
    void testCaseNonExistingPOI();
#endif

    /**
	 * TestCase to check if non existing Waypoint is added to the route
	 * @returnval void
	 */
#ifdef RUN_TEST_CASE_NON_EXIST_WAYPOINT
    void testCaseNonExistingWaypoint();
#endif

    /**
	 * TestCase to check when POI database is not available
	 * @returnval void
	 */
#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_POI
    void testCaseDatabaseNotAvailablePoi();
#endif

    /**
	 * TestCase to check when Waypoint database is not available
	 * @returnval void
	 */
#ifdef RUN_TEST_CASE_DATABASE_NOT_AVAILABLE_WAYPOINT
    void testCaseDatabaseNotAvailableWaypoint();
#endif

public:

    /**
	 * Constructor
	 */
    CNavigationSystem();

    /**
	 * Navigation System functionaliy's entry function
	 * @returnval void
	 */
    void run();

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
