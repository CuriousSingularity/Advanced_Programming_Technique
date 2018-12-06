/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPoiDatabase.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CPoiDatabase.
* 					The class CPoiDatabase is used to hold the information
* 					of all the points of interest in a container.
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
 * Add all the POIs to the Database
 */
CPoiDatabase::CPoiDatabase()
{
	this->m_PoiItr = this->m_Poi.begin();

	// add POIs from persistence storage
	// TODO: check the validity - type, lat, long
//	this->addPoi(CPOI(CPOI::UNIVERSITY, "HDA BuildingC10"	, "An awesome University", 		49.86727, 	8.638459));
//	this->addPoi(CPOI(CPOI::GASSTATION, "Aral Tankst."		, "Refuel your vehicle", 		49.871558, 	8.639206));
//	this->addPoi(CPOI(CPOI::RESTAURANT, "Starbucks"			, "A blissful coffee", 			49.872409, 	8.650744));
//	this->addPoi(CPOI(CPOI::RESTAURANT, "SushiRestaurant"	, "Asian food today!", 			49.869365,	8.645922));
//	this->addPoi(CPOI(CPOI::GASSTATION, "Aral Tankstelle"	, "Refuel your vehicle", 		49.868538,	8.645465));
//	this->addPoi(CPOI(CPOI::TOURISTIC,  "Church Holy"		, "Freie Christengemeinde", 	49.865072,	8.647415));
//	this->addPoi(CPOI(CPOI::RESTAURANT, "Thessaloniki"		, "Greek Restaurant ", 			49.862869, 	8.646691));
//	this->addPoi(CPOI(CPOI::TOURISTIC,  "Church 7 Days"		, "Adventist Chruch", 			49.839096,	8.646294));
//	this->addPoi(CPOI(CPOI::GASSTATION, "Ladestation"		, "Electric vehicle charge", 	49.811698,	8.646074));
//	this->addPoi(CPOI(CPOI::RESTAURANT, "El Quinto Vino"	, "Spanish Restaurant ", 		49.813422, 	8.646246));
//	this->addPoi(CPOI(CPOI::RESTAURANT, "El Quinto Vino"	, "Spanish Restaurant ", 		49.813422, 	8.646246));
}


/*
 * Add a Point of interest to the database
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(CPOI const &poi)
{
	CPOI tempPoi = poi;
	pair<Poi_Map_Itr_t, bool> ret;

	if (!tempPoi.getName().empty())
	{
		ret = this->m_Poi.insert(pair<string, CPOI>(tempPoi.getName(), poi));

		if (ret.second == false)
		{
			cout << "WARNING: POI already exists in the Database.\n" << poi << endl;
		}
	}
	else
	{
		cout << "WARNING: Trying to add invalid POI to the Database.\n" << poi << endl;
	}
}


/**
 * Function which returns the container having POIs in the Database
 * param@ Wp_Map_t &WpDatabase		-	POIs in Database	(IN)
 * returnvalue@ void
 */
const Poi_Map_t& CPoiDatabase::getPoisFromDatabase() const
{
	return (this->m_Poi);
}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI *pPoi = 0;

	if (!this->m_Poi.empty())
	{
		this->m_PoiItr = this->m_Poi.find(name);

		if (this->m_PoiItr != this->m_Poi.end())
		{
			// element found
			pPoi = &this->m_PoiItr->second;
		}
	}

	return pPoi;
}


/**
 * Reset the Database
 * returnvalue@ void
 */
void CPoiDatabase::resetPoisDatabase()
{
	this->m_Poi.clear();
}
