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
 * CWpDatabase constructor:
 * Add all the Waypoints to the Database
 */
CWpDatabase::CWpDatabase()
{
	this->m_WpItr = this->m_Wp.begin();

	// add POIs from persistence storage
}


/**
 * Add a Waypoint to the database
 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(CWaypoint const &wp)
{

}


/**
 * Get pointer to a Waypoint from the Database which matches the name
 * param@ string name		-	name of a Waypoint	(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint *pWp = 0;

	return pWp;
}



/**
 * Print all the Waypoints in the database
 * returnvalue@ void
 */
void CWpDatabase::print()
{

}
