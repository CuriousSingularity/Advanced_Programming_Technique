/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPoiDatabase.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CPoiDatabase.
* 					The class CPoiDatabase is used to hold the information
* 					of points of interest in a container.
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

//System Include Files
#include <string>
#include <map>

//Own Include Files
#include "CPOI.h"

class CPoiDatabase {
private:

	/**
	 * An Associative container to store point of interests.
	 * key 		- name
	 * value	- POI
	 */
    std::multimap<std::string, CPOI> 				m_Poi;

    /**
     * An iterator for the above container
     */
    std::multimap<std::string, CPOI>::iterator		m_PoiItr;

public:

    /**
	 * CPoiDatabase constructor:
	 * Add all the POIs to the Database
	 */
    CPoiDatabase();

    /**
	 * Add a Point of interest to the database
	 * param@ CPOI const &poi		-	point of interest   		(IN)
	 * returnvalue@ void
	 */
    void addPoi(CPOI const &poi);

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
