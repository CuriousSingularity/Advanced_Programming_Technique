/*
 * CConnectToWpDatabase.h
 */

#ifndef CCONNECTTOWPDATABASE_H_
#define CCONNECTTOWPDATABASE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to the CRoute's connectToWpDatabase method.
 * Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CConnectToWpDatabase: public CppUnit::TestFixture {
public:

	void testdontConnectToWpDatabase() {
		CRoute* pcurrentRoute 		= new CRoute;
		CWpDatabase *pWpDatabase 	= new CWpDatabase;

		pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

		pcurrentRoute->connectToWpDatabase(0);
		*pcurrentRoute += "Berliner Alle";

		CPPUNIT_ASSERT(0 == pcurrentRoute->getRoute().size());

		delete pcurrentRoute;
		delete pWpDatabase;
	}

	void testconnectToWpDatabase() {
			CRoute* pcurrentRoute 		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;

			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));
			pcurrentRoute->connectToWpDatabase(pWpDatabase);

			pcurrentRoute->addWaypoint("Berliner Alle");

			CPPUNIT_ASSERT(0 != pcurrentRoute->getRoute().size());

			delete pcurrentRoute;
			delete pWpDatabase;
		}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect Waypoint Database tests");

		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabase>
				 ("Don't connect the database to route", &CConnectToWpDatabase::testdontConnectToWpDatabase));

		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabase>
				 ("Connect the database to route", &CConnectToWpDatabase::testconnectToWpDatabase));

		return suite;
	}
};

#endif /* CCONNECTTOWPDATABASE_H_ */
