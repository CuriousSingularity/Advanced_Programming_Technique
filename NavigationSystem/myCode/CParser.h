/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CParser.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines class type - class CParser.
* 					The class CParser supports the algorithm to parse the
* 					input.
*
****************************************************************************/

#ifndef CPARSER_H_
#define CPARSER_H_

//System Include Files
#include <string>

//Own Include Files
#include "CPOI.h"

class CParser
{
private:

	/**
	 * The Possible delimiters are stored here
	 */
	static const std::string 		delimiters;

public:
	CParser();
	virtual ~CParser();

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
	bool parserEachLine(const std::string &readLine, std::string &name, double &latitude, double &longitude, const unsigned int lineCounter);

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
	bool parserEachLine(const std::string &readLine, CPOI::t_poi &type, std::string &name, std::string &description, double &latitude, double &longitude, const unsigned int lineCounter);

};

#endif /* CPARSER_H_ */
