/*
 * CRouteTest.h
 */

#ifndef CPRINT_H_
#define CPRINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

class CPrintTest: public CppUnit::TestFixture {
public:

	void testPrintRoute() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

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

			porigin->print();

			CPPUNIT_ASSERT(2 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Print route tests");

		suite->addTest(new CppUnit::TestCaller<CPrintTest>
				 ("Print the route", &CPrintTest::testPrintRoute));

		return suite;
	}
};

#endif /* CPRINT_H_ */
