/*
 * CRouteTest.h
 */

#ifndef CADDWAYPOINTTEST_H_
#define CADDWAYPOINTTEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

class CAddWaypointTest: public CppUnit::TestFixture {
public:

	void testAddWpWithoutDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			// add a POI to the database
			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

			// do not connect the database
			porigin->connectToWpDatabase(0);

			// add a waypoint to the route
			porigin->addWaypoint("Berliner Alle");

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testAddWpWithDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			// add a POI to the database
			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

			// do not connect the database
			porigin->connectToWpDatabase(pWpDatabase);

			// add a waypoint to the route
			porigin->addWaypoint("Berliner Alle");

			CPPUNIT_ASSERT(1 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testAddWpInvalidWithDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			// add a POI to the database
			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

			// do not connect the database
			porigin->connectToWpDatabase(pWpDatabase);

			// add a waypoint to the route
			porigin->addWaypoint("Mensa");

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect Waypoint Database tests");

		suite->addTest(new CppUnit::TestCaller<CAddWaypointTest>
				 ("Add Waypoint without DB connection", &CAddWaypointTest::testAddWpWithoutDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddWaypointTest>
				 ("Add Waypoint with DB connection", &CAddWaypointTest::testAddWpWithDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddWaypointTest>
				 ("Add Invalid Waypoint with DB connection", &CAddWaypointTest::testAddWpInvalidWithDBConnection));

		return suite;
	}
};

#endif /* CADDWAYPOINTTEST_H_ */
