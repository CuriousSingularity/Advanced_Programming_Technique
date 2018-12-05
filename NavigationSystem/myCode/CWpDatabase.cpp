/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWpDatabase.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CWpDatabase.
* 					The class CWpDatabase is used to hold the information
* 					of all the waypoints in a container.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <map>

//Own Include Files
#include "CWpDatabase.h"

//Namespaces
using namespace std;

//Method Implementations
/**
 * CWpDatabase constructor:
 * Add all the Waypoints to the Database
 */
CWpDatabase::CWpDatabase()
{
	this->m_WpItr = this->m_Wp.begin();

	// add Waypoints from persistence storage
	// TODO: check the validity - type, lat, long

//	this->addWaypoint(CWaypoint("Berliner Alle", 			49.866851, 	8.634864));
//	this->addWaypoint(CWaypoint("Rheinstraße", 				49.870267, 	8.633266));
//	this->addWaypoint(CWaypoint("Neckarstraße", 			49.8717, 	8.644417));
//	this->addWaypoint(CWaypoint("Landskronstraße", 			49.853308,	8.646835));
//	this->addWaypoint(CWaypoint("Bessunger", 				49.846994,	8.646193));
//	this->addWaypoint(CWaypoint("FriedrichStraße",	 		49.838545,	8.645571));
//	this->addWaypoint(CWaypoint("Katharinen Str.", 			49.824827,	8.644529));
//	this->addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));
//	this->addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));
}


/**
 * Add a Waypoint to the database
 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(CWaypoint const &wp)
{
	CWaypoint tempWp = wp;
	pair<Wp_Map_Itr_t, bool> ret;

	if (!tempWp.getName().empty())
	{
		ret = this->m_Wp.insert(pair<string, CWaypoint>(tempWp.getName(), wp));

		if (ret.second == false)
		{
			cout << "WARNING: Waypoint already exists in the Database.\n" << wp << endl;
		}
	}
	else
	{
		cout << "WARNING: Trying to add invalid Waypoint to the Database.\n" << wp << endl;
	}
}


/**
 * Get pointer to a Waypoint from the Database which matches the name
 * param@ string name		-	name of a Waypoint	(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint *pWp = 0;

	if (!this->m_Wp.empty())
	{
		this->m_WpItr = this->m_Wp.find(name);

		if (this->m_WpItr != this->m_Wp.end())
		{
			// element found
			pWp = &this->m_WpItr->second;
		}
	}

	return pWp;
}


/**
 * Function which returns the container having waypoints in the Database
 * param@ Wp_Map_t &WpDatabase		-	Waypoints in Database	(IN)
 * returnvalue@ void
 */
void CWpDatabase::getWpsFromDatabase(Wp_Map_t &Wps) const
{
	Wps = this->m_Wp;
}


/**
 * Function which reset the Database
 * returnvalue@ void
 */
void CWpDatabase::resetWpsDatabase()
{
	this->m_Wp.clear();
}


/**
 * Print all the Waypoints in the database
 * returnvalue@ void
 */
void CWpDatabase::print()
{
	for (this->m_WpItr = this->m_Wp.begin(); this->m_WpItr != this->m_Wp.end(); ++(this->m_WpItr))
	{
		cout << this->m_WpItr->second << endl;
	}
}
