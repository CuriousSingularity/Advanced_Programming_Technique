/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWaypoint.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CWaypoint
*
*
****************************************************************************/
//System Include Files
#include <iostream>
#include <math.h>

//Namespaces
using namespace std;

//Own Include Files
#include "CWaypoint.h"

//Macros
#define M_PI						(atan(1) * 4)
#define degToRad(angleInDegrees) 	((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) 	((angleInRadians) * 180.0 / M_PI)

//Method Implementations

/**
 * CWaypoint constructor:
 * Sets the value of any object when created
 * param@ string name		-	name of a Waypoint 		(IN)
 * param@ double latitude	-	latitude of a Waypoint 	(IN)
 * param@ double longitude	-	longitude of a Waypoint (IN)
 */
CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	// Solution (Exercise 1.1; section c):
	// set the class data members with the parameters values passed during an object creation.
	this->set(name, latitude, longitude);

#ifdef SHOWADRESS

	cout << "A CWaypoint Object has be created at address : " << this << endl;
	cout << "Attribute Name \t" <<"Attribute Address \t"<< 			"Attribute Size \t" 		<< "Attribute Value\n";

	/*
	 * Solution (Exercise 1.1; section c):
	 * Data occupied by different attributes are as follows:
	 * Data occupied by "m_name" 		= number of character string
	 * Data occupied by "m_latitude" 	= 8 bytes since it is of type double
	 * Data occupied by "m_longitude" 	= 8 bytes since it is of type double
	 */
	cout << "m_name \t\t" 		<< &this->m_name 		<< "\t\t" << this->m_name.size() 		<< "\t\t" << this->m_name << "\n";
	cout << "m_latitude \t" 	<< &this->m_latitude 	<< "\t\t" << sizeof(this->m_latitude)	<< "\t\t" << this->m_latitude << "\n";
	cout << "m_longitude \t" 	<< &this->m_longitude 	<< "\t\t" << sizeof(this->m_longitude)	<< "\t\t" << this->m_longitude << "\n\n";

#endif
}


/**
 * Sets the current waypoint co-ordinate values
 * param@ string name		-	name of a Waypoint		(IN)
 * param@ double latitude	-	latitude of a Waypoint	(IN)
 * param@ double longitude	-	longitude of a Waypoint	(IN)
 * returnvalue@ void
 */
void CWaypoint::set(string name, double latitude, double longitude)
{
	// Solution (Exercise 1.1; section b):
	if (((latitude >= LATITUDE_MIN) && (latitude <= LATITUDE_MAX)) &&
		((longitude >= LONGITUDE_MIN) && (longitude <= LONGITUDE_MAX)) &&
		(!name.empty()))
	{
		// All the parameters values are valid; we can assign these values to the respective data members of the class
		this->m_name 		= name;
		this->m_latitude 	= latitude;
		this->m_longitude 	= longitude;
	}
	else
	{
		// some of the parameters values are invalid, hence set the values default to 0
		this->m_name 		= "";
		this->m_latitude 	= 0;
		this->m_longitude 	= 0;
	}
}


/**
 * Return the current waypoint co-ordinate name
 * retuvalue@ string name	-	name of a Waypoint
 */
string CWaypoint::getName()
{
	return (this->m_name);
}


/**
 * Return the current waypoint latitude
 * returnvalue@ double latitude	-	latitude of a Waypoint
 */
double CWaypoint::getLatitude()
{
	return (this->m_latitude);
}


/**
 * Return the current waypoint longitude
 * returnvalue@ double longitude-	longitude of a Waypoint
 */
double CWaypoint::getLongitude()
{
	return (this->m_longitude);
}


/**
 * Return the current waypoint co-ordinate values
 * param@ string& name		-	name of a Waypoint		(OUT)
 * param@ double& latitude	-	latitude of a Waypoint	(OUT)
 * param@ double& longitude	-	longitude of a Waypoint (OUT)
 * returnvalue@ void
 */
