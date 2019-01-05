/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CJson.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CJson.
* 					The class CJson is used to implement the Persistence feature.
*
****************************************************************************/


#ifndef CJSON_H_
#define CJSON_H_

#include "CJsonScanner.h"
#include "CPersistentStorage.h"

class CJson : public CPersistentStorage
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

	CJson();

	virtual ~CJson();

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

	CPOI::AttributesType 			m_exceptedAttributeType;

	APT::CJsonToken 				*m_pToken;

	APT::CJsonToken::TokenType 		m_exceptedTokenType;

	bool							m_isAttrAlreadyRead[CPOI::MAX_TYPES];

	bool							m_currentObjectRead[MAX_JSON_OBJECTS];

	void resetCurrentReadObjects();

	bool currentReadObject(std::string name);

	void resetAllAttributesRead();

	bool allAttributesRead();

	void exceptionHandler(jsonReadExceptions& ex, int lineNumber);

	bool expectedAttributeValue(std::string attributeName);

	bool extractValue(std::string &name, double &latitude, double &longitude, CPOI::t_poi &type, std::string &description);
};

#endif /* CJSON_H_ */
