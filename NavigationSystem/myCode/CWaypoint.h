/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWaypoint.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CWaypoint.
* 					The class CWaypoint is used to hold the information of
* 					a waypoint co-ordinates and a name for it.
*
*
****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

//System Include Files
#include <string>
#include <ostream>

//Own Include Files

//Macros
#define DEGREE					1
#define MMSS					2

#define LATITUDE_MIN			(-90)
#define LATITUDE_MAX			(+90)
#define LONGITUDE_MIN			(-180)
#define LONGITUDE_MAX			(+180)


class CWaypoint {
public:

	enum wp_type
	{
		WAYPOINT,
		POI,
		INVALID,
	};

	/**
	 * CWaypoint constructor:
	 * Sets the value of an object when created.
	 * param@ string name		-	name of a Waypoint, default value ""	(IN)
	 * param@ double latitude	-	latitude of a Waypoint, default value 0	(IN)
	 * param@ double longitude	-	longitude of a Waypoint,default value 0	(IN)
	 * param@ wp_type type		-	Type of data - POI / Waypoint, default invalid (IN)
	 */
	CWaypoint(std::string name = "", double latitude = 0, double longitude = 0, wp_type type = WAYPOINT);

	/**
	 * Return the current waypoint co-ordinate name
	 * retuvalue@ string name	-	name of a Waypoint
	 */
	std::string getName();

	/**
	 * Return the current waypoint latitude
	 * returnvalue@ double latitude	-	latitude of a Waypoint
	 */
	double getLatitude();

	/**
	 * Return the current waypoint longitude
	 * returnvalue@ double longitude-	longitude of a Waypoint
	 */
	double getLongitude();

	/**
	 * Return the current waypoint co-ordinate values
	 * param@ string& name		-	name of a Waypoint		(OUT)
	 * param@ double& latitude	-	latitude of a Waypoint	(OUT)
	 * param@ double& longitude	-	longitude of a Waypoint (OUT)
	 * returnvalue@ void
	 */
	void getAllDataByReference(std::string& name, double& latitude, double& longitude);

	/**
	 * Converts the Latitude in decimal to deg-min-sec format
	 * param@ int& deg		-	latitude in degrees	(OUT)
	 * param@ int& deg		-	latitude in minutes	(OUT)
	 * param@ double& ss	-	latitude in seconds (OUT)
	 * returnvalue@ void
	 */
	void transformLatitude2degmmss(int& deg, int& mm, double& ss);

	/**
	 * Converts the Longitude in decimal to deg-min-sec format
	 * param@ int& deg		-	longitude in degrees (OUT)
	 * param@ int& deg		-	longitude in minutes (OUT)
	 * param@ double& ss	-	longitude in seconds (OUT)
	 * returnvalue@ void
	 */
	void transformLongitude2degmmss(int& deg, int& mm, double& ss);

	/**
	 * Return the distance between 2 waypoint co-ordinates
	 * param@ const CWaypoint& wp	-	Waypoint co-ordinate (IN)
	 * returnvalue@ double			- 	Distance in KMs
	 */
	double calculateDistance(const CWaypoint& wp);

	/**
	 * Prints the waypoint values in Degree-Mins-secs format or Decimal format
	 * param@ int format	-	Decimal or Deg-min-ss (OUT)
	 * returnvalue@ void
	 */
	virtual void print(int format);

	/**
	 * An operator overloaded friend function which prints the waypoint information
	 * param@ ostream &stream		-	output stream	(IN/OUT)
	 * param@ CWaypoint const &wp	-	A Waypoint 		(IN)
	 * returnvalue@ output stream with the waypoint information
	 */
	friend std::ostream& operator<< (std::ostream &stream, CWaypoint const &wp);

private:

	/*
	 * A name for the waypoint.
	 * eg: Berlin, California, Rio, Sydney etc
	 */
	std::string 	m_name;

	/**
	 * The latitude value of a co-ordinate
	 */
	double 			m_latitude;

	/**
	 * The longitude value of a co-ordinate
	 */
	double 			m_longitude;

	/**
	 * The type of data - POI or Waypoint
	 */
	wp_type			m_type;
};
/********************
**  CLASS END
*********************/
#endif /* CWAYPOINT_H */
