
// Project	: 	NavigationSystem
// File		:	main.c
// Author	: 	Bharath Ramachandraiah

/* Header Files */
#include <iostream>
#include <iomanip>

using namespace std;

#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"
#include "CNavigationSystem.h"

int main (void)
{
#if 0
	cout << "Navigation System:" << endl << endl;
	//cout << std::fixed << std::setprecision(4);

	// Solution (Exercise 1.1; section d):
	CWaypoint amsterdam("Amsterdam", 52.3680, 4.9036);
	CWaypoint darmstadt("Darmstadt", 49.8728, 8.6512);
	CWaypoint berlin("Berlin", 52.5200, 13.4050);
	CWaypoint tokio("Tokyo", 35.6895, 139.6917);
	CWaypoint newWaypoint;

#ifdef TESTCASE
	CWaypoint wp("", 10, 20);

	wp.print(MMSS);
#endif

	// Exercise 1.1 ; section f
	cout << "==================================================\n";
	cout << "Exercise 1.1; section f\n";
	berlin.print(DEGREE);
	berlin.print(MMSS);
	cout << "==================================================\n";

	// Exercise 1.1 ; section g
	// TODO
	// Exercise 1.1 ; section h
	string name;
	double latitude, longitude;

	cout << "==================================================\n";
	cout << "Exercise 1.1; section h\n";

	tokio.getAllDataByReference(name, latitude, longitude);

	cout << "==================================================\n";
	cout << "Local variables created at addresses : \n";
	cout << "Attribute Name \t" <<"Attribute Address \t"<< "Attribute Size \t" 			<< "Attribute Value\n";
	cout << "name \t\t" 		<< &name 				<< "\t\t" << name.size() 		<< "\t\t" << name << "\n";
	cout << "latitude \t" 		<< &latitude 			<< "\t\t" << sizeof(latitude)	<< "\t\t" << latitude << "\n";
	cout << "longitude \t" 		<< &longitude 			<< "\t\t" << sizeof(longitude)	<< "\t\t" << longitude << "\n";
	cout << "==================================================\n";

	// Exercise 1.1 ; section i
	cout << "==================================================\n";
	cout << "Exercise 1.1; section i\n";
	double Distance;

	Distance = amsterdam.calculateDistance(berlin);
	cout << "Distance between " << amsterdam.getName() << " and " << berlin.getName() << " : " << Distance << " Kms (approx.)\n";

	Distance = berlin.calculateDistance(tokio);
	cout << "Distance between " << berlin.getName() << " and " << tokio.getName() << " : " << Distance << " Kms (approx.)";
	cout << "==================================================\n";

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
