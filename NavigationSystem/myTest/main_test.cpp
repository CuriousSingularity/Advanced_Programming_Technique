/*
 * main.cpp
 *
 *  Created on: 11.09.2012
 *      Author: Michael
 */

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CAddPoi.h"
#include "CAddWaypointTest.h"
#include "CRouteTest.h"
#include "CPrintTest.h"
#include "COperatorOverloadingTest.h"
#include "CGetDistanceNextPoi.h"
#include "CConnectToPoiDatabaseTest.h"
#include "CConnectToWpDatabaseTest.h"

using namespace CppUnit;

int main (int argc, char* argv[]) {

	TextUi::TestRunner runner;

	runner.addTest( CRouteTest::suite() );
	runner.addTest( CConnectToWpDatabase::suite() );
	runner.addTest( CConnectToPoiDatabase::suite() );
	runner.addTest( CAddPoi::suite() );
	runner.addTest( CGetDistanceNextPoi::suite() );
	runner.addTest( CPrintTest::suite() );
	runner.addTest( COperatorOverloadingTest::suite() );
	runner.addTest( CAddWaypointTest::suite() );

	runner.run();

	return 0;
}
