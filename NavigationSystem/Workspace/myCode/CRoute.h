/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H
#include "CPoiDatabase.h"
#include "CWaypoint.h"
#include "CPOI.h"

class CRoute {
private:
    CWaypoint* m_pWaypoint;
    unsigned int m_maxWp;
    unsigned int m_nextWp;
    CPOI* * m_pPoi;
    unsigned int m_maxPoi;
    unsigned int m_nextPoi;
    CPoiDatabase* m_pPoiDatabase;
public:

    CRoute(unsigned int maxWp, unsigned int maxPoi);

    CRoute(CRoute const &origin);    

    ~CRoute();

    void connectToPoiDatabase(CPoiDatabase* pPoiDB);

    void addWaypoint(CWaypoint const &wp);

    void addPoi(string namePoi);

    double getDistanceNextPoi(int wp, CPOI& poi);

    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
