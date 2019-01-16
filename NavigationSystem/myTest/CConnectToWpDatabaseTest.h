/*
 * CConnectToWpDatabase.h
 */

#ifndef CCONNECTTOWPDATABASE_H_
#define CCONNECTTOWPDATABASE_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../myCode/CRoute.h"

class CConnectToWpDatabase: public CppUnit::TestFixture {
public:

	void testdontConnectToWpDatabase() {
		CRoute* pcurrentRoute 		= new CRoute;
		CWpDatabase *pWpDatabase 	= new CWpDatabase;

		// add a Wp to the database
		pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

		// do not connect the database
		pcurrentRoute->connectToWpDatabase(0);

		// add a Wp to the route
		*pcurrentRoute += "Berliner Alle";

		CPPUNIT_ASSERT(0 == pcurrentRoute->getRoute().size());

		delete pcurrentRoute;
		delete pWpDatabase;
	}

	void testconnectToWpDatabase() {
			CRoute* pcurrentRoute 		= new CRoute;
			CWpDatabase *pWpDatabase 	= new CWpDatabase;

			// add a Wp to the database
			pWpDatabase->addWaypoint("Berliner Alle", CWaypoint("Berliner Alle", 49.866851, 8.634864));

			// do not connect the database
			pcurrentRoute->connectToWpDatabase(pWpDatabase);

			// add a Wp to the route
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
