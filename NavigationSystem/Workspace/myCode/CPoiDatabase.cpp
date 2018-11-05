/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPoiDatabase.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CPoiDatabase.
* 					The class CPoiDatabase is used to hold the information
* 					of points of interest in an array.
*
****************************************************************************/


//System Include Files
#include <iostream>

//Own Include Files
#include "CPoiDatabase.h"

//Namespaces
using namespace std;

//Method Implementations
/**
 * CPoiDatabase constructor:
 * When an object is created, this constructor gets called.
 * Before this constructor is called, default constructor of CPOI class are invoked.
 *
 * Add all the POIs to the Database
 */
CPoiDatabase::CPoiDatabase()
{
	this->m_noPoi 	= 	0;

	for (unsigned int Index = 0; Index <sizeof(this->m_POI)/sizeof(CPOI); Index++)
	{
		// Reset the Database elements
		this->m_POI[Index] = CPOI(CPOI::DEFAULT_POI, "", "", 0, 0);
	}

	// Add POIs to the Database
	this->addPoi(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 		49.86727, 	8.638459);
	this->addPoi(CPOI::GASSTATION, "Aral Tankst."		, "Refuel your vehicle", 		49.871558, 	8.639206);
	this->addPoi(CPOI::RESTAURANT, "Starbucks"			, "A blissful coffee", 			49.872409, 	8.650744);
	this->addPoi(CPOI::RESTAURANT, "SushiRestaurant"	, "Asian food today!", 			49.869365,	8.645922);
	this->addPoi(CPOI::GASSTATION, "Aral Tankstelle"	, "Refuel your vehicle", 		49.868538,	8.645465);
	this->addPoi(CPOI::TOURISTIC,  "Church Holy"		, "Freie Christengemeinde", 	49.865072,	8.647415);
	this->addPoi(CPOI::RESTAURANT, "Thessaloniki"		, "Greek Restaurant ", 			49.862869, 	8.646691);
	this->addPoi(CPOI::TOURISTIC,  "Church 7 Days"		, "Adventist Chruch", 			49.839096,	8.646294);
	this->addPoi(CPOI::GASSTATION, "Ladestation"		, "Electric vehicle charge", 	49.811698,	8.646074);
	this->addPoi(CPOI::RESTAURANT, "El Quinto Vino"		, "Spanish Restaurant ", 		49.813422, 	8.646246);
}


/*
 * Add a Point of interest to the database
 * param@ t_poi type		-	point of interest type  		(IN)
 * param@ string name		-	name of a POI					(IN)
 * param@ string description-	description of a POI			(IN)
 * param@ double latitude	-	latitude of a POI's Waypoint	(IN)
 * param@ double longitude	-	longitude of a POI's Waypoint 	(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(CPOI::t_poi type, string name, string description, double latitude, double longitude)
{
	// check if the Database has free memory to store new POI
	if (this->m_noPoi < sizeof(this->m_POI)/sizeof(CPOI))
	{
		bool alreadyExist = false;

		// check if the POI already exists
		for (int Index = 0; Index < this->m_noPoi; Index++)
		{
			CPOI::t_poi getTypeFromDB;
			string getNameFromDB, getDescriptionFromDB;
			double getLatitudeFromDB, getLongitudeFromDB;

			this->m_POI[Index].getAllDataByReference(getNameFromDB, getLatitudeFromDB, getLongitudeFromDB, getTypeFromDB, getDescriptionFromDB);

			if ((getTypeFromDB == type) && (getNameFromDB == name) &&
				(getLatitudeFromDB == latitude) && (getLongitudeFromDB == longitude))
			{
				// POI already exists
				alreadyExist = true;
				break;
			}
		}

		if (!alreadyExist)
		{
			this->m_POI[this->m_noPoi] = CPOI(type, name, description, latitude, longitude);
			this->m_noPoi++;
		}
		else
		{
			cout << "WARNING: POI already exists!\n";
		}
	}
	else
	{
		cout << "WARNING: Database full!\n";
	}
}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI *pPoi = 0;

	for (int Index = 0; Index < this->m_noPoi; Index++)
	{
		if (this->m_POI[Index].CWaypoint::getName() == name)
		{
			pPoi = &this->m_POI[Index];
			break;
		}
	}

	return pPoi;
}
