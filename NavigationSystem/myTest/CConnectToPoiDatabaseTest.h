/*
 * CConnectToPoiDatabase.h
 */

#ifndef CCONNECTTOPOIDATABASE_H_
#define CCONNECTTOPOIDATABASE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's connectToPoiDatabase method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */

class CConnectToPoiDatabase: public CppUnit::TestFixture {
public:

	void testdontConnectToPoiDatabase() {
		CRoute* pcurrentRoute 		= new CRoute;
		CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

		pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

		pcurrentRoute->connectToPoiDatabase(0);
		*pcurrentRoute += "HDA BuildingC10";

		CPPUNIT_ASSERT(0 == pcurrentRoute->getRoute().size());

		delete pcurrentRoute;
		delete pPOIDatabase;
	}

	void testconnectToPoiDatabase() {
			CRoute* pcurrentRoute 		= new CRoute;
			CPoiDatabase *pPOIDatabase 	= new CPoiDatabase;

			pPOIDatabase->addPoi("HDA BuildingC10", CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 49.86727, 8.638459));

			pcurrentRoute->connectToPoiDatabase(pPOIDatabase);
			pcurrentRoute->addPoi("HDA BuildingC10", "Mensa");

			CPPUNIT_ASSERT(0 != pcurrentRoute->getRoute().size());

			delete pcurrentRoute;
			delete pPOIDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect POI Database tests");

		suite->addTest(new CppUnit::TestCaller<CConnectToPoiDatabase>
				 ("Don't connect the database to route", &CConnectToPoiDatabase::testdontConnectToPoiDatabase));

		suite->addTest(new CppUnit::TestCaller<CConnectToPoiDatabase>
				 ("Connect the database to route", &CConnectToPoiDatabase::testconnectToPoiDatabase));

		return suite;
	}
};

#endif /* CCONNECTTOPOIDATABASE_H_ */
