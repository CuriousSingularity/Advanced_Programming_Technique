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


typedef std::map<std::string, CPOI> 			Poi_Map_t;
typedef std::map<std::string, CPOI>::iterator 	Poi_Map_Itr_t;

class CPoiDatabase {
private:

	/**
	 * An Associative container to store point of interests.
	 * key 		- name
	 * value	- POI
	 */
	Poi_Map_t 				m_Poi;

    /**
     * An iterator for the above container
     */
	Poi_Map_Itr_t			m_PoiItr;

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
	 * Function which returns the container having POIs in the Database
	 * param@ Wp_Map_t &WpDatabase		-	POIs in Database	(IN)
	 * returnvalue@ void
	 */
    const Poi_Map_t& getPoisFromDatabase() const;

    /**
	 * Resets the Database
	 * returnvalue@ void
	 */
	void resetPoisDatabase();

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
