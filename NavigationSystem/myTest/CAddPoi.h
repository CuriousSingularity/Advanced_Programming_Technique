/*
 * CRouteTest.h
 */

#ifndef CADDPOI_H_
#define CADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

class CAddPoi: public CppUnit::TestFixture {
public:

	void testAddPoiWithoutDBConnection() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			// add a POI to the database
			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

			// add a POI to the database
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			// do not connect the database
			porigin->connectToWpDatabase(0);

			// do not connect the database
			porigin->connectToPoiDatabase(0);

			// add a waypoint to the route
			porigin->addWaypoint("Berliner Alle");

			// add a POI to the route
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

				// add a POI to the database
				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

				// add a POI to the database
				pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

				// do not connect the database
				porigin->connectToWpDatabase(pWpDatabase);

				// do not connect the database
				porigin->connectToPoiDatabase(pPOIDatabase);

				// add a waypoint to the route
				porigin->addWaypoint("Berliner Alle");

				// add a POI to the route
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

				// add a wp to the database
				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

				// do not connect the database
				porigin->connectToWpDatabase(pWpDatabase);

				// do not connect the database
				porigin->connectToPoiDatabase(pPOIDatabase);

				// add a waypoint to the route
				porigin->addWaypoint("Berliner Alle");

				CPPUNIT_ASSERT(1 == porigin->getRoute().size());

				// add an invalid poi not present in the database
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

				// add a POI to the database
				pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

				// add a POI to the database
				pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

				// do not connect the database
				porigin->connectToWpDatabase(pWpDatabase);

				// do not connect the database
				porigin->connectToPoiDatabase(pPOIDatabase);

				// add a waypoint to the route
				porigin->addWaypoint("Berliner Alle");

				CPPUNIT_ASSERT(1 == porigin->getRoute().size());

				// add an invalid poi not present in the database
				porigin->addPoi("HDA BuildingC10", "Mensa");

				CPPUNIT_ASSERT(2 == porigin->getRoute().size());

				delete porigin;
				delete pWpDatabase;
				delete pPOIDatabase;
			}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect Waypoint Database tests");

		suite->addTest(new CppUnit::TestCaller<CAddPoi>
				 ("Add POI without DB connection", &CAddPoi::testAddPoiWithoutDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddPoi>
				 ("Add POI with DB connection", &CAddPoi::testAddPoiWithDBConnection));

		suite->addTest(new CppUnit::TestCaller<CAddPoi>
				 ("Add invalid POI to the route", &CAddPoi::testAddPoiWithoutPoiInDB));

		suite->addTest(new CppUnit::TestCaller<CAddPoi>
				 ("Add invalid Waypoint to the route", &CAddPoi::testAddPoiWithoutWpInDB));

		return suite;
	}
};

#endif /* CADDPOI_H_ */
