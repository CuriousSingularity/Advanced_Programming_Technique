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

class CWpDatabase {
private:

	/**
	 * An Associative container to store waypoints.
	 * key 		- name
	 * value	- waypoint
	 */
	std::multimap<std::string, CWaypoint> 				m_Wp;

    /**
	 * An iterator for the above container
	 */
	std::multimap<std::string, CWaypoint>::iterator		m_WpItr;

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
	 * Print all the Waypoints in the database
	 * returnvalue@ void
	 */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
