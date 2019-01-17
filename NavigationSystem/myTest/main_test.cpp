/*
 * main.cpp
 *
 *  Created on: 11.09.2012
 *      Author: Michael
 */

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "CAddPoiTest.h"
#include "CAddWaypointTest.h"
#include "CRouteTest.h"
#include "CPrintTest.h"
#include "COperatorOverloadingTest.h"
#include "CGetDistanceNextPoiTest.h"
#include "CConnectToPoiDatabaseTest.h"
#include "CConnectToWpDatabaseTest.h"

using namespace CppUnit;

/**
 * Test cases entry point
 */
int main (int argc, char* argv[]) {

	TextUi::TestRunner runner;

	runner.addTest( CRouteTest::suite() );
	runner.addTest( CConnectToWpDatabase::suite() );
	runner.addTest( CConnectToPoiDatabase::suite() );
	runner.addTest( CAddPoiTest::suite() );
	runner.addTest( CGetDistanceNextPoiTest::suite() );
	runner.addTest( CPrintTest::suite() );
	runner.addTest( COperatorOverloadingTest::suite() );
	runner.addTest( CAddWaypointTest::suite() );

	runner.run();

	return 0;
}
