
// Project	: 	NavigationSystem
// File		:	main.c
// Author	: 	Bharath Ramachandraiah

/* Header Files */
#include <iostream>
#include <iomanip>

using namespace std;

#include "CWaypoint.h"

int main (void)
{
	cout << "Navigation System:" << endl << endl;
	//cout << std::fixed << std::setprecision(4);

	// Solution (Exercise 1.1; section d):
	/*
		amsterdam
		Latitude: 52.3680 or 52 22' 4.8"
		Longitude: 4.9036 or 4 54' 12.9594"
	*/
	CWaypoint amsterdam("Amsterdam", 52.3680, 4.9036);

	/*
		darmstadt
		Latitude: 49.8728 or 49 52' 22.0794"
		Longitude: 8.6512 or 8 39' 4.3194"
	*/
	CWaypoint darmstadt("Darmstadt", 49.8728, 8.6512);

	/*
		berlin
		Latitude: 52.5200 or 52 31' 12"
		Longitude: 13.4050 or 24' 17.9994"
	 */
	CWaypoint berlin("Berlin", 52.5200, 13.4050);

	/*
		tokio
		Latitude: 35.6895 or 35 41' 22.2"
		Longitude: 139.6917 or 139 41' 30.1194"
	 */
	CWaypoint tokio("Tokyo", 35.6895, 139.6917);

	CWaypoint newWaypoint;

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

	cout << "==================================================\n";
	cout << "Exercise 1.1; section i\n";
	double Distance;

	Distance = amsterdam.calculateDistance(berlin);
	cout << "Distance between " << amsterdam.getName() << " and " << berlin.getName() << " : " << Distance << " KM\n";
	cout << "==================================================\n";
/*
	0	0	0	0		Berlin		(Latitude:  52.520007 | Longitude:  13.404954 )		Amsterdam	Latitude:  52.367984 | Longitude:   4.903561
	0	0	0	1		Berlin		(Latitude:  52.520007 | Longitude:  13.404954 )		New York	Latitude:  40.712775 | Longitude: -74.005973
	0	0	1	0		Berlin		(Latitude:  52.520007 | Longitude:  13.404954 )		Sydney		Latitude:  -33.86882 | Longitude: 151.209296
	0	0	1	1		Berlin		(Latitude:  52.520007 | Longitude:  13.404954 )		Rio			Latitude: -22.906847 | Longitude: -43.172896
	0	1	0	0		California	(Latitude:  36.778261 | Longitude: -119.417932)		Amsterdam	Latitude:  52.367984 | Longitude:   4.903561
	0	1	0	1		California  (Latitude:  36.778261 | Longitude: -119.417932)		New York	Latitude:  40.712775 | Longitude: -74.005973
	0	1	1	0		California  (Latitude:  36.778261 | Longitude: -119.417932)		Sydney		Latitude:  -33.86882 | Longitude: 151.209296
	0	1	1	1		California  (Latitude:  36.778261 | Longitude: -119.417932)		Rio			Latitude: -22.906847 | Longitude: -43.172896
	1	0	0	0		Melbourne	(Latitude: -37.813628 | Longitude:  144.963058)		Amsterdam	Latitude:  52.367984 | Longitude:   4.903561
	1	0	0	1		Melbourne   (Latitude: -37.813628 | Longitude:  144.963058)		New York	Latitude:  40.712775 | Longitude: -74.005973
	1	0	1	0		Melbourne   (Latitude: -37.813628 | Longitude:  144.963058)		Sydney		Latitude:  -33.86882 | Longitude: 151.209296
	1	0	1	1       Melbourne   (Latitude: -37.813628 | Longitude:  144.963058)		Rio			Latitude: -22.906847 | Longitude: -43.172896
	1	1	0	0		Argentina   (Latitude: -38.416097 | Longitude: -63.616672 )		Amsterdam	Latitude:  52.367984 | Longitude:   4.903561
	1	1	0	1		Argentina   (Latitude: -38.416097 | Longitude: -63.616672 )		New York	Latitude:  40.712775 | Longitude: -74.005973
	1	1	1	0		Argentina   (Latitude: -38.416097 | Longitude: -63.616672 )		Sydney		Latitude:  -33.86882 | Longitude: 151.209296
	1	1	1	1		Argentina   (Latitude: -38.416097 | Longitude: -63.616672 )		Rio			Latitude: -22.906847 | Longitude: -43.172896
*/

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

		cout << place1.getName() << "\tto\t" << place2.getName() << ": " << place1.calculateDistance(place2) << " Kms\n";
	}



	return 0;
}
