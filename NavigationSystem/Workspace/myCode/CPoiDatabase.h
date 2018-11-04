/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPoiDatabase.h
* Author          : Bharath Ramachandraiah
* Description     : The file declares a class CPoiDatabase.
* 					The class CPoiDatabase is used to hold the information of
* 					array of point of interests.
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

//System Include Files
#include <string>

//Own Include Files
#include "CPOI.h"

class CPoiDatabase {
private:
	/**
	 * An array to store different point of interests.
	 */
    CPOI m_POI[10];

    /**
     * A counter to keep track of number of point of interests.
     */
    int m_noPoi;
public:

    /**
	 * CPoiDatabase constructor:
	 * Sets the value of an object when created.
	 */
    CPoiDatabase();

    /**
	 * Add a Point of interest to the database
	 * param@ t_poi type		-	point of interest type  		(IN)
	 * param@ string name		-	name of a POI					(IN)
	 * param@ string description-	description of a POI			(IN)
	 * param@ double latitude	-	latitude of a POI's Waypoint	(IN)
	 * param@ double longitude	-	longitude of a POI's Waypoint 	(IN)
	 * returnvalue@ void
	 */
    void addPoi(t_poi type, std::string name, std::string description, double latitude, double longitude);

    /**
     * Get pointer to a POI from the Database which matches the name
     * param@ string name		-	name of a POI					(IN)
     * returnvalue@ CPOI*		-	Pointer to a POI in the database
     */
    CPOI* getPointerToPoi(std::string name);
};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
