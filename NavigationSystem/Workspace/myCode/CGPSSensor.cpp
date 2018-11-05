/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSensor.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CGPSSensor.
* 					The class CGPSSensor is used to receive the current
* 					location from GPS sensor.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <limits>

//Own Include Files
#include "CGPSSensor.h"

//Namespace
using namespace std;


//Method Implementations
/**
 * CGPSSensor constructor
 */
CGPSSensor::CGPSSensor()
{
	// Do Nothing
}


/**
 * Get the current position from the sensor
 * @returnval CWaypoint
 */
CWaypoint CGPSSensor::getCurrentPosition()
{
	double latitude = 0, longitude = 0;
	CWaypoint gpsSensorValue;

	cout << "GPS Sensor\n";

	do
	{
		cout << "\tEnter latitude: \t";
		cin >> latitude;

		if (!cin.fail())
			break;

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Input, please enter a number.\n";

	} while (1);

	do
	{
		cout << "\tEnter longitude: \t";
		cin >> longitude;

		if (!cin.fail())
			break;

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Input, please enter a number.\n";

	} while (1);

	gpsSensorValue.set("Current Position", latitude, longitude);

	return gpsSensorValue;
}
