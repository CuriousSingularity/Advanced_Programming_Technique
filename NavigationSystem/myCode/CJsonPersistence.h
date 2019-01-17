/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CJsonPersistence.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CJsonPersistence.
* 					The class CJsonPersistence is used to implement the Persistence feature.
*
****************************************************************************/


#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_

#include "CJsonScanner.h"
#include "CPersistentStorage.h"

class CJsonPersistence : public CPersistentStorage
{
public:

	enum jsonObjects
	{
		WAYPOINTS = 0,
		POINT_OF_INTEREST,
		MAX_JSON_OBJECTS,
	};
	enum readStates
	{
		WAITING_FOR_BEGIN_OBJECT,
		WAITING_FOR_DB_NAME,
		WAITING_FOR_DB_ARRAY_BEGIN,
		//WAITING_FOR_DB_ARRAY_END,
		WAITING_FOR_DB_OBJECT_BEGIN,
		WAITING_FOR_DB_OBJECT_END,
		WAITING_FOR_ATTRIBUTE_NAME,
		WAITING_FOR_NAME_SEPARATOR,
		WAITING_FOR_VALUE,
		WAITING_FOR_VALUE_SEPARATOR,
		WAITING_FOR_COMPLETION,
	};

	enum jsonReadExceptions
	{
		JSON_ERR_NO = -1,
		JSON_ERR_EXPECT_BEGIN_OBJECT,
		JSON_ERR_EXPECT_DB_NAME_STRING,
		JSON_ERR_EXPECT_NAME_SEPARATOR,
		JSON_ERR_EXPECT_DB_ARRAY_BEGIN,
		JSON_ERR_EXPECT_DB_OBJECT_BEGIN,
		JSON_ERR_EXPECT_DB_OBJECT_END,
		JSON_ERR_EXPECT_ATTR_NAME,
		JSON_ERR_EXPECT_ATTR_VALUE,
		JSON_ERR_EXPECT_VALUE_SEPARATOR,
		JSON_ERR_ILLEGAL_CHARACTER,
	};

	CJsonPersistence();

	virtual ~CJsonPersistence();

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

private:

	/**
	 * Media Name of the Storage
	 */
	std::string 					mediaName;

	/**
	 * Attributes types expected
	 */
	CPOI::AttributesType 			m_exceptedAttributeType;

	/**
	 * A pointer to the json token
	 */
	APT::CJsonToken 				*m_pToken;

	/**
	 * An expected token
	 */
	APT::CJsonToken::TokenType 		m_exceptedTokenType;

	/**
	 * To keep track if all attributes are read
	 */
	bool							m_isAttrAlreadyRead[CPOI::MAX_TYPES];

	/**
	 * To keep track of the current object being read
	 */
	bool							m_currentObjectRead[MAX_JSON_OBJECTS];

	/**
	 * A function to reset the current read object flags
	 * return@void
	 */
	void resetCurrentReadObjects();

	/**
	 * A function to to set flag to signify the current object being read
	 * return@void
	 */
	bool currentReadObject(std::string name);

	/**
	 * A function to reset all the attributes flags
	 * return@void
	 */
	void resetAllAttributesRead();

	/**
	 * A function to check if all the attributes for an object is being read
	 * return@bool
	 */
	bool allAttributesRead();

	/**
	 * An exception handler for the possible errors
	 * param@ jsonReadExceptions& ex		- exception									(IN)
	 * param@ int lineNumber				- line number where the error has occured 	(IN)
	 * return@void
	 */
	void exceptionHandler(jsonReadExceptions& ex, int lineNumber);

	/**
	 * A function to check whether the string name is the expected attribute's name
	 * param@ string attributeName			- attribte name
	 * return@bool
	 */
	bool expectedAttributeValue(std::string attributeName);

	/**
	 * A function to extract values
	 * param@ string& name		-	name of a POI					(OUT)
	 * param@ double& latitude	-	latitude of a POI's Waypoint	(OUT)
	 * param@ double& longitude	-	longitude of a POI's Waypoint 	(OUT)
	 * param@ t_poi& type		-	point of interest type  		(OUT)
	 * param@ string&description-	description of a POI			(OUT)
	 * return@bool
	 */
	bool extractValue(std::string &name, double &latitude, double &longitude, CPOI::t_poi &type, std::string &description);
};

#endif /* CJSONPERSISTENCE_H_ */
