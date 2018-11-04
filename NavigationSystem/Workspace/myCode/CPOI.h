/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.h
* Author          : Bharath Ramachandraiah
* Description     : The file declares a class CPOI.
* 					The class CPOI is used to hold the information of a
* 					point of interest.
*
****************************************************************************/

#ifndef CPOI_H
#define CPOI_H

//System Include Files
#include <string>

//Own Include Files
#include "CWaypoint.h"

//Enumations
enum t_poi
{
	RESTAURANT,
	TOURISTIC,
	GASSTATION,
	UNIVERSITY,
	DEFAULT_POI,
};

class CPOI : public CWaypoint {
private:

	/**
	 * To identify the type of point of interest.
	 */
    t_poi 			m_type;

    /**
     * A description about the point of interest.
     */
    std::string 	m_description;

public:

    /**
	 * CPOI constructor:
	 * Sets the value of an object when created.
	 * param@ t_poi type		-	type of a Point of interest	(IN)
	 * param@ string name		-	name of a Waypoint			(IN)
	 * param@ double latitude	-	latitude of a Waypoint		(IN)
	 * param@ double longitude	-	longitude of a Waypoint		(IN)
	 */
    CPOI(t_poi type = DEFAULT_POI, std::string name = "", std::string description = "", double latitude = 0, double longitude = 0);

    /*
     * Return the current point of interest's values
	 * param@ string& name		-	name of a POI					(OUT)
	 * param@ double& latitude	-	latitude of a POI's Waypoint	(OUT)
	 * param@ double& longitude	-	longitude of a POI's Waypoint 	(OUT)
	 * param@ t_poi& type		-	point of interest type  		(OUT)
	 * param@ string&description-	description of a POI			(OUT)
	 * returnvalue@ void
     */
    void getAllDataByReference(std::string& name, double& latitude, double& longitude, t_poi &type, std::string &description);

    /**
     * Print all the information of a Point of Interest.
     * returnvalue@ void
     */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
