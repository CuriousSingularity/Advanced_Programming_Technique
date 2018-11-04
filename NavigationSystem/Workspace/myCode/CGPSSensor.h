/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

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
