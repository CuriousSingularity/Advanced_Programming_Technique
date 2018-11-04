/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files
#include <iostream>

using namespace std;

//Own Include Files
#include "CPoiDatabase.h"
#include "CPOI.h"

//Method Implementations
/**
 * CPoiDatabase constructor:
 * Sets the value of an object when created.
 */
CPoiDatabase::CPoiDatabase()
{
	this->m_noPoi = 0;

	for (unsigned int Index = 0; Index <sizeof(this->m_POI)/sizeof(CPOI); Index++)
	{
		// Reset the database elements
		this->m_POI[Index] = CPOI(DEFAULT_POI, "", "", 0, 0);
	}

	// Add POIs to the Database
	this->addPoi(UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 		49.86727, 	8.638459);
	this->addPoi(GASSTATION, "Aral Tankstelle"	, "Refuel your vehicle", 		49.871558, 	8.639206);
	this->addPoi(RESTAURANT, "Starbucks"		, "A blissful coffee", 			49.872409, 	8.650744);
	this->addPoi(RESTAURANT, "SushiRestaurant"	, "Asian food today!", 			49.869365,	8.645922);
	this->addPoi(GASSTATION, "Aral Tankstelle"	, "Refuel your vehicle", 		49.868538,	8.645465);
	this->addPoi(TOURISTIC,  "Church Holy"		, "Freie Christengemeinde", 	49.868538,	8.645465);
	this->addPoi(RESTAURANT, "Thessaloniki"		, "Greek Restaurant ", 			49.862869, 	8.646691);
	this->addPoi(TOURISTIC,  "Church 7 Days"	, "Adventist Chruch", 			49.839096,	8.646294);
	this->addPoi(GASSTATION, "Ladestation"		, "Electric vehicle charge", 	49.811698,	8.646074);
	this->addPoi(RESTAURANT, "El Quinto Vino"	, "Spanish Restaurant ", 		49.813422, 	8.646246);
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
void CPoiDatabase::addPoi(t_poi type, string name, string description, double latitude, double longitude)
{
	// check if the database has memory to store new POI
	if ((this->m_noPoi >= 0) && (this->m_noPoi < sizeof(this->m_POI)/sizeof(CPOI)))
	{
		bool alreadyExist = false;

		for (unsigned int Index = 0; Index <sizeof(this->m_POI)/sizeof(CPOI); Index++)
		{
			// check if the POI already exists
			string getCurrentName;
			double getCurrentLatitude, getCurrentLongitude;
			this->m_POI[Index].CWaypoint::getAllDataByReference(getCurrentName, getCurrentLatitude, getCurrentLongitude);

			if ((getCurrentName == name) && (getCurrentLatitude == latitude) && (getCurrentLongitude == longitude))
			{
				// POI already exists
				alreadyExist = true;

				cout << "Warning: POI already exists!\n";
				this->m_POI[Index].print();
				break;
			}
		}

		if (!alreadyExist)
		{
			this->m_POI[this->m_noPoi] = CPOI(type, name, description,latitude, longitude);
			this->m_noPoi++;
		}
	}
	else
	{
		cout << "Warning: Database full.\n";
	}
}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(std::string name)
{
	CPOI *pPoi = 0;

	for (unsigned int Index = 0; Index <sizeof(this->m_POI)/sizeof(CPOI); Index++)
	{
		if (this->m_POI[Index].CWaypoint::getName() == name)
		{
			pPoi = &this->m_POI[Index];
			break;
		}
	}

	return pPoi;
}
