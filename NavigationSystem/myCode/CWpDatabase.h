/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWpDatabase.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CWpDatabase.
* 					The class CWpDatabase is used to hold the information
* 					of all the waypoints in a container.
*
****************************************************************************/

#ifndef CWPDATABASE_H
#define CWPDATABASE_H

//System Include Files
#include <string>
#include <map>

//Own Include Files
#include "CWaypoint.h"
#include "CDatabase.h"

//typedefs
typedef std::string											Wp_Database_key_t;

class CWpDatabase : public CDatabase<Wp_Database_key_t, CWaypoint> {
public:

	typedef std::map<Wp_Database_key_t, CWaypoint> 						Wp_Map_t;
	typedef std::map<Wp_Database_key_t, CWaypoint>::iterator 			Wp_Map_Itr_t;
	typedef std::map<Wp_Database_key_t, CWaypoint>::reverse_iterator 	Wp_Map_RevItr_t;

	/**
	 * CWpDatabase constructor
	 */
    CWpDatabase();

    /**
     * CWpDatabase destructor
     */
    ~CWpDatabase();

    /**
	 * Add a Waypoint to the database
	 * param@ Wp_Database_key_t &name	- 	unique name for the wp		(IN)
	 * param@ CWaypoint const &wp		-	Waypoint   					(IN)
	 * returnvalue@ void
	 */
	void addWaypoint(Wp_Database_key_t const &name, CWaypoint const &wp);

    /**
	 * Get pointer to a Waypoint from the Database which matches the name
	 * param@ Wp_Database_key_t name	-	name of a Waypoint	(IN)
	 * returnvalue@ CWaypoint*			-	Pointer to a Waypoint in the database
	 */
    CWaypoint* getPointerToWaypoint(Wp_Database_key_t name);

    /**
     * Get Waypoints from the Database
     * returnvalue@ Wp_Map_t			-	Waypoints in the Database	(OUT)
     */
    const Wp_Map_t getWpsFromDatabase() const;

    /**
	 * Resets the Database
	 * returnvalue@ void
	 */
	void resetWpsDatabase();

	/**
	 * Print all the Waypoints in the database
	 * returnvalue@ void
	 */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
