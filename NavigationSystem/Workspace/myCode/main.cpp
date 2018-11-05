/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : main.cpp
* Author          : Bharath Ramachandraiah
* Description     : The entry file for the Navigation System Application.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <iomanip>

//Own Include Files
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CNavigationSystem.h"

//Namespaces
using namespace std;

//Macros
//#define RUN_TEST_CASE

#define LATITUDE_AMSTERDAM			52.3680
#define LONGITUDE_AMSTERDAM			4.9036
#define LATITUDE_DARMSTADT			49.8728
#define LONGITUDE_DARMSTADT			8.6512
#define LATITUDE_BERLIN				52.5200
#define LONGITUDE_BERLIN			13.4050
#define LATITUDE_TOKYO				35.6895
#define LONGITUDE_TOKYO				139.691

/**
 * main function:
 * An entry point to Navigation System Application.
 */
int main (void)
{
	cout << "Navigation System:" << endl << endl;

	// Set the precision to 6 decimal places
	cout << std::fixed << std::setprecision(6);

	// Solution (Exercise 1.1; section d):
	CWaypoint amsterdam("Amsterdam", LATITUDE_AMSTERDAM, LONGITUDE_AMSTERDAM);
	CWaypoint darmstadt("Darmstadt", LATITUDE_DARMSTADT, LONGITUDE_DARMSTADT);
	CWaypoint berlin("Berlin", LATITUDE_BERLIN, LONGITUDE_BERLIN);
	CWaypoint tokio("Tokyo", LATITUDE_TOKYO, LONGITUDE_TOKYO);
	CWaypoint newWaypoint;

	// Solution (Exercise 1.1; section f)
	cout << "==================================================\n";
	cout << "Exercise 1.1; section f\n";
	berlin.print(DEGREE);
	berlin.print(MMSS);
	cout << "==================================================\n";

	// Solution (Exercise 1.1; section g)
#ifdef RUN_TEST_CASE
	{
		cout << "==================================================\n";
		cout << "Exercise 1.1; section g\n";
		if ("Berlin" == berlin.getName())
		{
			cout << "TEST CASE: Get name from CWaypoint\t: PASS\n";
		}
		else
		{
			cout << "TEST CASE: Get name from CWaypoint\t: FAIL\n";
		}

		if (LATITUDE_BERLIN == berlin.getLatitude())
		{
			cout << "TEST CASE: Get Latitude from CWaypoint\t: PASS\n";
		}
		else
		{
			cout << "TEST CASE: Get Latitude from CWaypoint\t: FAIL\n";
		}

		if (LONGITUDE_BERLIN == berlin.getLongitude())
		{
			cout << "TEST CASE: Get Longitude from CWaypoint\t: PASS\n";
		}
		else
		{
			cout << "TEST CASE: Get Longitude from CWaypoint\t: FAIL\n";
		}
		cout << "==================================================\n";
	}
#endif

	// Solution (Exercise 1.1; section h)
#ifdef RUN_TEST_CASE
	{
		string name;
		double latitude, longitude;

		cout << "==================================================\n";
		cout << "Exercise 1.1; section h\n";

		tokio.getAllDataByReference(name, latitude, longitude);

#ifdef SHOWADRESS
		cout << "Local variables at addresses : \n";
		cout << "Attribute Name \t" <<"Attribute Address \t"<< "Attribute Size \t" 			<< "Attribute Value\n";
		cout << "name \t\t" 		<< &name 				<< "\t\t" << name.size() 		<< "\t\t" << name << "\n";
		cout << "latitude \t" 		<< &latitude 			<< "\t\t" << sizeof(latitude)	<< "\t\t" << latitude << "\n";
		cout << "longitude \t" 		<< &longitude 			<< "\t\t" << sizeof(longitude)	<< "\t\t" << longitude << "\n";
		cout << "==================================================\n";
#endif
	}
#endif

	// Solution (Exercise 1.1; section i)
#ifdef RUN_TEST_CASE
	{
		double distance;

		cout << "==================================================\n";
		cout << "Exercise 1.1; section i\n";

		distance = amsterdam.calculateDistance(berlin);
		cout << "Distance between " << amsterdam.getName() << " and " << berlin.getName() << " : " << distance << " Kms (approx.)\n";

		distance = berlin.calculateDistance(tokio);
		cout << "Distance between " << berlin.getName() << " and " << tokio.getName() << " : " << distance << " Kms (approx.)\n";
		cout << "==================================================\n";
	}
#endif

#ifdef RUN_TEST_CASE
	{
		struct Lookup_s
		{
			string name;
			double latitude;
			double longitude;
		};

		struct Lookup_s LookUpTable[][2] = {
			{{"Berlin	  " ,  52.520007 ,  13.404954 }	,	{"Amsterdam	" ,  52.367984 ,    4.903561 }},
			{{"Berlin	  " ,  52.520007 ,  13.404954 }	,	{"New York	" ,  40.712775 ,  -74.005973 }},
			{{"Berlin	  " ,  52.520007 ,  13.404954 }	,	{"Sydney(A)	" ,  -33.86882 ,  151.209296 }},
			{{"Berlin	  " ,  52.520007 ,  13.404954 }	,	{"Rio		" , -22.906847 ,  -43.172896 }},
			{{"California " ,  36.778261 , -119.417932}	,	{"Amsterdam	" ,  52.367984 ,    4.903561 }},
			{{"California " ,  36.778261 , -119.417932}	,	{"New York	" ,  40.712775 ,  -74.005973 }},
			{{"California " ,  36.778261 , -119.417932}	,	{"Sydney(A)	" ,  -33.86882 ,  151.209296 }},
			{{"California " ,  36.778261 , -119.417932}	,	{"Rio		" , -22.906847 ,  -43.172896 }},
			{{"Melbourne  " , -37.813628 ,  144.963058}	,	{"Amsterdam	" ,  52.367984 ,    4.903561 }},
			{{"Melbourne  " , -37.813628 ,  144.963058}	,	{"New York	" ,  40.712775 ,  -74.005973 }},
			{{"Melbourne  " , -37.813628 ,  144.963058}	,	{"Sydney(A)	" ,  -33.86882 ,  151.209296 }},
			{{"Melbourne  " , -37.813628 ,  144.963058}	,	{"Rio		" , -22.906847 ,  -43.172896 }},
			{{"Argentina  " , -38.416097 , -63.616672 }	,	{"Amsterdam	" ,  52.367984 ,    4.903561 }},
			{{"Argentina  " , -38.416097 , -63.616672 }	,	{"New York	" ,  40.712775 ,  -74.005973 }},
			{{"Argentina  " , -38.416097 , -63.616672 }	,	{"Sydney(A)	" ,  -33.86882 ,  151.209296 }},
			{{"Argentina  " , -38.416097 , -63.616672 }	,	{"Rio		" , -22.906847 ,  -43.172896 }},
		};

		cout << "Distance Test:" << endl;
		for (unsigned int index = 0; index < sizeof(LookUpTable)/(2 * sizeof(Lookup_s)); index++)
		{
			CWaypoint place1(LookUpTable[index][0].name, LookUpTable[index][0].latitude, LookUpTable[index][0].longitude);
			CWaypoint place2(LookUpTable[index][1].name, LookUpTable[index][1].latitude, LookUpTable[index][1].longitude);

			cout << place1.getName() << "\tto\t" << place2.getName() << ": " << place1.calculateDistance(place2) << " Kms (approx.)\n";
		}
	}
#endif
#ifdef TESTCASE
	CPOI poi_testcase_1(RESTAURANT, "KFC", "KFC near Lusienplatz", 12, 11.5);
	CPOI poi_testcase_2(RESTAURANT, "", "", 12, 11.5);

	poi_testcase_1.print();
	poi_testcase_2.print();
#endif

	CNavigationSystem navigationSystem;

	navigationSystem.run();

	return 0;
}
