/*
 * CRouteTest.h
 */

#ifndef GETDISTANCENEXTPOITEST_H_
#define GETDISTANCENEXTPOITEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's getDistanceNextPoi method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */

class CGetDistanceNextPoiTest: public CppUnit::TestFixture {
public:

	void testGetDistanceNextPoiEmptyRoute() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;
			CPOI *pPoi					= new CPOI;
			CWaypoint *pWp				= new CWaypoint;

			*pWp = CWaypoint("Berliner Alle", 49.866851, 8.634864);

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			CPPUNIT_ASSERT(!pPoi->getPoiTypeName().compare("Default"));

			porigin->getDistanceNextPoi(*pWp, *pPoi);

			CPPUNIT_ASSERT(!pPoi->getPoiTypeName().compare("Default"));

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testGetDistanceNextPoiRoute() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;
			CPOI *pPoi					= new CPOI;
			CWaypoint *pWp				= new CWaypoint;
			double 						distance;

			*pWp = CWaypoint("Berliner Alle", 49.866851, 8.634864);

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			porigin->addWaypoint("Berliner Alle");
			porigin->addPoi("HDA BuildingC10", "Berliner Alle");

			distance = porigin->getDistanceNextPoi(*pWp, *pPoi);

			CPPUNIT_ASSERT(distance == pPoi->CWaypoint::calculateDistance(*pWp));

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Get distance tests");

		suite->addTest(new CppUnit::TestCaller<CGetDistanceNextPoiTest>
				 ("Get Distance when route is empty", &CGetDistanceNextPoiTest::testGetDistanceNextPoiEmptyRoute));

		suite->addTest(new CppUnit::TestCaller<CGetDistanceNextPoiTest>
				 ("Get Distance", &CGetDistanceNextPoiTest::testGetDistanceNextPoiRoute));

		return suite;
	}
};

#endif /* GETDISTANCENEXTPOITEST_H_ */
