/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

// Solution (Exercise 1.1; section f):
// Macros should be defined here (CWaypoint.h) so that it can be accessed by
// both print method and calling function.
#define DEGREE					1
#define MMSS					2

#define LATITUDE_MIN			(-90)
#define LATITUDE_MAX			(+90)
#define LONGITUDE_MIN			(-180)
#define LONGITUDE_MAX			(+180)

class CWaypoint {
private:

    void transformLongitude2degmmss(int& deg, int& mm, double& ss);

    void transformLatitude2degmmss(int& deg, int& mm, double& ss);

protected:

    string m_name;
    double m_latitude;
    double m_longitude;

public:
    // Assigning default values for objects created with no parameters
    CWaypoint(string name = "", double latitude = 0, double longitude = 0);

    void set(string name, double latitude, double longitude);

    string getName();

    double getLatitude();

    double getLongitude();

    void getAllDataByReference(string& name, double& latitude, double& longitude);

    double calculateDistance(const CWaypoint& wp);

    void print(int format);

};
/********************
**  CLASS END
*********************/
#endif /* CWAYPOINT_H */
