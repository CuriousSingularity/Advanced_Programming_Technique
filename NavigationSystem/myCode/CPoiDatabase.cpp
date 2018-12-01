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
}


/*
 * Add a Point of interest to the database
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(CPOI const &poi)
{
//	// check if the Database has free memory to store new POI
//	if (this->m_noPoi < sizeof(this->m_POI)/sizeof(CPOI))
//	{
//		bool alreadyExist = false;
//
//		// check if the POI already exists
//		for (int Index = 0; Index < this->m_noPoi; Index++)
//		{
//			CPOI::t_poi getTypeFromDB;
//			string getNameFromDB, getDescriptionFromDB;
//			double getLatitudeFromDB, getLongitudeFromDB;
//
//			this->m_POI[Index].getAllDataByReference(getNameFromDB, getLatitudeFromDB, getLongitudeFromDB, getTypeFromDB, getDescriptionFromDB);
//
//			if ((getTypeFromDB == type) && (getNameFromDB == name) &&
//				(getLatitudeFromDB == latitude) && (getLongitudeFromDB == longitude))
//			{
//				// POI already exists
//				alreadyExist = true;
//				break;
//			}
//		}
//
//		if (!alreadyExist)
//		{
//			if ((CPOI::DEFAULT_POI != type) &&
//				((latitude >= LATITUDE_MIN) && (latitude <= LATITUDE_MAX)) &&
//				((longitude >= LONGITUDE_MIN) && (longitude <= LONGITUDE_MAX)) &&
//				(!name.empty()))
//			{
//				this->m_POI[this->m_noPoi] = CPOI(type, name, description, latitude, longitude);
//				this->m_noPoi++;
//			}
//			else
//			{
//				cout << "WARNING: Invalid POI. Not added to the Database.\n";
//			}
//		}
//		else
//		{
//			cout << "WARNING: POI already exists!\n";
//		}
//	}
//	else
//	{
//		cout << "WARNING: Database full!\n";
//	}
}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI *pPoi = 0;

//	for (int Index = 0; Index < this->m_noPoi; Index++)
//	{
//		if (this->m_POI[Index].CWaypoint::getName() == name)
//		{
//			pPoi = &this->m_POI[Index];
//			break;
//		}
//	}

	return pPoi;
}
