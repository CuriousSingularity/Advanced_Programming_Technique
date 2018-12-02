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

	this->addWaypoint(CWaypoint("Berliner Alle", 			49.866851, 	8.634864));
	this->addWaypoint(CWaypoint("Rheinstraße", 				49.870267, 	8.633266));
	this->addWaypoint(CWaypoint("Neckarstraße", 			49.8717, 	8.644417));
	this->addWaypoint(CWaypoint("Landskronstraße", 			49.853308,	8.646835));
	this->addWaypoint(CWaypoint("Bessunger", 				49.846994,	8.646193));
	this->addWaypoint(CWaypoint("FriedrichStraße",	 		49.838545,	8.645571));
	this->addWaypoint(CWaypoint("Katharinen Str.", 			49.824827,	8.644529));
	this->addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));
	this->addWaypoint(CWaypoint("Wartehalle", 				49.820845,	8.644222));
}


/**
 * Add a Waypoint to the database
 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(CWaypoint const &wp)
{
	CWaypoint tempWp = wp;
	pair<map<string, CWaypoint>::iterator, bool> ret;

	ret = this->m_Wp.insert(pair<string, CWaypoint>(tempWp.getName(), wp));

	if (ret.second == false)
	{
		cout << "WARNING: Waypoint already exists in the Database.\n" << wp << endl;
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

	for (this->m_WpItr = this->m_Wp.begin(); this->m_WpItr != this->m_Wp.end(); ++(this->m_WpItr))
	{
		if (!name.compare(this->m_WpItr->first))
		{
			pWp = &this->m_WpItr->second;
			break;
		}
	}

	return pWp;
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
