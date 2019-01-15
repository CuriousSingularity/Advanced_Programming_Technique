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
 * CWpDatabase destructor
 */
CWpDatabase::~CWpDatabase()
{
	// do nothing
}


/**
 * Add a Waypoint to the database
 * param@ Wp_Database_key_t const &key	- 	key for the wp	(IN)
 * param@ CWaypoint const &wp			-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(Wp_Database_key_t const &key, CWaypoint const &wp)
{
	this->addElement(key, wp);
}


/**
 * Get pointer to a Waypoint from the Database which matches the name
 * param@ Wp_Database_key_t name	-	name of a Waypoint	(IN)
 * returnvalue@ CPOI*				-	Pointer to a Waypoint in the database
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(Wp_Database_key_t name)
{
	return (this->getPointerToElement(name));
}


/**
 * Get Waypoints from the Database
 * returnvalue@ Wp_Map_t			-	Waypoints in the Database	(OUT)
 */
const CWpDatabase::Wp_Map_t CWpDatabase::getWpsFromDatabase() const
{
	return (this->getElementsFromDatabase());
}


/**
 * Reset the Database
 * returnvalue@ void
 */
void CWpDatabase::resetWpsDatabase()
{
	this->resetDatabase();
}


/**
 * Print all the Waypoints in the database
 * returnvalue@ void
 */
void CWpDatabase::print()
{
	this->CDatabase::print();
}
