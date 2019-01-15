/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRoute.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CRoute.
* 					The class CRoute is used to hold the information
* 					of points of interest and waypoints of a Route.
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H

//System Include Files
#include <string>
#include <list>
#include <vector>

//Own Include Files
#include "CPoiDatabase.h"
#include "CWpDatabase.h"

typedef POI_Database_key_t							Database_key_t;
//typedef Wp_Database_key_t							Database_key_t;

typedef std::list<CWaypoint *> 						Route_Collection_t;
typedef std::list<CWaypoint *>::iterator			Route_Collection_FwdItr;
typedef std::list<CWaypoint *>::reverse_iterator	Route_Collection_RevItr;

class CRoute {
private:

	/**
	 * An list container to store the waypoints and POI of the route
	 */
	std::list<CWaypoint *>						m_Course;

	/**
	 * A pointer to the Point of interest Database
	 */
	CPoiDatabase								*m_pPoiDatabase;

	/**
	 * A pointer the Waypoint Database
	 */
	CWpDatabase									*m_pWpDatabase;

public:

	/**
	 * CRoute Constructor:
	 * Sets the value when an object is created.
	 */
    CRoute();

    /**
	 * CRoute Constructor:
	 * Sets the value when an object is created by performing deep copy.
	 * @param CRoute const &origin	- CRoute const object (IN)
	 */
	CRoute(CRoute const &origin);

    /**
	 * CRoute Destructor:
	 * Called when the object is destroyed
	 */
    ~CRoute();

    /**
	 * Get the address of the POI Database and connect it to the CRoute
	 * @param CPoiDatabase* pPoiDB		- pointer to the POI Database 		(IN)
	 * @returnval void
	 */
    void connectToPoiDatabase(CPoiDatabase *pPoiDB);

    /**
	 * Get the address of the Waypoint Database and connect it to the CRoute
	 * @param CWpDatabase *pWpDB		- pointer to the Waypoint Database 	(IN)
	 * @returnval void
	 */
    void connectToWpDatabase(CWpDatabase *pWpDB);

    /**
	 * Search the waypoint in the waypoint-database by the name; Add the waypoint to current route
	 * @param Database_key_t key		- name of a waypoint		(IN)
	 * @returnval void
	 */
    void addWaypoint(Database_key_t key);

    /**
     * Search the POI in the POI-database by the name; Add the POI to current route after "afterWp"
     * @param Database_key_t namePoi			- name of a POI		(IN)
     * @param Database_key_t afterWp			- name of a waypoint(IN)
     * @returnval void
     */
    void addPoi(Database_key_t namePoi, Database_key_t afterWp);

    /**
     * Get the current route information
     * @returnval vector - 	Current route having Waypoints and POI
     */
    const std::vector<const CWaypoint*> getRoute();

    /**
	 * Calculates the distance between waypoint and POI
	 * @param CWaypoint const &wp	- waypoint			(IN)
	 * @param CPOI& poi				- POI				(IN)
	 * @return double				- Distance in Kms
	 */
	double getDistanceNextPoi(CWaypoint const &wp, CPOI& poi);

    /**
	 * prints all the waypoints and POIs in the route
	 */
    void print();

    /**
	 * The function is an extension of addPoi which searches the Databases and add the
	 * Waypoint or the POI which matches the name.
	 */
	void operator += (Database_key_t const &name);

    /**
     * A copy assignment operator
     * @param CRoute const & rhs	- CRoute const object (IN)
     * @returnval CRoute&
     */
    CRoute& operator=(CRoute const & rhs);

    /**
	 * An addition operator
	 * @param CRoute const & rhs	- CRoute const object (IN)
	 * @returnval CRoute
	 */
	CRoute operator+(CRoute const & rhs);

};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
