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

//Own Include Files
#include "CPoiDatabase.h"
#include "CWpDatabase.h"

class CRoute {
private:

	/**
	 * An list container to store the waypoints and POI of the route
	 */
	std::list<CWaypoint *>						m_Course;

	/**
	 * An iterator for the above container
	 */
	std::list<CWaypoint *>::iterator			m_ForwardItr;

	/**
	 * A reverse iterator for the above container
	 */
	std::list<CWaypoint *>::reverse_iterator	m_ReverseItr;

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
	 * @param string name		- name of a waypoint		(IN)
	 * @returnval void
	 */
    void addWaypoint(std::string name);

    /**
     * Search the POI in the POI-database by the name; Add the POI to current route after "afterWp"
     * @param string namePoi			- name of a POI		(IN)
     * @param string afterWp			- name of a waypoint(IN)
     * @returnval void
     */
    void addPoi(std::string namePoi, std::string afterWp);

    /**
	 * The function is an extension of addPoi which searches the Databases and add the
	 * Waypoint or the POI which matches the name.
	 */
	void operator += (std::string const &name);

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

};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
