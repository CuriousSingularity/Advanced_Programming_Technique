/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>

using namespace std;
//Own Include Files
#include "CGPSSensor.h"
#include "CWaypoint.h"

//Method Implementations
/**
 * CGPSSensor constructor
 */
CGPSSensor::CGPSSensor()
{
	// Nothing
}


/**
 * Get the current position from the sensor
 * @returnval CWaypoint
 */
CWaypoint CGPSSensor::getCurrentPosition()
{
	double latitude = 360, longitude = 360;		// initializing to invalid values
	CWaypoint gpsSensorValue;

	cout << "GPS Sensor\n";
	cout << "\tEnter latitude: \n";
	cin >> latitude;
	cout << "\tEnter longitude: \n";
	cin >> longitude;

	gpsSensorValue.set("Current Position", latitude, longitude);

	return gpsSensorValue;

#if 0
	do
	{
		cout << "GPS Sensor\n";
		cout << "\tEnter latitude: \n";
		cin >> latitude;
		cout << "\tEnter longitude: \n";
		cin >> longitude;

		// check if the value entered is valid co-ordinates
		if ((latitude >= LATITUDE_MIN) && (latitude <= LATITUDE_MAX) &&
				(longitude >= LONGITUDE_MIN) && (longitude <= LONGITUDE_MAX))
		{
			break;
		}
		else
		{
			cout << "Invalid sensor value" << endl;
		}
	}
	while(1);
#endif

}
