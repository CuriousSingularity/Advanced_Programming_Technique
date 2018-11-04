/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H

//System Include Files

//Own Include Files
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"

class CNavigationSystem {
private:

	/**
	 * GPS sensor which feeds the current location
	 */
    CGPSSensor m_GPSSensor;

    /**
     * Navigation System's current route
     */
    CRoute m_route;

    /**
     * The Database of points of interest
     */
    CPoiDatabase m_PoiDatabase;

    /**
     * Add waypoints and POIs to create custom route
     * @returnval void
     */
    void enterRoute();

    /**
	 * Print all the waypoints and POIs of the custom route
	 * @returnval void
	 */
    void printRoute();

    /**
     * Print the Distance between current position and a closest POI
     * @returnval void
     */
    void printDistanceCurPosNextPoi();

public:

    /**
     * Constructor
     */
    CNavigationSystem();

    /**
     * Navigation System functionaliy's entry function
     * @returnval void
     */
    void run();

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
