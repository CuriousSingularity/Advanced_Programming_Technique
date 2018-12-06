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
 * CPoiDatabase constructor
 */
CPoiDatabase::CPoiDatabase()
{
	// do nothing
}


/*
 * Add a Point of interest to the database
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(CPOI const &poi)
{
	CPOI 						inPoi = poi;
	pair<Poi_Map_Itr_t, bool> 	ret;

	if (!inPoi.getName().empty())
	{
		ret = this->m_Poi.insert(pair<string, CPOI>(inPoi.getName(), poi));

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
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI *pPoi = 0;

	if (!this->m_Poi.empty())
	{
		Poi_Map_Itr_t	poiItr = this->m_Poi.find(name);

		if (poiItr != this->m_Poi.end())
		{
			// element found
			pPoi = &poiItr->second;
		}
	}

	return pPoi;
}


/**
 * Get POIs from the Database
 * returnvalue@ Poi_Map_t			-	POIs in the Database	(OUT)
 */
const Poi_Map_t CPoiDatabase::getPoisFromDatabase() const
{
	return (this->m_Poi);
}


/**
 * Reset the Database
 * returnvalue@ void
 */
void CPoiDatabase::resetPoisDatabase()
{
	this->m_Poi.clear();
}


/**
 * Print all the POIs in the database
 * returnvalue@ void
 */
void CPoiDatabase::print()
{
	for (Poi_Map_Itr_t poiItr = this->m_Poi.begin(); poiItr != this->m_Poi.end(); ++poiItr)
	{
		cout << poiItr->second << endl;
	}
}
