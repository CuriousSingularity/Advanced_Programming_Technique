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


using namespace std;


typedef struct
{
	t_poi		type;
	string		type_name;
} poi_type_t;

const poi_type_t poi_types [] =
{
	{	RESTAURANT,		"Restaurant"	},
	{	TOURISTIC,		"Touristic"		},
	{	GASSTATION,		"Gas station"	},
	{	UNIVERSITY,		"University"	},
	{	DEFAULT_POI,	"Default"		}
};


//Method Implementations
/**
 * CPOI constructor:
 * Sets the value of an object when created.
 * param@ t_poi type		-	type of a Point of interest	(IN)
 * param@ string name		-	name of a Waypoint			(IN)
 * param@ double latitude	-	latitude of a Waypoint		(IN)
 * param@ double longitude	-	longitude of a Waypoint		(IN)
 */
CPOI::CPOI(t_poi type, string name, string description, double latitude, double longitude) : CWaypoint(name, latitude, longitude)
{
//	if (name.empty() || description.empty())
//	{
//		// TODO:throw exception
//		cout << "WARNING: The POI entered has missing Name and/or Description\n";
//	}

	this->m_type 			= type;
	this->m_description 	= description;
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
	name 		= this->m_name;
	latitude 	= this->m_latitude;
	longitude 	= this->m_longitude;
	type 		= this->m_type;
	description = this->m_description;
}


/**
 * Print all the information of a Point of Interest.
 * returnvalue@ void
 */
void CPOI::print()
{
	for (unsigned int index = 0; index < sizeof(poi_types) / sizeof(poi_type_t); index++)
	{
		if (this->m_type == poi_types[index].type)
		{
			cout << "Point of interest\n";
			cout << "===================\n";
			cout << " of type " << poi_types[index].type_name << " : " << this->m_description << "\n";
			this->CWaypoint::print(MMSS);
			cout << endl;
			break;
		}
	}
}
