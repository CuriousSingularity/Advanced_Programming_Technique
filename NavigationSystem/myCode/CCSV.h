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

class CCSV : public CPersistentStorage {
private:

	static const std::string delimiters;
	std::string 	mediaName;

	unsigned int 	lineCounter;

	bool extractNumberFromString(const std::string &str, double &number);

	bool parserEachLine(const std::string &readLine, std::string &name, double &latitude, double &longitude);

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
