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
 * param@ CWaypoint const &wp	-	Waypoint   		(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(CWaypoint const &wp)
{
	this->addWaypoint(wp.getName(), wp);
}


/**
 * Add a Waypoint to the database
 * param@ string &name			- 	unique name for the wp		(IN)
 * param@ CWaypoint const &wp	-	Waypoint   					(IN)
 * returnvalue@ void
 */
void CWpDatabase::addWaypoint(const std::string &name, CWaypoint const &wp)
{
	if (!wp.getName().empty())
	{
		this->addElement(name, wp);
	}
	else
	{
		cout << "WARNING: Trying to add invalid Waypoint to the Database.\n" << wp << endl;
	}
}

///**
// * Add a Waypoint to the database
// * param@ int &number			- 	unique number for the wp	(IN)
// * param@ CWaypoint const &wp	-	Waypoint   					(IN)
// * returnvalue@ void
// */
//void CWpDatabase::addWaypoint(const int &number, CWaypoint const &poi)
//{
//
//}


/**
 * Get pointer to a Waypoint from the Database which matches the name
 * param@ string name		-	name of a Waypoint	(IN)
 * returnvalue@ CPOI*		-	Pointer to a Waypoint in the database
 */
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	return (this->getPointerToElement(name));
}


/**
 * Get Waypoints from the Database
 * returnvalue@ Wp_Map_t			-	Waypoints in the Database	(OUT)
 */
const Wp_Map_t CWpDatabase::getWpsFromDatabase() const
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
