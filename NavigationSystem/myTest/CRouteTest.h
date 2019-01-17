/*
 * CRouteTest.h
 */

#ifndef CROUTETEST_H_
#define CROUTETEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute constructor method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CRouteTest: public CppUnit::TestFixture {
public:

	void testRouteTest() {
			CRoute* porigin 		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			*porigin += "HDA BuildingC10";

			porigin->addWaypoint("Berliner Alle");

			CPPUNIT_ASSERT(2 == porigin->getRoute().size());

			CRoute *pcurrentRoute	= new CRoute(*porigin);

			CPPUNIT_ASSERT(2 == pcurrentRoute->getRoute().size());

			delete porigin;
			delete pcurrentRoute;
			delete pWpDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect Waypoint Database tests");

		suite->addTest(new CppUnit::TestCaller<CRouteTest>
				 ("Copy constructor", &CRouteTest::testRouteTest));

		return suite;
	}
};

#endif /* CROUTETEST_H_ */
