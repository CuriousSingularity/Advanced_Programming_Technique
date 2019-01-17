/*
 * CRouteTest.h
 */

#ifndef CPRINT_H_
#define CPRINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's print method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CPrintTest: public CppUnit::TestFixture {
public:

	void testPrintRoute() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			porigin->addWaypoint("Berliner Alle");
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
