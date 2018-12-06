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

	/**
	 * The Possible delimiters are stored here
	 */
	static const std::string 		delimiters;

	/**
	 * Media Name of the Storage
	 */
	std::string 					mediaName;

	/**
	 * Line number of Database which is currently Parsing
	 */
	unsigned int 	lineCounter;

	/**
	 * Extract number from the string
	 * @param const string &str		-	string				(IN)
	 * @param double &number		-	Number to return 	(OUT)
	 * @returnval bool				- 	Success - true or Failure - false
	 */
	bool extractNumberFromString(const std::string &str, double &number);

	/**
	 * Parse a line to get waypoint information such as name, latitude and longitude in order
	 * @param const string &readLine	-	Each Line				(IN)
	 * @param const string &name		-	name of waypoint		(OUT)
	 * @param const double &latitude	-	latitude of waypoint	(OUT)
	 * @param const double &longitude	-	longitude of waypoint	(OUT)
	 * @returnval bool					- 	Success - true or Failure - false
	 */
	bool parserEachLine(const std::string &readLine, std::string &name, double &latitude, double &longitude);

	/**
	 * Parse a line to get POI information such as type, name, description, latitude and longitude in order
	 * @param const string &readLine	-	Each Line				(IN)
	 * @param const t_poi &type			-	name of POI				(OUT)
	 * @param const string &name		-	name of POI				(OUT)
	 * @param const string &description	-	description of POI		(OUT)
	 * @param const double &latitude	-	latitude of POI			(OUT)
	 * @param const double &longitude	-	longitude of POI		(OUT)
	 * @returnval bool					- 	Success - true or Failure - false
	 */
	bool parserEachLine(const std::string &readLine, CPOI::t_poi &type, std::string &name, std::string &description, double &latitude, double &longitude);

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
