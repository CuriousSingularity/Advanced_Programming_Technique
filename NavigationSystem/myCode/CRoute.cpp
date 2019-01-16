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
#include <limits>
#include <typeinfo>

//Own Include Files
#include "CRoute.h"

//Namespace
using namespace std;

//Method Implementations
/**
 * CRoute Constructor:
 * Sets the value when an object is created.
 */
CRoute::CRoute()
{
	this->m_Course.clear();
	this->m_pPoiDatabase	= 0;
	this->m_pWpDatabase		= 0;
}


/**
 * CRoute Constructor:
 * Sets the value when an object is created by performing deep copy.
 * @param CRoute const &origin	- CRoute const object (IN)
 */
CRoute::CRoute(CRoute const &origin)
{
	cout << "INFO: Performing deep copy.\n";

	this->m_Course 		= origin.m_Course;
	this->m_pPoiDatabase= origin.m_pPoiDatabase;
	this->m_pWpDatabase	= origin.m_pWpDatabase;
}


/**
 * CRoute Destructor
 */
CRoute::~CRoute()
{
	// clear all the elements
	this->m_Course.clear();

	// disconnect from the Database
	this->m_pPoiDatabase 	= 0;
	this->m_pWpDatabase		= 0;
}


/**
 * Get the address of the POI Database and connect it to the CRoute
 * @param CPoiDatabase* pPoiDB		- pointer to the POI Database 		(IN)
 * @returnval void
 */
void CRoute::connectToPoiDatabase(CPoiDatabase *pPoiDB)
{
	// connect to the POI Database
	if (pPoiDB)
	{
		this->m_pPoiDatabase 	= pPoiDB;
		cout << "INFO: POI Database connected to the route.\n";
	}
	else
	{
		cout << "WARNING: POI Database not connected to the route.\n";
	}
}


/**
 * Get the address of the Waypoint Database and connect it to the CRoute
 * @param CWpDatabase *pWpDB		- pointer to the Waypoint Database 	(IN)
 * @returnval void
 */
void CRoute::connectToWpDatabase(CWpDatabase *pWpDB)
{
	// connect to the Waypoint Database
	if (pWpDB)
	{
		this->m_pWpDatabase 	= pWpDB;
		cout << "INFO: Waypoint Database connected to the route.\n";
	}
	else
	{
		cout << "WARNING: Waypoint Database not connected to the route.\n";
	}
}


/**
 * Search the waypoint in the waypoint-database by the name; Add the waypoint to current route
 * @param Database_key_t key		- name of a waypoint		(IN)
 * @returnval void
 */
void CRoute::addWaypoint(Database_key_t key)
{
	CWaypoint *pWp;

	// check if the database is connected
	if (this->m_pWpDatabase)
	{
		pWp = this->m_pWpDatabase->getPointerToWaypoint(key);

		if (pWp)
		{
			// save the pointer to the waypoint in the current route
			this->m_Course.push_back(static_cast<CWaypoint *>(pWp));
		}
		else
		{
			cout << "WARNING: The Requested Waypoint -\"" << key << "\" is not available in the Database.\n";
		}
	}
	else
	{
		cout << "WARNING: The Waypoint Database is not available.\n";
	}
}


/**
 * Search the POI in the POI-database by the name; Add the POI to current route after "afterWp"
 * if ->
 * 		namePoi is empty 		and afterWp is empty		-> don't add
 * 		namePoi is empty 		and afterWp is not empty	-> POI will not be in the DB
 * 		namePoi is not empty 	and afterWp is empty		-> Add POI to Route at the end
 * 		namePoi is not empty 	and afterWp is not empty	-> Add POI afterWp where afterWP is already added
 *
 * @param string namePoi			- name of a POI		(IN)
 * @param string afterWp			- name of a waypoint(IN)
 * @returnval void
 */
void CRoute::addPoi(Database_key_t namePoi, Database_key_t afterWp)
{
	bool		isAfterWp 	= false;
	CPOI		*pPoi 		= 0;
	CWaypoint 	*pWp 		= 0;

	if ((typeid(namePoi) == typeid(string)) &&
		(typeid(afterWp) == typeid(string)) &&
		(!namePoi.empty() || !afterWp.empty()))
	{
		// check if the database is connected
		if (this->m_pPoiDatabase)
		{
			pPoi = this->m_pPoiDatabase->getPointerToPoi(namePoi);

			if (pPoi)
			{
				for (Route_Collection_RevItr revItr = this->m_Course.rbegin(); revItr != this->m_Course.rend(); ++revItr)
				{
					pWp = dynamic_cast<CWaypoint *>(*revItr);

					// is this a Waypoint ?
					if (pWp)
					{
						// are the names matching ?
						if (!afterWp.compare(pWp->getName()))
						{
							this->m_Course.insert(revItr.base(), pPoi);
							isAfterWp = true;
							break;
						}
					}
				}

				if (!isAfterWp)
				{
					this->m_Course.push_back(static_cast<CPOI *>(pPoi));

					cout << "WARNING: The Requested Waypoint - \"" << afterWp << "\" is not available in the Route.\n";
				}
			}
			else
			{
				cout << "WARNING: The Requested POI - \"" << namePoi << "\" is not available in the Database.\n";
			}
		}
		else
		{
			cout << "WARNING: The POI Database is not available.\n";
		}
	}
	else
	{
		cout << "WARNING: The Waypoint and POI are invalid.\n";
	}
}


