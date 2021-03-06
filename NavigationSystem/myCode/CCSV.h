/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCSV.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CCSV.
* 					The class CCSV is used to implement the Persistence feature.
*
****************************************************************************/

#ifndef CCSV_H
#define CCSV_H

//System Include Files
#include <string>

//Own Include Files
#include "CPersistentStorage.h"
#include "CParser.h"

class CCSV : public CPersistentStorage, public CParser {
private:

	/**
	 * Media Name of the Storage
	 */
	std::string 					mediaName;

	/**
	 * Line number of Database which is currently Parsing
	 */
	unsigned int 	lineCounter;

public:
	/**
	 * Constructor
	 */
	CCSV();

	/**
	 * Destructor
	 */
	~CCSV();

    /**
    * Set the name of the media to be used for persistent storage.
	* The exact interpretation of the name depends on the implementation
	* of the component.
	*
    * @param name the media to be used
    * @returnval void
	*/
    void setMediaName(std::string name);
	
    /**
    * Write the data to the persistent storage.
	*
    * @param waypointDb the data base with way points
	* @param poiDb the database with points of interest
	* @return true if the data could be saved successfully
	*/
    bool writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb);
	
    /**
    * Fill the databases with the data from persistent storage. If
	* merge mode is MERGE, the content in the persistent storage
	* will be merged with any content already existing in the data
	* bases. If merge mode is REPLACE, already existing content
	* will be removed before inserting the content from the persistent
	* storage.
	*
    * @param waypointDb the the data base with way points
	* @param poiDb the database with points of interest
	* @param mode the merge mode
	* @return true if the data could be read successfully
	*/
    bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);
};
/********************
**  CLASS END
*********************/
#endif /* CCSV_H */
