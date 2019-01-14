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
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(CPOI const &poi)
{
	this->addPoi(poi.getName(), poi);
}


/*
 * Add a Point of interest to the database
 * param@ string &name			- 	unique name for the poi		(IN)
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
void CPoiDatabase::addPoi(const string &name, CPOI const &poi)
{
	if (!poi.getName().empty())
	{
		this->addElement(name, poi);
	}
	else
	{
		cout << "WARNING: Trying to add invalid POI to the Database.\n" << poi << endl;
	}
}


/*
 * Add a Point of interest to the database
 * param@ int &number			- 	unique number for the poi	(IN)
 * param@ CPOI const &poi		-	point of interest   		(IN)
 * returnvalue@ void
 */
//void CPoiDatabase::addPoi(const int &number, CPOI const &poi)
//{
//	this->addElement(number, poi);
//}


/**
 * Get pointer to a POI from the Database which matches the name
 * param@ string name		-	name of a POI					(IN)
 * returnvalue@ CPOI*		-	Pointer to a POI in the database
 */
CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	return (this->getPointerToElement(name));
}


/**
 * Get POIs from the Database
 * returnvalue@ Poi_Map_t			-	POIs in the Database	(OUT)
 */
const Poi_Map_t CPoiDatabase::getPoisFromDatabase() const
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