/**
 * Get the current route information
 * @returnval vector - 	Current route having Waypoints and POI
 */
const vector<const CWaypoint*> CRoute::getRoute()
{
	vector<const CWaypoint*> currentRoute;

	for (Route_Collection_FwdItr itr = this->m_Course.begin(); itr != this->m_Course.end(); ++itr)
	{
		currentRoute.push_back(*itr);
	}

	return currentRoute;
}


/**
 * Calculates the distance between waypoint and POI
 * @param CWaypoint const &wp	- waypoint			(IN)
 * @param CPOI& poi				- POI				(IN)
 * @return double				- Distance in Kms
 */
double CRoute::getDistanceNextPoi(CWaypoint const &wp, CPOI& poi)
{
	CPOI	*pPoi = 0;
	double	shortestDistance = numeric_limits<double>::max(), currentDistance = 0;

	if (!this->m_Course.empty())
	{
		for (Route_Collection_FwdItr fwdItr = this->m_Course.begin(); fwdItr != this->m_Course.end(); ++fwdItr)
		{
			pPoi = dynamic_cast<CPOI *>(*fwdItr);

			if (pPoi)
			{
				currentDistance = pPoi->CWaypoint::calculateDistance(wp);

				if (currentDistance <= shortestDistance)
				{
					shortestDistance = currentDistance;
					poi				 = *pPoi;
				}
			}
		}
	}

	return shortestDistance;
}


/**
 * prints all the waypoints and POIs in the route
 */
void CRoute::print()
{
	CPOI		*pPoi	= 0;
	CWaypoint 	*pWp 	= 0;

	cout << "=======================================================\n";
	cout << "The Route Information:\n";
	cout << "=======================================================\n";

	for (Route_Collection_FwdItr fwdItr = this->m_Course.begin(); fwdItr != this->m_Course.end(); ++fwdItr)
	{
		pPoi = dynamic_cast<CPOI *>(*fwdItr);

#ifdef RUN_TEST_PRINT
		// The iterator can point to
		// 1. Address of a CWaypoint	-> CWaypoint::print() 	will be invoked.
		// 2. Address of a CPOI			-> CPOI::print() 		will be invoked.
		// The respective print function will be called due to polymorphic virtual function
		(*this->m_ForwardItr)->print(2);

		// Since the container used is of type CWaypoint, even the POI will be treated as
		// a Waypoint data(since there is not explict dynamic casting) and the
		// CWaypointer's operator<< will be invoked.
		cout << (**this->m_ForwardItr) << endl;
#endif

		if (pPoi)
		{
			cout << *pPoi << endl;
		}
		else
		{
			pWp = dynamic_cast<CWaypoint *>(*fwdItr);

			if (pWp)
			{
				cout << *pWp << endl;
			}
			else
			{
				cout << "WARNING: Unknown type of Data in the Route.\n" << endl;
			}
		}
	}
}


/**
 * The function is an extension of addPoi which searches the Databases and add the
 * Waypoint and/or the POI which matches the name.
 */
void CRoute::operator += (Database_key_t const &name)
{
	CPOI		*pPoi = 0;
	CWaypoint	*pWp  = 0;
	string 		namePoi, nameWp;

	if (!name.empty())
	{
		if (this->m_pWpDatabase)
		{
			pWp	= this->m_pWpDatabase->getPointerToWaypoint(name);

			if (pWp)
			{
				this->addWaypoint(name);
				nameWp = name;
			}
		}

		if (this->m_pPoiDatabase)
		{
			pPoi = this->m_pPoiDatabase->getPointerToPoi(name);

			if (pPoi)
			{
				namePoi = name;
			}
		}
		this->addPoi(namePoi, nameWp);
	}
	else
	{
		cout << "WARNING: Invalid POI / Waypoint addition to the route request.\n";
	}
}


/**
 * A copy assignment operator
 * @param CRoute const & rhs	- CRoute const object (IN)
 * @returnval CRoute&
 */
CRoute& CRoute::operator=(CRoute const & rhs)
{
	this->m_Course.clear();
	this->m_pPoiDatabase= 0;
	this->m_pWpDatabase	= 0;

	this->m_Course 		= rhs.m_Course;
	this->m_pPoiDatabase= rhs.m_pPoiDatabase;
	this->m_pWpDatabase	= rhs.m_pWpDatabase;

	return *this;
}


/**
 * An addition operator
 * @param CRoute const & rhs	- CRoute const object (IN)
 * @returnval CRoute
 */
CRoute CRoute::operator+(CRoute const & rhs)
{
	CRoute result;

	// check if the Databases are same
	if ((this->m_pPoiDatabase == rhs.m_pPoiDatabase) &&
		(this->m_pWpDatabase == rhs.m_pWpDatabase))
	{
		Route_Collection_t 		rhs1 = this->m_Course;
		Route_Collection_t 		rhs2 = rhs.m_Course;
		Route_Collection_FwdItr fwdItr = result.m_Course.begin();

		result.m_Course.splice(fwdItr, rhs1);
		result.m_Course.splice(fwdItr, rhs2);
		result.m_pPoiDatabase	= rhs.m_pPoiDatabase;
		result.m_pWpDatabase	= rhs.m_pWpDatabase;
	}
	else
	{
		cout << "WARNING: The Databases are different and can not be concatenated.\n";
	}

	return result;
}
