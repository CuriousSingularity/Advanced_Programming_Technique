/*
 * CRouteTest.h
 */

#ifndef GETDISTANCENEXTPOI_H_
#define GETDISTANCENEXTPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

class CGetDistanceNextPoi: public CppUnit::TestFixture {
public:

	void testGetDistanceNextPoiEmptyRoute() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;
			CPOI *pPoi					= new CPOI;
			CWaypoint *pWp				= new CWaypoint;

			// add a POI to the database
			*pWp = CWaypoint("Berliner Alle", 49.866851, 8.634864);

			// do not connect the database
			porigin->connectToWpDatabase(pWpDatabase);

			// do not connect the database
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

			// add a POI to the database
			*pWp = CWaypoint("Berliner Alle", 49.866851, 8.634864);

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

			distance = porigin->getDistanceNextPoi(*pWp, *pPoi);

			CPPUNIT_ASSERT(distance == pPoi->CWaypoint::calculateDistance(*pWp));

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Get distance tests");

		suite->addTest(new CppUnit::TestCaller<CGetDistanceNextPoi>
				 ("Get Distance when route is empty", &CGetDistanceNextPoi::testGetDistanceNextPoiEmptyRoute));

		suite->addTest(new CppUnit::TestCaller<CGetDistanceNextPoi>
				 ("Get Distance", &CGetDistanceNextPoi::testGetDistanceNextPoiRoute));

		return suite;
	}
};

#endif /* GETDISTANCENEXTPOI_H_ */
