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
 * Prints the POI values in Degree-Mins-secs format or Decimal format
 * param@ int format	-	Decimal or Deg-min-ss (OUT)
 * returnvalue@ void
 */
void CPOI::print(int format)
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
	this->CWaypoint::print(format);
	cout << endl;
}


/**
 * An operator overloaded friend function which prints the POI information
 * param@ ostream &stream		-	output stream	(IN/OUT)
 * param@ CPOI const &poi		-	A POI 			(IN)
 * returnvalue@ output stream with the POI information
 */
ostream& operator<< (ostream &stream, CPOI const &poi)
{
	CPOI tempPoi = poi;
	CPOI::t_poi type;
	string name, description, typeName;
	double latitude, longitude;

	tempPoi.getAllDataByReference(name, latitude, longitude, type, description);

	switch(type)
	{
		case CPOI::RESTAURANT:
			typeName = "Restaurant";
			break;

		case CPOI::TOURISTIC:
			typeName = "Touristic";
			break;

		case CPOI::GASSTATION:
			typeName = "Gas station";
			break;

		case CPOI::UNIVERSITY:
			typeName = "University";
			break;

		case CPOI::DEFAULT_POI:
		default:
			typeName = "Default";
			break;
	}

	stream << "POI	  : " << name << "\n";
	stream << "POI type  : " << typeName << "\n";
	stream << "Descript  : " << description << "\n";

	int deg, mm;
	double ss;

	tempPoi.transformLatitude2degmmss(deg, mm, ss);
	stream << "Latitude  : " << deg << "deg " << mm << "min " << ss << "s\n";

	tempPoi.transformLongitude2degmmss(deg, mm, ss);
	stream << "Longitude : " << deg << "deg " << mm << "min " << ss << "s \n";

	return stream;
}
