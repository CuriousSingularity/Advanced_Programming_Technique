/*
 * CRouteTest.h
 */

#ifndef CADDPOITEST_H_
#define CADDPOITEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's addPoi method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CAddPoiTest: public CppUnit::TestFixture {
public:

	void testAddPoiWithoutDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(0);
			porigin->connectToPoiDatabase(0);
			porigin->addWaypoint("Berliner Alle");
			porigin->addPoi("HDA BuildingC10", "Berliner Alle");

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testAddPoiWithDBConnection() {
				CRoute* porigin 			= new CRoute;
				CWpDatabase *pWpDatabase 	= new CWpDatabase;
				CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

				CPPUNIT_ASSERT(0 == porigin->getRoute().size());

				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

				pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));
				porigin->connectToWpDatabase(pWpDatabase);
				porigin->connectToPoiDatabase(pPOIDatabase);
				porigin->addWaypoint("Berliner Alle");
				porigin->addPoi("HDA BuildingC10", "Berliner Alle");

				CPPUNIT_ASSERT(2 == porigin->getRoute().size());

				delete porigin;
				delete pWpDatabase;
				delete pPOIDatabase;
			}

	void testAddPoiWithoutPoiInDB() {
				CRoute* porigin 			= new CRoute;
				CWpDatabase *pWpDatabase 	= new CWpDatabase;
				CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

				CPPUNIT_ASSERT(0 == porigin->getRoute().size());

				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
				porigin->connectToWpDatabase(pWpDatabase);
				porigin->connectToPoiDatabase(pPOIDatabase);
				porigin->addWaypoint("Berliner Alle");

				CPPUNIT_ASSERT(1 == porigin->getRoute().size());

				porigin->addPoi("Mensa", "Berliner Alle");

				CPPUNIT_ASSERT(1 == porigin->getRoute().size());

				delete porigin;
				delete pWpDatabase;
				delete pPOIDatabase;
			}

	void testAddPoiWithoutWpInDB() {
				CRoute* porigin 			= new CRoute;
				CWpDatabase *pWpDatabase 	= new CWpDatabase;
				CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

				CPPUNIT_ASSERT(0 == porigin->getRoute().size());

				pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));
				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
				porigin->connectToWpDatabase(pWpDatabase);
				porigin->connectToPoiDatabase(pPOIDatabase);

				porigin->addWaypoint("Berliner Alle");

				CPPUNIT_ASSERT(1 == porigin->getRoute().size());

				porigin->addPoi("HDA BuildingC10", "Mensa");

				CPPUNIT_ASSERT(2 == porigin->getRoute().size());

				delete porigin;
				delete pWpDatabase;
				delete pPOIDatabase;
			}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect Waypoint Database tests");

		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add POI without DB connection", &CAddPoiTest::testAddPoiWithoutDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add POI with DB connection", &CAddPoiTest::testAddPoiWithDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add invalid POI to the route", &CAddPoiTest::testAddPoiWithoutPoiInDB));

		suite->addTest(new CppUnit::TestCaller<CAddPoiTest>
				 ("Add invalid Waypoint to the route", &CAddPoiTest::testAddPoiWithoutWpInDB));

		return suite;
	}
};

#endif /* CADDPOITEST_H_ */
