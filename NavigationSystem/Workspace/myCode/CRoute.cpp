/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRoute.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CRoute.
* 					The class CRoute is used to hold the information
* 					of points of interest and waypoints of a Route.
*
****************************************************************************/

//System Include Files
#include <iostream>

//Own Include Files
#include "CRoute.h"

//Namespace
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
	this->m_nextPoi			= 0;
	this->m_maxPoi			= maxPoi;
	this->m_pPoi			= 0;
	this->m_pWaypoint 		= 0;
	this->m_pPoiDatabase	= 0;

	if (this->m_maxWp)
	{
		this->m_pWaypoint 	= new (nothrow) CWaypoint[this->m_maxWp];

		if (!this->m_pWaypoint)
		{
			cout << "WARNING: Memory allocation to store waypoints for the route failed.\n";
		}
	}

	if (this->m_maxPoi)
	{
		this->m_pPoi		= new (nothrow) CPOI*[this->m_maxPoi];

		if (!this->m_pPoi)
		{
			cout << "WARNING: Memory allocation to store POIs for the route failed.\n";
		}

		// Initialise all the pointers to null
		for (unsigned int Index = 0; (Index < this->m_maxPoi) && this->m_pPoi; Index++)
		{
			this->m_pPoi[Index]	= 0;
		}
	}
}


/**
 * CRoute Constructor:
 * Sets the value when an object is created by deep copy.
 * @param CRoute const &origin	- CRoute const object (IN)
 */
CRoute::CRoute(CRoute const &origin)
{
	cout << "INFO: Performing deep copy.\n";

	// Perform Deep copy
	this->m_nextWp			= origin.m_nextWp;
	this->m_maxWp			= origin.m_maxWp;
	this->m_nextPoi			= origin.m_nextPoi;
	this->m_maxPoi			= origin.m_maxPoi;
	this->m_pPoi			= 0;
	this->m_pWaypoint 		= 0;
	this->m_pPoiDatabase	= origin.m_pPoiDatabase;

	if (this->m_maxWp)
	{
		this->m_pWaypoint 	= new (nothrow) CWaypoint[this->m_maxWp];

		if (!this->m_pWaypoint)
		{
			cout << "WARNING: Memory allocation to store waypoints for the route failed.\n";
		}

		for (unsigned int Index = 0; (Index < this->m_maxWp) && this->m_pWaypoint && origin.m_pWaypoint; Index++)
		{
			this->m_pWaypoint[Index] = origin.m_pWaypoint[Index];
		}
	}

	if (this->m_maxPoi)
	{
		this->m_pPoi		= new (nothrow) CPOI*[this->m_maxPoi];

		if (!this->m_pPoi)
		{
			cout << "WARNING: Memory allocation to store POIs for the route failed.\n";
		}

		for (unsigned int Index = 0; (Index < this->m_maxPoi) && this->m_pPoi && origin.m_pPoi; Index++)
		{
			this->m_pPoi[Index] = origin.m_pPoi[Index];
		}
	}
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

	// disconnect from the Database
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
	if (pPoiDB)
	{
		this->m_pPoiDatabase = pPoiDB;
	}
}


/**
 * Add the waypoint to current route
 * @param CWaypoint const &wp		- waypoint	(IN)
 * @returnval void
 */
void CRoute::addWaypoint(CWaypoint const &wp)
{
	// check if the dynamic memory is allocated
	if (this->m_pWaypoint)
	{
		if (this->m_nextWp < this->m_maxWp)
		{
			this->m_pWaypoint[this->m_nextWp] = wp;
			this->m_nextWp++;
		}
		else
		{
			cout << "WARNING: memory full, waypoint can not be added to the route.\n";
		}
	}
	else
	{
		cout << "WARNING: Memory not created to add any waypoints to the route.\n";
	}
}


/**
 * Add the POI to current route
 * @param string namePoi			- name of POI	(IN)
 * @returnval void
 */
void CRoute::addPoi(string namePoi)
{
	// check if the dynamic memory is allocated
	if (this->m_pPoi)
	{
		if (this->m_nextPoi < this->m_maxPoi)
		{
			CPOI* pPoi = 0;

			// check if the Database is connected
			if (this->m_pPoiDatabase)
			{
				pPoi = this->m_pPoiDatabase->getPointerToPoi(namePoi);

				if (pPoi)
				{
					// check if the POI is already added to the route
					bool AlreadyExists = false;

					for (unsigned int Index = 0; Index < this->m_nextPoi; Index++)
					{
						if (pPoi == this->m_pPoi[this->m_nextPoi])
						{
							AlreadyExists = true;
						}
					}

					if (!AlreadyExists)
					{
						if (!namePoi.empty())
						{
							this->m_pPoi[this->m_nextPoi] = this->m_pPoiDatabase->getPointerToPoi(namePoi);
							this->m_nextPoi++;
						}
						else
						{
							cout << "WARNING: Invalid POI can't be added to the route.\n";
						}
					}
					else
					{
						cout << "WARNING: POI already added to the route.\n";
					}
				}
				else
				{
					cout << "WARNING: The Point of interest is not available in the Database.\n";
				}
			}
			else
			{
				cout << "WARNING: The Database is not available.\n";
			}
		}
		else
		{
			cout << "WARNING: memory full, POI can not be added to the route.\n";
		}
	}
	else
	{
		cout << "WARNING: Memory not created to add any POIs to the route.\n";
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

	if (this->m_pPoi)
	{
		if (this->m_nextPoi)
		{
			// assume 0th element has shortest distance
			shortestDistance = this->m_pPoi[0]->CWaypoint::calculateDistance(wp);

			// perform linear comparison for shortest distance
			for (unsigned int Index = 0; Index < this->m_nextPoi; Index++)
			{
				currentDistance = this->m_pPoi[Index]->CWaypoint::calculateDistance(wp);

				if (currentDistance <= shortestDistance)
				{
					shortestDistance 	= currentDistance;
					poi					= *this->m_pPoi[Index];
				}
			}
		}
		else
		{
			cout << "WARNING: No POIs added to the current route.\n";
		}
	}
	else
	{
		cout << "WARNING: No POIs added to the current route.\n";
	}

	return shortestDistance;
}


/**
 * prints the current waypoints and POIs
 */
void CRoute::print()
{
	cout << "=============================================" << endl << endl;

	// print all the waypoints in the route
	cout << "The route has " << this->m_nextWp << " waypoints (maximum : " << this->m_maxWp << ")\n";

	for (unsigned int Index = 0; (Index < this->m_nextWp) && this->m_pWaypoint; Index++)
	{
		this->m_pWaypoint[Index].print(MMSS);
	}

	cout << "=============================================" << endl << endl;

	// print all the POIs in the route
	cout << "The route has " << this->m_nextPoi << " POIs (maximum : " << this->m_maxPoi << ")\n";

	for (unsigned int Index = 0; (Index < this->m_nextPoi) && this->m_pPoi; Index++)
	{
		this->m_pPoi[Index]->CWaypoint::print(MMSS);
	}

	cout << "=============================================" << endl << endl;
}
