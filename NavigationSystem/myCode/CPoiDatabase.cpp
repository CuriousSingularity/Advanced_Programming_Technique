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

/**
 * CPoiDatabase destructor
 */
CPoiDatabase::~CPoiDatabase()
{
	// do nothing
}


/*
 * Add a Point of interest to the database
 * param@ POI_Database_key_t &name	- 	unique name for the poi		(IN)
 * param@ CPOI const &poi			-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(POI_Database_key_t const &key, CPOI const &poi)
{
	this->addElement(key, poi);
}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string key		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(Database_Container_key_t key)
{
	return (this->getPointerToElement(key));
}


/**
 * Get POIs from the Database
 * returnvalue@ Poi_Map_t			-	POIs in the Database	(OUT)
 */
const CPoiDatabase::Poi_Map_t CPoiDatabase::getPoisFromDatabase() const
{
	return (this->getElementsFromDatabase());
}


/**
 * Reset the Database
 * returnvalue@ void
 */
void CPoiDatabase::resetPoisDatabase()
{
	this->resetDatabase();
}


/**
 * Print all the POIs in the database
 * returnvalue@ void
 */
void CPoiDatabase::print()
{
	this->CDatabase::print();
}
