/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSensor.h
* Author          : Bharath Ramachandraiah
* Description     : The file defines a class CGPSSensor.
* 					The class CGPSSensor is used to receive the current
* 					location from GPS sensor.
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

//System Include Files

//Own Include Files
#include "CWaypoint.h"

class CGPSSensor {
public:

	/**
	 * CGPSSensor constructor
	 */
	CGPSSensor();

	/**
	 * Get the current position from the sensor
	 * @returnval CWaypoint
	 */
	CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
