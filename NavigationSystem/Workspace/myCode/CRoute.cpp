/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>

//Own Include Files
#include "CRoute.h"
#include "CWaypoint.h"
#include "CPOI.h"
#include "CPoiDatabase.h"

using namespace std;

//Method Implementations
/**
 * CRoute Constructor:
 * Sets the value when an object is created.
 * @param unsigned int maxWp	- maximum waypoints (IN)
 * @param unsigned int maxPoi	- maximum POI		(IN)
 */
CRoute::CRoute(unsigned int maxWp, unsigned int maxPoi)
{
	this->m_nextWp			= 0;
	this->m_maxWp			= maxWp;
	this->m_pWaypoint 		= new CWaypoint[this->m_maxWp];

	this->m_nextPoi			= 0;
	this->m_maxPoi			= maxPoi;
	this->m_pPoi			= new CPOI*[this->m_maxPoi];	// TODO: initialise this to null pointers

	this->m_pPoiDatabase	= 0;
}


/**
 * CRoute Constructor:
 * Sets the value when an object is created by deep copy.
 * @param CRoute const &origin	- CRoute const object (IN)
 */
CRoute::CRoute(CRoute const &origin)
{
	// Perform Deep copy
	this->m_nextWp			= origin.m_nextWp;
	this->m_maxWp			= origin.m_maxWp;
	this->m_pWaypoint 		= new CWaypoint[this->m_maxWp];

	for (unsigned int Index = 0; Index < this->m_maxWp; Index++)
	{
		this->m_pWaypoint[Index] = origin.m_pWaypoint[Index];
	}

	this->m_nextPoi			= origin.m_nextPoi;
	this->m_maxPoi			= origin.m_maxPoi;
	this->m_pPoi			= new CPOI*[this->m_maxPoi];

	for (unsigned int Index = 0; Index < this->m_maxPoi; Index++)
	{
		this->m_pPoi[Index] = origin.m_pPoi[Index];
	}

	this->m_pPoiDatabase	= origin.m_pPoiDatabase;
}


/**
 * CRoute Destructor:
 * When an object is about to destroy this function will be invoked.
 */
CRoute::~CRoute()
{
	// cleanup dynamic memories
	delete[] this->m_pWaypoint;
	delete[] this->m_pPoi;
	this->m_pPoiDatabase = 0;
}


/**
 * Get the address of the POI Database and connect it to the CRoute
 * @param CPoiDatabase* pPoiDB		- pointer to the POI Database 	(IN)
 * @returnval void
 */
void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	// connect to the POI Database
	this->m_pPoiDatabase = pPoiDB;
}


/**
 * Add the waypoint to current route
 * @param CWaypoint const &wp		- waypoint	(IN)
 * @returnval void
 */
void CRoute::addWaypoint(CWaypoint const &wp)
{
	if (this->m_nextWp < this->m_maxWp)
	{
		this->m_pWaypoint[this->m_nextWp] = wp;
		this->m_nextWp++;
	}
	else
	{
		cout << "Warning: waypoint can not be added to the route.\n";
	}
}


/**
 * Add the POI to current route
 * @param string namePoi			- name of POI	(IN)
 * @returnval void
 */
void CRoute::addPoi(string namePoi)
{
	if (this->m_nextPoi < this->m_maxPoi)
	{
		CPOI* pPoi = 0;

		pPoi = this->m_pPoiDatabase->getPointerToPoi(namePoi);

		if (pPoi)
		{
			this->m_pPoi[this->m_nextPoi] = this->m_pPoiDatabase->getPointerToPoi(namePoi);
			this->m_nextPoi++;
		}
	}
}


/**
 * Calculates the distance between waypoint and POI
 * @param CWaypoint const &wp	- waypoint			(IN)
 * @param CPOI& poi				- POI				(IN)
 * @return double				- Distance in Kms
 */
double CRoute::getDistanceNextPoi(CWaypoint const &wp, CPOI& poi)
{
	double shortestDistance = 0, currentDistance = 0;

	if (this->m_maxPoi)
	{
		// assume 0th element has shortest distance
		shortestDistance = this->m_pPoi[0]->calculateDistance(wp);

		// perform linear comparison for shortest distance
		for (unsigned int Index = 0; Index < this->m_maxPoi; Index++)
		{
			currentDistance = this->m_pPoi[Index]->calculateDistance(wp);

			if (currentDistance <= shortestDistance)
			{
				shortestDistance 	= currentDistance;
				poi					= *this->m_pPoi[Index];
			}
		}
	}

	return shortestDistance;
}


/**
 * prints the current waypoints and POIs
 */
void CRoute::print()
{
	// print all the waypoints in the route
	cout << "The route's has " << this->m_nextWp << " waypoints (maximum : " << this->m_maxWp << ")\n";

	for (unsigned int Index = 0; Index < this->m_maxWp; Index++)
	{
		this->m_pWaypoint[Index].print(MMSS);
	}

	cout << "=============================================" << endl;

	// print all the POIs in the route
	cout << "The route's has " << this->m_nextPoi << " POIs (maximum : " << this->m_maxPoi << ")\n";

	for (unsigned int Index = 0; Index < this->m_maxPoi; Index++)
	{
		this->m_pPoi[Index]->CWaypoint::print(MMSS);
	}
}
