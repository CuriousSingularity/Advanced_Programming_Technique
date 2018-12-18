/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CParser.cpp
* Author          : Bharath Ramachandraiah
* Description     : The file defines all the methods pertaining to the
* 					class type - class CParser.
* 					The class CParser supports the algorithm to parse the
* 					input.
*
****************************************************************************/

//System Include Files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Own Include Files
#include "CParser.h"

//Namespaces
using namespace std;

//Class constant variables
const std::string CParser::delimiters(",;");

CParser::CParser()
{
	// TODO Auto-generated constructor stub

}

CParser::~CParser()
{
	// TODO Auto-generated destructor stub
}


/**
 * Extract number from the string
 * @param const string &str		-	string				(IN)
 * @param double &number		-	Number to return 	(OUT)
 * @returnval bool				- 	Success - true or Failure - false
 */
bool CParser::extractNumberFromString(const std::string &str, double &number)
{
	bool 			isNumber = false;

	if (!str.empty())
	{
		unsigned int index = 0;

		// remove all the leading spaces and tabs
		while ((str[index] == ' ') || (str[index] == '\t'))
		{
			index++;
		}

		for (unsigned int decPointCount = 0; index < str.length(); ++index)
		{
			// check if the string contains only numbers and maybe a .
			if (!((str[index] >= '0' && str[index] <= '9') || (str[index] == '.' && !decPointCount++)))
			{
				isNumber = false;
				break;
			}
			else
			{
				isNumber = true;
			}
		}

		if (isNumber)
		{
			stringstream	ss(str);

			// extract the number
			ss >> number;
		}
	}

	return isNumber;
}


/**
 * Parse a line to get waypoint information such as name, latitude and longitude in order
 * @param const string &readLine	-	Each Line				(IN)
 * @param const string &name		-	name of waypoint		(OUT)
 * @param const double &latitude	-	latitude of waypoint	(OUT)
 * @param const double &longitude	-	longitude of waypoint	(OUT)
 * @returnval bool					- 	Success - true or Failure - false
 */
bool CParser::parserEachLine(const string &readLine, std::string &name, double &latitude, double &longitude, const unsigned int lineCounter)
{
	bool			ret = true;

	// check if the one of the delimiters exists
	if (readLine.find_first_of(this->delimiters) != string::npos)
	{
		stringstream	ss(readLine);
		string			nameParsed, latitudeParsed, longitudeParsed;

		for (unsigned int index = 0; index < this->delimiters.length(); index++)
		{
			if (readLine.find_first_of(this->delimiters[index]) != string::npos)
			{
				getline(ss, nameParsed, 		this->delimiters[index]);
				getline(ss, latitudeParsed, 	this->delimiters[index]);
				getline(ss, longitudeParsed,	'\n');

				// remove leading spaces and tables
				nameParsed.erase(0, nameParsed.find_first_not_of(' '));
				nameParsed.erase(0, nameParsed.find_first_not_of('\t'));
				name = nameParsed;
				break;
			}
		}

		if ((!this->extractNumberFromString(latitudeParsed, latitude)) ||
			(!this->extractNumberFromString(longitudeParsed, longitude)) ||
			(nameParsed.empty()))
		{
			cout << "ERROR: Invalid or too few fields in line " << lineCounter << ": " << readLine << "\n";
			ret = false;
		}
	}
	else
	{
		cout << "ERROR: Could not find the delimiters in line " << lineCounter << ": " << readLine << "\n";
		ret = false;
	}

	return ret;
}


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
bool CParser::parserEachLine(const string &readLine, CPOI::t_poi &type, string &name, std::string &description, double &latitude, double &longitude, const unsigned int lineCounter)
{
	bool			ret = true;

	// check if the one of the delimiters exists
	if (readLine.find_first_of(this->delimiters) != string::npos)
	{
		stringstream	ss(readLine);
		string			typeParsed, nameParsed, descriptionParsed, latitudeParsed, longitudeParsed;

		for (unsigned int index = 0; index < this->delimiters.length(); index++)
		{
			if (readLine.find_first_of(this->delimiters[index]) != string::npos)
			{
				getline(ss, typeParsed, 		this->delimiters[index]);
				getline(ss, nameParsed, 		this->delimiters[index]);
				getline(ss, descriptionParsed,	this->delimiters[index]);
				getline(ss, latitudeParsed, 	this->delimiters[index]);
				getline(ss, longitudeParsed,	'\n');

				// remove leading spaces and tables
				nameParsed.erase(0, nameParsed.find_first_not_of(' '));
				nameParsed.erase(0, nameParsed.find_first_not_of('\t'));
				name 			= nameParsed;

				// remove leading spaces and tables
				descriptionParsed.erase(0, descriptionParsed.find_first_not_of(' '));
				descriptionParsed.erase(0, descriptionParsed.find_first_not_of('\t'));
				description 	= descriptionParsed;

				// remove leading spaces and tables
				typeParsed.erase(0, typeParsed.find_first_not_of(' '));
				typeParsed.erase(0, typeParsed.find_first_not_of('\t'));
				type			= CPOI::getPoiType(typeParsed);
				break;
			}
		}

		if ((!this->extractNumberFromString(latitudeParsed, latitude)) ||
			(!this->extractNumberFromString(longitudeParsed, longitude)) ||
			(CPOI::DEFAULT_POI == type) ||
			(nameParsed.empty()))
		{
			cout << "ERROR: Invalid or too few fields in line " << lineCounter << ": " << readLine << "\n";
			ret = false;
		}
	}
	else
	{
		cout << "ERROR: Could not find the delimiters in line " << lineCounter << ": " << readLine << "\n";
		ret = false;
	}

	return ret;
}
