/*
 * CRouteTest.h
 */

#ifndef COPERATOROVERLOADINGTEST_H_
#define COPERATOROVERLOADINGTEST_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's operator overloading methods.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class COperatorOverloadingTest: public CppUnit::TestFixture {
public:

	void testOperatorPlusEqualWithDB() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			*porigin += "Berliner Alle";
			*porigin += "HDA BuildingC10";

			CPPUNIT_ASSERT(2 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testOperatorPlusEqualWithoutDB() {
			CRoute* porigin 			= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(0);
			porigin->connectToPoiDatabase(0);

			*porigin += "Berliner Alle";
			*porigin += "HDA BuildingC10";

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			delete porigin;
			delete pWpDatabase;
			delete pPOIDatabase;
		}

	void testOperatorEqual() {
			CRoute* porigin 			= new CRoute;
			CRoute *pcurrentRoute		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			*porigin += "HDA BuildingC10";
			porigin->addWaypoint("Berliner Alle");

			CPPUNIT_ASSERT(pcurrentRoute->getRoute().size() != porigin->getRoute().size());

			*pcurrentRoute	= *porigin;

			CPPUNIT_ASSERT(pcurrentRoute->getRoute().size() == porigin->getRoute().size());

			delete porigin;
			delete pcurrentRoute;
			delete pWpDatabase;
		}

	void testOperatorPlus() {
			CRoute* porigin 			= new CRoute;
			CRoute *pcurrentRoute		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(pWpDatabase);
			porigin->connectToPoiDatabase(pPOIDatabase);

			pcurrentRoute->connectToWpDatabase(pWpDatabase);
			pcurrentRoute->connectToPoiDatabase(pPOIDatabase);

			*porigin += "HDA BuildingC10";
			pcurrentRoute->addWaypoint("Berliner Alle");
			*pcurrentRoute = *pcurrentRoute + *porigin;

			CPPUNIT_ASSERT(2 == pcurrentRoute->getRoute().size());

			delete porigin;
			delete pcurrentRoute;
			delete pWpDatabase;
		}

	void testOperatorPlusDiffDB() {
			CRoute* porigin 			= new CRoute;
			CRoute *pcurrentRoute		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			porigin->connectToWpDatabase(0);
			porigin->connectToPoiDatabase(pPOIDatabase);
			*porigin += "HDA BuildingC10";

			pcurrentRoute->connectToWpDatabase(pWpDatabase);
			pcurrentRoute->connectToPoiDatabase(0);
			pcurrentRoute->addWaypoint("Berliner Alle");

			*pcurrentRoute 	= *pcurrentRoute + *porigin;
			*porigin 		= *porigin + *pcurrentRoute;

			CPPUNIT_ASSERT(0 == pcurrentRoute->getRoute().size());
			CPPUNIT_ASSERT(0 == porigin->getRoute().size());

			delete porigin;
			delete pcurrentRoute;
			delete pWpDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Operator Overloading tests");

		suite->addTest(new CppUnit::TestCaller<COperatorOverloadingTest>
				 ("Operator-Plus-Equal with Database", &COperatorOverloadingTest::testOperatorPlusEqualWithDB));

		suite->addTest(new CppUnit::TestCaller<COperatorOverloadingTest>
				 ("Operator-Plus-Equal without Database", &COperatorOverloadingTest::testOperatorPlusEqualWithoutDB));

		suite->addTest(new CppUnit::TestCaller<COperatorOverloadingTest>
				 ("Operator-Equal", &COperatorOverloadingTest::testOperatorEqual));

		suite->addTest(new CppUnit::TestCaller<COperatorOverloadingTest>
				 ("Operator-Plus", &COperatorOverloadingTest::testOperatorPlus));

		suite->addTest(new CppUnit::TestCaller<COperatorOverloadingTest>
				 ("Operator-Plus Different Database", &COperatorOverloadingTest::testOperatorPlusDiffDB));

		return suite;
	}
};

#endif /* COPERATOROVERLOADINGTEST_H_ */