void CWaypoint::getAllDataByReference(string& name, double& latitude, double& longitude)
{
	/*
	 * Solution (Exercise 1.1; section h):
	 * The address of the variables of a calling function is same as the address of this function parameters.
	 * This is due to "&" in the parameter, which implies that the function call is pass-by-reference.
	 * Since the address is same, the value inside them are same as well, but the function member or method
	 * "getAllDataByReference" overrides the value with the data members value. Thus, once the method is returned,
	 * the local variables used during function call will have this object's data members value.
	 */
#ifdef SHOWADRESS
	cout << "Parameters variables at addresses : \n";
	cout << "Attribute Name \t" <<"Attribute Address \t"<< "Attribute Size \t" 			<< "Attribute Value\n";
	cout << "name \t\t" 		<< &name 				<< "\t\t" << name.size() 		<< "\t\t" << name << "\n";
	cout << "latitude \t" 		<< &latitude 			<< "\t\t" << sizeof(latitude)	<< "\t\t" << latitude << "\n";
	cout << "longitude \t" 		<< &longitude 			<< "\t\t" << sizeof(longitude)	<< "\t\t" << longitude << "\n";
#endif

	name 		= this->m_name;
	latitude 	= this->m_latitude;
	longitude 	= this->m_longitude;
}


/**
 * Return the distance between 2 waypoint co-ordinates
 * param@ const CWaypoint& wp	-	Waypoint co-ordinate (IN)
 * returnvalue@ double			- 	Distance in KMs
 */
double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	double distance = 0;

	// distance is in spherical co-ordinate system
	distance = 6378.17 * (acos(sin(degToRad(this->m_latitude)) * sin(degToRad(wp.m_latitude)) + 		\
						 cos(degToRad(this->m_latitude)) * cos(degToRad(wp.m_latitude)) * cos(degToRad(wp.m_longitude - this->m_longitude))));

	return distance;
}


/**
 * Prints the waypoint values in Degree-Mins-secs format or Decimal format
 * returnvalue@ void
 */
void CWaypoint::print(int format)
{
	// Exercise 1.1 ; section e
	if (format == DEGREE)
	{
		// Latitude and Longitude in decimal format
		cout << this->m_name << "\t\ton " << "latitude = " << this->m_latitude << " and " << "longitude = " << this->m_longitude << endl;
	}
	else if (format == MMSS)
	{
		// Latitude and Longitude in deg mm ss format
		int deg = 0, mm = 0;
		double ss = 0;

		this->transformLatitude2degmmss(deg, mm, ss);
		cout << this->m_name << "\t\ton " << "latitude = " << deg << "deg " << mm << "min " << ss << "s ";

		this->transformLongitude2degmmss(deg, mm, ss);
		cout << "and longitude = " << deg << "deg " << mm << "min " << ss << "s" << endl;
	}
}


/**
 * Converts the Latitude in decimal to deg-min-sec format
 * param@ int& deg		-	latitude in degrees	(OUT)
 * param@ int& deg		-	latitude in minutes	(OUT)
 * param@ double& ss	-	latitude in seconds (OUT)
 * returnvalue@ void
 */
void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss)
{
	// Exercise 1.1 ; section e
	deg = this->m_latitude;
	mm  = (this->m_latitude - deg) * 60;
	ss  = (((this->m_latitude - deg) * 60) - mm) * 60;

	// check if the latitude is negative; if so change the sign of minute and second
	if (this->m_latitude < 0)
	{
		mm = -mm;
		ss = -ss;
	}
}


/**
 * Converts the Longitude in decimal to deg-min-sec format
 * param@ int& deg		-	longitude in degrees (OUT)
 * param@ int& deg		-	longitude in minutes (OUT)
 * param@ double& ss	-	longitude in seconds (OUT)
 * returnvalue@ void
 */
void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss)
{
	// Exercise 1.1 ; section e
	deg = this->m_longitude;
	mm  = (this->m_longitude - deg) * 60;
	ss  = (((this->m_longitude - deg) * 60) - mm) * 60;

	// check if the longitude is negative; if so change the sign of minute and second
	if (this->m_longitude < 0)
	{
		mm = -mm;
		ss = -ss;
	}
}
