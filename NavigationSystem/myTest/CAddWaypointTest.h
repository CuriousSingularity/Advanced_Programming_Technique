/*
 * CRouteTest.h
 */

#ifndef CADDWAYPOINTTEST_H_
#define CADDWAYPOINTTEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's addWaypoint method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CAddWaypointTest: public CppUnit::TestFixture {
public:

	void testAddWpWithoutDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			porigin->connectToWpDatabase(0);
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

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			porigin->connectToWpDatabase(pWpDatabase);
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

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			porigin->connectToWpDatabase(pWpDatabase);
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
