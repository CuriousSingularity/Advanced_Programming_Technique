/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

// Solution (Exercise 1.1; section f):
// Macros should be defined here (CWaypoint.h) so that it can be accessed by
// both print method and calling function in main.cpp or *.cpp which includes
// this header file.
#define DEGREE					1
#define MMSS					2

#define LATITUDE_MIN			(-90)
#define LATITUDE_MAX			(+90)
#define LONGITUDE_MIN			(-180)
#define LONGITUDE_MAX			(+180)

class CWaypoint {
private:

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

protected:

    std::string m_name;
    double 		m_latitude;
    double 		m_longitude;

public:

    /**
     * CWaypoint constructor:
     * Sets the value of an object when created.
     * param@ string name		-	name of a Waypoint, default value ""	(IN)
     * param@ double latitude	-	latitude of a Waypoint, default value 0	(IN)
     * param@ double longitude	-	longitude of a Waypoint,default value 0	(IN)
     */
    CWaypoint(std::string name = "", double latitude = 0, double longitude = 0);		// Solution (Exercise 1.1; section c):

    /**
     * Sets the current waypoint co-ordinate values
     * param@ string name		-	name of a Waypoint	(IN)
     * param@ double latitude	-	latitude of a Waypoint	(IN)
     * param@ double longitude	-	longitude of a Waypoint	(IN)
     * returnvalue@ void
     */
    void set(std::string name, double latitude, double longitude);

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
	 * param@ string& name		-	name of a Waypoint	(OUT)
	 * param@ double& latitude	-	latitude of a Waypoint	(OUT)
	 * param@ double& longitude	-	longitude of a Waypoint (OUT)
	 * returnvalue@ void
	 */
    void getAllDataByReference(std::string& name, double& latitude, double& longitude);

    /**
	 * Return the distance between 2 waypoint co-ordinates
	 * param@ const CWaypoint& wp	-	Waypoint co-ordinate (IN)
	 * returnvalue@ double			- 	Distance in KMs
	 */
    double calculateDistance(const CWaypoint& wp);

    /**
     * Prints the waypoint values in Degree-Mins-secs format or Decimal format
     * returnvalue@ void
     */
    void print(int format);

};
/********************
**  CLASS END
*********************/
#endif /* CWAYPOINT_H */
