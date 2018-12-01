/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CPOI.
* 					The class CPOI is used to hold the information of a
* 					point of interest.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <string>

//Own Include Files
#include "CPOI.h"

//Namespaces
using namespace std;

//Method Implementations

/**
 * CPOI constructor:
 * Sets the value of an object when created.
 * param@ t_poi type		-	type of a Point of interest	(IN)
 * param@ string name		-	name of a Waypoint			(IN)
 * param@ double latitude	-	latitude of a Waypoint		(IN)
 * param@ double longitude	-	longitude of a Waypoint		(IN)
 */
CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude) : CWaypoint(name, latitude, longitude, CWaypoint::POI)
{
	this->m_type 			= type;
	this->m_description 	= description;
}


/**
 * CPOI Destructor:
 * Called when the object is destroyed
 */
CPOI::~CPOI()
{
	// Do nothing
}


/*
 * Return the current point of interest's values
 * param@ string& name		-	name of a POI					(OUT)
 * param@ double& latitude	-	latitude of a POI's Waypoint	(OUT)
 * param@ double& longitude	-	longitude of a POI's Waypoint 	(OUT)
 * param@ t_poi& type		-	point of interest type  		(OUT)
 * param@ string&description-	description of a POI			(OUT)
 * returnvalue@ void
*/
void CPOI::getAllDataByReference(string& name, double& latitude, double& longitude, t_poi &type, string &description)
{
	type 		= this->m_type;
	description = this->m_description;

	this->CWaypoint::getAllDataByReference(name, latitude, longitude);
}


/**
 * Print all the information of a Point of Interest.
 * returnvalue@ void
 */
void CPOI::print()
{
	string typeName;

	switch(this->m_type)
	{
		case RESTAURANT:
			typeName = "Restaurant";
			break;

		case TOURISTIC:
			typeName = "Touristic";
			break;

		case GASSTATION:
			typeName = "Gas station";
			break;

		case UNIVERSITY:
			typeName = "University";
			break;

		case DEFAULT_POI:
		default:
			typeName = "Default";
			break;
	}

	cout << "Point of interest\n";
	cout << "===================\n";
	cout << " of type " << typeName << " : " << this->m_description << "\n";
	this->CWaypoint::print(MMSS);
	cout << endl;
}
