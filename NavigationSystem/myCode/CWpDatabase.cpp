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

//Own Include Files
#include "CWpDatabase.h"

//Namespaces
using namespace std;

//Method Implementations
/**
 * CWpDatabase constructor
 */
CWpDatabase::CWpDatabase()
{
	// do nothing
}


/**
 * Add a Waypoint to the database
 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(CWaypoint const &wp)
{
	CWaypoint 					inWp = wp;
	pair<Wp_Map_Itr_t, bool> 	ret;

	if (!inWp.getName().empty())
	{
		ret = this->m_Wp.insert(pair<string, CWaypoint>(inWp.getName(), wp));

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
 * returnvalue@ CPOI*		-	Pointer to a Waypoint in the database
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint 	*pWp = 0;

	if (!this->m_Wp.empty())
	{
		Wp_Map_Itr_t 	wpItr = this->m_Wp.find(name);

		if (wpItr != this->m_Wp.end())
		{
			// element found
			pWp = &wpItr->second;
		}
	}

	return pWp;
}


/**
 * Get Waypoints from the Database
 * returnvalue@ Wp_Map_t			-	Waypoints in the Database	(OUT)
 */
const Wp_Map_t CWpDatabase::getWpsFromDatabase() const
{
	return (this->m_Wp);
}


/**
 * Reset the Database
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
	for (Wp_Map_Itr_t wpItr = this->m_Wp.begin(); wpItr != this->m_Wp.end(); ++wpItr)
	{
		cout << wpItr->second << endl;
	}
}
