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

//Own Include Files
#include "CWaypoint.h"

//Macros
#define PI_VALUE						(atan(1) * 4)
#define degToRad(angleInDegrees) 		((angleInDegrees) * PI_VALUE / 180.0)
#define radToDeg(angleInRadians) 		((angleInRadians) * 180.0 / PI_VALUE)

//Namespaces
using namespace std;

//Method Implementations
/**
 * CWaypoint constructor:
 * Sets the value of any object when created
 * param@ string name		-	name of a Waypoint 		(IN)
 * param@ double latitude	-	latitude of a Waypoint 	(IN)
 * param@ double longitude	-	longitude of a Waypoint (IN)
 * param@ wp_type type		-	type of data the object represents:
 * 								POI / Waypoint / Invalid(IN)
 */
CWaypoint::CWaypoint(string name, double latitude, double longitude, wp_type type)
{
	if (((latitude >= LATITUDE_MIN) && (latitude <= LATITUDE_MAX)) &&
			((longitude >= LONGITUDE_MIN) && (longitude <= LONGITUDE_MAX)) &&
			(!name.empty()))
	{
		// All the parameters values are valid; we can assign these values to the respective data members of the class
		this->m_name 		= name;
		this->m_latitude 	= latitude;
		this->m_longitude 	= longitude;
		this->m_type		= type;
	}
	else
	{
		// some of the parameters values are invalid, hence set the values default to 0
		this->m_name 		= "";
		this->m_latitude 	= 0;
		this->m_longitude 	= 0;
		this->m_type	 	= CWaypoint::INVALID;
	}
}


/**
 * Destructor
 */
CWaypoint::~CWaypoint()
{
	// do nothing
}


/**
 * Return the current waypoint co-ordinate name
 * retuvalue@ string name	-	name of a Waypoint
 */
string CWaypoint::getName() const
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
	name 		= this->getName();
	latitude 	= this->getLatitude();
	longitude 	= this->getLongitude();
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
	// Solution (Exercise 1.1; section e)
	deg = this->m_latitude;
	mm  = (this->m_latitude - deg) * 60;
	ss  = (((this->m_latitude - deg) * 60) - mm) * 60;

	// check if the latitude is negative; if so change the sign of minute and second
	if (this->m_latitude < 0)
	{
		mm = -mm;
		ss = -ss;
	}
	else
	{
		// Do nothing
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
	// Solution (Exercise 1.1; section e)
	deg = this->m_longitude;
	mm  = (this->m_longitude - deg) * 60;
	ss  = (((this->m_longitude - deg) * 60) - mm) * 60;

	// check if the longitude is negative; if so change the sign of minute and second
	if (this->m_longitude < 0)
	{
		mm = -mm;
		ss = -ss;
	}
	else
	{
		// Do nothing
	}
}


/**
 * Return the distance between 2 waypoint co-ordinates
 * param@ const CWaypoint& wp	-	Waypoint co-ordinate (IN)
 * returnvalue@ double			- 	Distance in KMs
 */
double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	double distance = 0;

	// distance in a spherical co-ordinate system
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
	if (format == DEGREE)
	{
		// Latitude and Longitude in decimal format
		cout << this->m_name << "\ton " << "latitude = " << this->m_latitude << "\tand " << "longitude = " << this->m_longitude << endl;
	}
	else if (format == MMSS)
	{
		// Latitude and Longitude in deg mm ss format
		int deg = 0, mm = 0;
		double ss = 0;

		this->transformLatitude2degmmss(deg, mm, ss);
		cout << this->m_name << "\ton " << "latitude = " << deg << "deg " << mm << "min " << ss << "s ";

		this->transformLongitude2degmmss(deg, mm, ss);
		cout << "\tand longitude = " << deg << "deg " << mm << "min " << ss << "s" << endl;
	}
	else
	{
		cout << "WARNING: Requested Print format doesn't exist.\n";
	}
}


/**
 * An operator overloaded friend function which prints the waypoint information
 * param@ ostream &stream		-	output stream	(IN/OUT)
 * param@ CWaypoint const &wp	-	A Waypoint 		(IN)
 * returnvalue@ output stream with the waypoint information
 */
ostream& operator<< (ostream &stream, CWaypoint const &wp)
{
	CWaypoint outWp = wp;

	string name;
	double latitude, longitude;

	outWp.getAllDataByReference(name, latitude, longitude);

	int deg, mm;
	double ss;

	stream << "Waypoint  : " << name << "\n";

	outWp.transformLatitude2degmmss(deg, mm, ss);
	stream << "Latitude  : " << deg << "deg " << mm << "min " << ss << "s\n";

	outWp.transformLongitude2degmmss(deg, mm, ss);
	stream << "Longitude : " << deg << "deg " << mm << "min " << ss << "s \n";

	return stream;
}
