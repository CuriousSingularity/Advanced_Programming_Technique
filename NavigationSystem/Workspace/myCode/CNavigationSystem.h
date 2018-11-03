/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNAVIGATIONSYSTEM.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"
class CNavigationSystem {
private:

    CGPSSensor m_GPSSensor;
    CRoute m_route;
    CPoiDatabase m_PoiDatabase;

    void enterRoute();
    void printRoute();
    void printDistanceCurPosNextPoi();

public:

    CNavigationSystem();

    void run();

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */
