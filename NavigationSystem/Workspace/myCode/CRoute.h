/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H

//System Include Files
#include <string>

//Own Include Files
#include "CPoiDatabase.h"
#include "CWaypoint.h"
#include "CPOI.h"

class CRoute {
private:

	/**
	 * Basepointer to an array of Waypoints in the route
	 */
    CWaypoint* m_pWaypoint;

    /**
     * Maximum number of Waypoints that can be added to the route
     */
    unsigned int m_maxWp;

    /**
     * Number of Waypoints present in the current route
     */
    unsigned int m_nextWp;

    /**
     * A pointer to an array of pointers containing the POIs of the current route
     */
    CPOI* * m_pPoi;

    /**
     * Maximum number of Points of interest that can be added to the route
     */
    unsigned int m_maxPoi;

    /**
	 * Number of Points of interest present in the current route
	 */
    unsigned int m_nextPoi;

    /**
     * A pointer the Point of interest Database
     */
    CPoiDatabase* m_pPoiDatabase;
public:

    /**
     * CRoute Constructor:
     * Sets the value when an object is created.
     * @param unsigned int maxWp	- maximum waypoints (IN)
     * @param unsigned int maxPoi	- maximum POI		(IN)
     */
    CRoute(unsigned int maxWp, unsigned int maxPoi);

    /**
	 * CRoute Constructor:
	 * Sets the value when an object is created by deep copy.
	 * @param CRoute const &origin	- CRoute const object (IN)
	 */
    CRoute(CRoute const &origin);    

    /**
     * CRoute Destructor:
     * When an object is about to destroy this function will be invoked.
     */
    ~CRoute();

    /**
     * Get the address of the POI Database and connect it to the CRoute
     * @param CPoiDatabase* pPoiDB		- pointer to the POI Database 	(IN)
     * @returnval void
     */
    void connectToPoiDatabase(CPoiDatabase* pPoiDB);

    /**
     * Add the waypoint to current route
     * @param CWaypoint const &wp		- waypoint		(IN)
     * @returnval void
     */
    void addWaypoint(CWaypoint const &wp);

    /**
	 * Add the POI to current route
	 * @param string namePoi			- name of POI	(IN)
	 * @returnval void
	 */
    void addPoi(std::string namePoi);

    /**
     * Calculates the distance between waypoint and POI
     * @param CWaypoint const &wp	- waypoint			(IN)
     * @param CPOI& poi				- POI				(IN)
     * @return double				- Distance in Kms
     */
    double getDistanceNextPoi(CWaypoint const &wp, CPOI& poi);

    /**
     * prints the current waypoints and POIs
     */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
