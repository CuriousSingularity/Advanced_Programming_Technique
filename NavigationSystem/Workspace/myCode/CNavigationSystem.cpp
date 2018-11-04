/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.CPP
* Author          :
* Description     :
*
*
****************************************************************************/

//System Include Files
#include <iostream>

//Own Include Files
#include "CNavigationSystem.h"


using namespace std;

//Method Implementations
/**
 * Constructor
 */
CNavigationSystem::CNavigationSystem() : m_route(10, 10)
{
	this->m_route.connectToPoiDatabase(&this->m_PoiDatabase);
}


/**
 * Navigation System functionaliy's entry function
 * @returnval void
 */
void CNavigationSystem::run()
{
	this->enterRoute();
	this->printRoute();
	this->printDistanceCurPosNextPoi();
}


/**
 * Add waypoints and POIs to create custom route
 * @returnval void
 */
void CNavigationSystem::enterRoute()
{
	// add waypoints
	this->m_route.addWaypoint(CWaypoint("Berliner Alle", 			49.866851, 	8.634864));
	this->m_route.addWaypoint(CWaypoint("Rheinstraße", 				49.870267, 	8.633266));
	this->m_route.addWaypoint(CWaypoint("Neckarstraße", 			49.8717, 	8.644417));
	this->m_route.addWaypoint(CWaypoint("Landskronstraße", 			49.853308,	8.646835));
	this->m_route.addWaypoint(CWaypoint("Bessunger", 				49.846994,	8.646193));
	this->m_route.addWaypoint(CWaypoint("FriedrichStraße",	 		49.838545,	8.645571));
	this->m_route.addWaypoint(CWaypoint("Katharinen Str.", 			49.824827,	8.644529));
	this->m_route.addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));
	this->m_route.addWaypoint(CWaypoint("PfungstädterStr",	 		49.817379,	8.644088));
	this->m_route.addWaypoint(CWaypoint("Büschelstraße", 			49.815069,	8.644614));
	this->m_route.addWaypoint(CWaypoint("Seeheimer Str.", 			49.813681,	8.646337));
	this->m_route.addWaypoint(CWaypoint("Heidelberger Landstrasse", 49.80687 ,	8.641321));

	// add POIs
	this->m_route.addPoi("HDA BuildingC10");
	this->m_route.addPoi("Aral Tankstelle"	);
	this->m_route.addPoi("Starbucks"		);
	this->m_route.addPoi("SushiRestaurant"	);
	this->m_route.addPoi("Aral Tankstelle"	);
	this->m_route.addPoi("Church Holy"		);
	this->m_route.addPoi("Thessaloniki"		);
	this->m_route.addPoi("Church 7 Days"	);
	this->m_route.addPoi("Ladestation"		);
	this->m_route.addPoi("El Quinto Vino"	);
	this->m_route.addPoi("My Chicken"		);
}


/**
 * Print all the waypoints and POIs of the custom route
 * @returnval void
 */
void CNavigationSystem::printRoute()
{
	this->m_route.print();
}


/**
 * Print the Distance between current position and a closest POI
 * @returnval void
 */
void CNavigationSystem::printDistanceCurPosNextPoi()
{
	double distance = 0;
	CPOI poi;
	//CWaypoint currentPosition = this->m_GPSSensor.getCurrentPosition();
	CWaypoint currentPosition("CurrentPos", 49.866851, 	8.634864);

	distance = this->m_route.getDistanceNextPoi(currentPosition, poi);

	cout << "Distance to next POI = " << distance << endl;
	poi.print();
}
