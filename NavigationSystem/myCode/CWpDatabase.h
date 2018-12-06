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

//typedefs
typedef std::map<std::string, CWaypoint> 			Wp_Map_t;
typedef std::map<std::string, CWaypoint>::iterator 	Wp_Map_Itr_t;

class CWpDatabase {
private:

	/**
	 * An Associative container to store waypoints.
	 * key 		- name
	 * value	- waypoint
	 */
	Wp_Map_t 				m_Wp;

    /**
	 * An iterator for the above container
	 */
	Wp_Map_Itr_t			m_WpItr;

public:

	/**
	 * CWpDatabase constructor:
	 * Add all the Waypoints to the Database
	 */
    CWpDatabase();

    /**
	 * Add a Waypoint to the database
	 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
	 * returnvalue@ void
	 */
    void addWaypoint(CWaypoint const &wp);

    /**
	 * Get pointer to a Waypoint from the Database which matches the name
	 * param@ string name		-	name of a Waypoint	(IN)
	 * returnvalue@ CPOI*		-	Pointer to a POI in the database
	 */
    CWaypoint* getPointerToWaypoint(std::string name);

    /**
     * Function which returns the container having waypoints in the Database
     * param@ Wp_Map_t &WpDatabase		-	Waypoints in Database	(IN)
     * returnvalue@ void
     */
    const Wp_Map_t& getWpsFromDatabase() const;

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
