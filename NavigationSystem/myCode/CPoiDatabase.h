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
#include "CDatabase.h"

typedef std::string								POI_Database_key_t;

class CPoiDatabase : public CDatabase<POI_Database_key_t, CPOI> {
public:

	typedef std::map<POI_Database_key_t, CPOI> 					Poi_Map_t;
	typedef std::map<POI_Database_key_t, CPOI>::iterator 		Poi_Map_Itr_t;

    /**
	 * CPoiDatabase constructor
	 */
    CPoiDatabase();

    /**
     * CPoiDatabase destructor
     */
    ~CPoiDatabase();

    /*
     * Add a Point of interest to the database
     * param@ POI_Database_key_t const &key	- 	unique name for the poi		(IN)
     * param@ CPOI const &poi						-	point of interest   		(IN)
     * returnvalue@ void
     */
    void addPoi(POI_Database_key_t const &key, CPOI const &poi);

    /**
	 * Get pointer to a POI from the Database which matches the name
	 * param@ POI_Database_key_t key		-	key of a POI					(IN)
	 * returnvalue@ CPOI*						-	Pointer to a POI in the database(IN)
	 */
    CPOI* getPointerToPoi(POI_Database_key_t key);

    /**
     * Get POIs from the Database
     * returnvalue@ Poi_Map_t			-	POIs in the Database	(OUT)
     */
    const Poi_Map_t getPoisFromDatabase() const;

    /**
	 * Resets the Database
	 * returnvalue@ void
	 */
	void resetPoisDatabase();

	/**
	 * Print all the POIs in the database
	 * returnvalue@ void
	 */
	void print();

};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
